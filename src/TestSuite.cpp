#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <exception>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include "TestSuite.h"
#include "Mpu6502.h"
#include "Memory6502.h"
#include "defines.h"
#include "exceptions.h"

namespace fs = boost::filesystem;

TestSuite::TestSuite() // {{{
{
    mpu_ptr = new Mpu6502();
} // }}}
TestSuite::~TestSuite() // {{{
{
    delete mpu_ptr;
} // }}}

void TestSuite::run(const std::string &path) // {{{
{
    fs::path fs_path(path);

    if (!fs::exists(fs_path))
    {
        std::cerr << "Path not found: " << fs_path << std::endl;
        std::cerr << "Couldn't start testsuite :-/" << std::endl;
        return;
    }

    successive_tests = 0;
    failed_tests = 0;

    if (fs::is_directory(fs_path))
    {
        for (fs::basic_recursive_directory_iterator<fs::path> it(fs_path), end; it != end; ++it)
        {
            if (fs::extension(*it) == ".t")
            {
                fs::path fs_path(it->path());
                test_file(fs_path);
            }
        }
    }
    else
    {
        test_file(fs_path);
    }

    std::cout << std::endl << "Failed " << failed_tests << "/" << (failed_tests + successive_tests) << " tests" << std::endl;
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

            /* Break if we find an assertion */
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

        if (was_success)
        {
            ++successive_tests;
        }
        else
        {
            std::cout << path << ", " << name << ": FAIL" << std::endl;
            ++failed_tests;
        }
    }

    file_stream.close();
} // }}}
bool TestSuite::run_test(const std::string &code, const std::vector<std::string> &asserts) // {{{
{
    fs::ofstream out("asm.tmp");
    out << code;
    out.close();

    bool compile_success = (0 == system("xa -CW -bt0 asm.tmp"));
    if (!compile_success)
    {
        std::cerr << "Couldn't compile test:" << std::endl;
        unlink("asm.tmp");
        unlink("a.o65");
        return false;
    }

    /* Load the contents into the MPU */
    mpu_ptr->reset();
    mpu_ptr->load_binary_file("a.o65", 0);

    unlink("asm.tmp");
    unlink("a.o65");

    /* Step through the code */
    try
    {
        mpu_ptr->run();
    }
    catch (InvalidOpcodeException &e)
    {
        if (e.get_opcode() != 2)
        {
            std::cerr << e.what() << std::endl;
            return false;
        }
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

        /* Every assertion should be space delimited with 3 sections: type, source and value */
        std::string assertType, source, value;
        is >> assertType;
        is >> source;
        is >> value;

        bool assert_success = check_assertion(assertType, source, value);

        if (!assert_success)
            asserts_success = false;
    }

    return asserts_success;
} // }}}
bool TestSuite::check_assertion(const std::string &assertType, const std::string &str_source, const std::string &str_value) // {{{
{
    uint16_t source, value;

    if (str_source.find("mem.") == 0)
    {
        /* We're comparing with a place in memory */
        /* Might be prefixed by 0x to indicate hex. strtol() takes care of this! */
        uint16_t int_val = strtol(str_source.substr(4).c_str(), 0, 0);

        source = mpu_ptr->mem_ptr->get_byte(int_val);
    }

    else if (str_source.find("reg.") == 0)
    {
        /* We're comparing with a register */
        char char_val = str_source.at(4);
        switch (char_val)
        {
            case 'p':
                if (str_source.size() > 5 && str_source.at(5) == 's')
                {
                    source = (uint8_t) mpu_ptr->reg.ps.to_ulong();
                }
                else
                {
                    source = mpu_ptr->reg.pc;
                }
                break;
            case 's':
                source = mpu_ptr->reg.sp;
                break;
            case 'a':
                source = mpu_ptr->reg.ac;
                break;
            case 'x':
                source = mpu_ptr->reg.x;
                break;
            case 'y':
                source = mpu_ptr->reg.y;
                break;
            default:
                std::cerr << "Invalid source for assertion: " << str_source << std::endl;
                return false;
        }
    }
    else if (str_source.find("flags.") == 0)
    {
        /* We're comparing with the Process Status register */
        char char_val = str_source.at(6);
        switch (char_val)
        {
            case 'b':
                source = mpu_ptr->reg.ps[FLAG_BREAK];
                break;
            case 'z':
                source = mpu_ptr->reg.ps[FLAG_ZERO];
                break;
            case 'n':
                source = mpu_ptr->reg.ps[FLAG_NEGATIVE];
                break;
            case 'c':
                source = mpu_ptr->reg.ps[FLAG_CARRY];
                break;
            case 'd':
                source = mpu_ptr->reg.ps[FLAG_DECIMAL];
                break;
            case 'i':
                source = mpu_ptr->reg.ps[FLAG_INTERRUPT];
                break;
            case 'v':
                source = mpu_ptr->reg.ps[FLAG_OVERFLOW];
                break;
            default:
                std::cerr << "Invalid source for assertion: " << str_source << std::endl;
                return false;
        }
    }
    else
    {
        std::cerr << "Invalid source for assertion: " << str_source << std::endl;
        return false;
    }

    /* Might be prefixed by 0x to indicate hex. strtol() takes care of this! */
    value = strtol(str_value.c_str(), 0, 0);

    if (source != value)
    {
        std::cerr << "Failed assertion: '" << assertType << ' ' << str_source << ' ' << str_value << "'. "
                  << source << " != " << value << std::endl;
        std::cerr << mpu_ptr->to_string() << std::endl;
        return false;
    }
    
    return true;
} // }}}
