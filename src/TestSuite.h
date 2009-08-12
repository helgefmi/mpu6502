#ifndef __TESTSUITE_H
#define __TESTSUITE_H

#include "Mpu6502.h"
#include <string>
#include <vector>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

namespace fs = boost::filesystem;

class TestSuite
{
    public:
        void run(const std::string&);
    private:
        void test_file(const fs::path&);
        bool run_test(const std::string&, const std::vector<std::string>&);
        bool check_assertion(const Mpu6502&, const std::string&, const std::string&, const std::string&);

        int successive_tests;
        int failed_tests;
};

#endif
