#include <iostream>
#include <string>
#include <boost/program_options.hpp>
#include "Mpu6502.h"
#include "TestSuite.h"
#include "Util.h"
#include "exceptions.h"

namespace po = boost::program_options;

int main(int argc, char **argv)
{
    std::string tests_path, file_path;
    static po::variables_map vm;

    /* Specify the valid arguments */
    static po::options_description args("Optional options");

    args.add_options()
        ("test-path,p", po::value<std::string>(&tests_path)->default_value("tests/"),
            "Specify path to testsuite (directory or single file)")
        ("run-tests,t", "Do the testsuite pointed at by tests-path")
        ("file,f", po::value<std::string>(&file_path), "Copy a binary file to memory and start simulation")
        ("help,h", "Help")
    ;

    /* Parse arguments into 'vm' */
    try
    {
        po::store(po::parse_command_line(argc, argv, args), vm);
        po::notify(vm);
    }
    catch (po::error &e)
    {
        std::cerr << e.what() << std::endl;
        std::cout << args << std::endl;
        return 1;
    }

    /* --help */
    if (vm.count("help"))
    {
        std::cout << args << std::endl;
        return 0;
    }

    /* --file */
    if (vm.count("file"))
    {
        Mpu6502 mpu;
        try
        {
            mpu.load_binary_file(file_path, 0);
            mpu.subscribe_to_write(0xF001, 1, Util::std_cout_cb);
            mpu.subscribe_to_read(0xF004, 1, Util::std_getch_cb);

            try
            {
                mpu.run();
            }
            catch (InvalidOpcodeException &e)
            {
                std::cerr << e.what() << std::endl;
                return 1;
            }
            catch (std::exception &e)
            {
                std::cerr << e.what() << std::endl;
                return 1;
            }
        }
        catch (std::exception &e)
        {
            std::cerr << e.what() << std::endl;
            return 1;
        }
    }

    /* --run-tests */
    if (vm.count("run-tests"))
    {
        TestSuite testSuite;
        try
        {
            testSuite.run(tests_path);
        }
        catch (std::exception &e)
        {
            std::cerr << e.what() << std::endl;
            return 1;
        }
    }

    return 0;
}
