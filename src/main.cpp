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

    /* Arguments -- will have values filled in by program_options */
    std::string tests_path;

    /* Specify the valid arguments */
    static po::options_description args("Optional options");
    static po::variables_map vm;

    args.add_options()
        ("tests-path,p", po::value<std::string>(&tests_path)->default_value("tests/"),
            "Specify path to testsuite (directory or single file)")
        ("run-tests,r", "Do the testsuite pointed at by tests-path")
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
        return 1;
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
        }
    }

    return 0;
}
