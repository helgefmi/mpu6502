#ifndef __TESTSUITE_H
#define __TESTSUITE_H

#include <string>
#include <vector>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

namespace fs = boost::filesystem;

class Mpu6502;

class TestSuite
{
    public:
        TestSuite();
        ~TestSuite();
        void run(const std::string&);
    private:
        void test_file(const fs::path&);
        bool run_test(const std::string&, const std::vector<std::string>&);
        bool check_assertion(const std::string&, const std::string&, const std::string&);

        int successive_tests;
        int failed_tests;
        Mpu6502 *mpu_ptr;
};

#endif
