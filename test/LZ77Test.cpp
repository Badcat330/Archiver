//
// Created by Alex Glushko on 06.04.2020.
//


#include <gtest/gtest.h>
#include <fstream>

#include "LZ77.h"

TEST(LZ77Test, SimpelPackTest)
{
    using namespace archiver;

    LZ77 arch;

    std::string test_path1 = "../../test/test_data/archiver_test_1";

    arch.pack_file(test_path1, 8 * 1024, 2 * 1024);
}

TEST(LZ77Test, SimpelUnPackTest)
{
    using namespace archiver;

    LZ77 arch;

    std::string test_path1 = "../../test/test_data/archiver_test_1.lz7710";

    arch.unpack_file(test_path1, 8 * 1024, 2 * 1024);
}

TEST(LZ77Test, PackUnPackTest)
{
    using namespace archiver;
    LZ77 arch;
    std::string test_path1 = "../../test/test_data/archiver_test_3";
    std::string test_path2 = "../../test/test_data/archiver_test_3.lz775";

//    std::remove("../../test/test_data/archiver_test_1.lz775");
//    std::remove("../../test/test_data/archiver_test_1.unlz775");

    arch.pack_file(test_path1, 4 * 1024, 1024);
    arch.unpack_file(test_path2, 4 * 1024, 1024);

    std::fstream fin1;
    std::fstream fin2;
    fin1.open("../../test/test_data/archiver_test_3.unlz775", std::ios::in);
    fin2.open(test_path1, std::ios::in);

    do
    {
        char ch1, ch2;
        fin1.get(ch1);
        fin2.get(ch2);
        EXPECT_EQ(ch1, ch2);
        if(ch1 != ch2)
            break;
    }while (!fin1.eof());
}