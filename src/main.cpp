#include "Mpu6502.h"
#include "TestSuite.h"
#include "exceptions.h"
#include <iostream>
#include <string>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

int main(int argc, char **argv)
{
    Mpu6502 cpu;

    std::string tests_path;
    static po::variables_map vm;

    /* Specify the valid arguments */
    static po::options_description args("Optional options");

    args.add_options()
        ("test-path,p", po::value<std::string>(&tests_path)->default_value("tests/"),
            "Specify path to testsuite (directory or single file)")
        ("run-tests,t", "Do the testsuite pointed at by tests-path")
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
            return 2;
        }
    }

    return 0;
}
