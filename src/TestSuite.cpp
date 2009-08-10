#include "TestSuite.h"
#include "Mpu6502.h"
#include "Memory6502.h"
#include "exceptions.h"
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <exception>

namespace fs = boost::filesystem;

void TestSuite::run(const std::string &path) // {{{
{
    fs::path fs_path(path);
    if (!fs::exists(fs_path))
    {
        std::cerr << "Path not found: " << fs_path.file_string() << std::endl;
        std::cerr << "Couldn't start testsuite :-/" << std::endl;
        return;
    }

    for (fs::basic_recursive_directory_iterator<fs::path> it(fs_path), end; it != end; ++it)
    {
        if (fs::extension(*it) == ".t")
        {
            fs::path it_path(it->path());
            test_file(it_path);
        }
    }
} // }}}
void TestSuite::test_file(const fs::path &path) // {{{
{
    fs::ifstream file_stream(path);

    if (!file_stream.is_open())
    {
        std::cerr << "Couldn't open the file " << path << std::endl;
        return;
    }

    while (!file_stream.eof())
    {
        std::string line, name, code;
        std::vector<std::string> asserts;

        /* Get the name */
        do
        {
            getline(file_stream, name);
        } while (!file_stream.eof() && name.substr(0, 4) != "test");

        /* Remove the 'test ' part of name */
        name.erase(0, 5);

        /* Get the assembly lines */
        do
        {
            getline(file_stream, line);

            /* Break if we find an assertion, which represents the end of the assembly-section */
            if (line.find("assert") == 0)
            {
                asserts.push_back(line);
                break;
            }
            code += line + "\n";
        } while (!file_stream.eof());

        /* Get the assertions */
        do
        {
            getline(file_stream, line);

            /* Break when we find an empty line (which represents the end of a test) */
            if (line.length() == 0)
                break;

            asserts.push_back(line);
        } while (!file_stream.eof());

        bool was_success = run_test(code, asserts);
        std::cout << path << ", " << name << (was_success ? ": SUCCESS" : ": FAIL") << std::endl;
    }

    file_stream.close();
} // }}}
bool TestSuite::run_test(const std::string &code, const std::vector<std::string> &asserts) // {{{
{
    fs::ofstream out("asm.tmp");
    out << code;
    out.close();

    bool compile_success = (0 == system("xa asm.tmp"));
    if (!compile_success)
    {
        std::cerr << "Couldn't compile test:" << std::endl;
        unlink("asm.tmp");
        unlink("a.o65");
        return false;
    }

    /* Load the contents into the MPU */
    Mpu6502 mpu;
    mpu.load_binary_file("a.o65");

    unlink("asm.tmp");
    unlink("a.o65");

    /* Tick through the code */
    try
    {
        /* I think the number of ticks will always be the number of code lines .. */
        int steps = std::count(code.begin(), code.end(), '\n');
        while (steps--)
        {
            mpu.tick();
        }
    }
    catch (InvalidOpcodeException &e)
    {
        std::cerr << e.what() << std::endl;
        return false;
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return false;
    }

    bool asserts_success = true;

    /* Run through every assertion */
    for (std::vector<std::string>::const_iterator it = asserts.begin(), end = asserts.end(); it != end; ++it)
    {
        std::istringstream is(*it);

        /* Every assertion should be space delimited with the 3 sections, type, source, value */
        std::string assertType, source, value;
        is >> assertType;
        is >> source;
        is >> value;

        bool assert_success = check_assertion(mpu, assertType, source, value);

        if (!assert_success)
        {
            asserts_success = false;
        }
    }

    return asserts_success;
} // }}}
bool TestSuite::check_assertion(const Mpu6502 &mpu, const std::string &assertType, const std::string &str_source, const std::string &str_value) // {{{
{
    int source = -1, value = -2;

    /* We're comparing with a place in memory */
    if (str_source.find("mem.") == 0)
    {
        /* Might be proceeded by 0x to indicate hex. strtol() takes care of this! */
        int int_val = strtol(str_source.substr(4).c_str(), 0, 0);

        source = mpu.mem->byteAt(int_val);
    }

    /* We're comparing with a register */
    else if (str_source.find("reg.") == 0)
    {
        char char_val = str_source.at(4);
        switch (char_val)
        {
            case 'a':
                source = mpu.reg.ac;
                break;
            case 'p':
                source = mpu.reg.pc;
                break;
            case 'x':
                source = mpu.reg.x;
                break;
            case 'y':
                source = mpu.reg.y;
                break;
            case 's':
                source = mpu.reg.sp;
                break;
            default:
                std::cerr << "Invalid source for assertion: " << str_source << std::endl;
                return false;
        }
    }
    else
    {
        std::cerr << "Invalid source for assertion: " << source << std::endl;
        return false;
    }

    /* Might be proceeded by 0x to indicate hex. strtol() takes care of this! */
    value = strtol(str_value.c_str(), 0, 0);

    if (source != value)
    {
        std::cerr << "Failed assertion: '" << assertType << ' ' << str_source << ' ' << str_value << "'. " << source << " != " << value << std::endl;
        return false;
    }
    
    return true;
} // }}}