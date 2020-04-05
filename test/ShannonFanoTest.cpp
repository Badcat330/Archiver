//
// Created by Alex Glushko on 03.04.2020.
//

#include <gtest/gtest.h>
#include <gtest/gtest_prod.h>

#include "ShannonFano.h"
#include "ReadWrite.h"

namespace archiver
{
    TEST(ShennonFano, AddChanceTest)
    {
        std::fstream fout;
        fout.open("output.txt", std::ios::out);
        fout << "aaaraatctct";
        fout.close();

        ReadWrite r("output.txt");

        ShannonFano arch;
        arch.chances_add(r);

        EXPECT_EQ(arch.chances[0].first, (byte)'a');
        EXPECT_EQ(arch.chances[0].second, 5);

        EXPECT_EQ(arch.chances[1].first, (byte)'t');
        EXPECT_EQ(arch.chances[1].second, 3);

        EXPECT_EQ(arch.chances[2].first, (byte)'c');
        EXPECT_EQ(arch.chances[2].second, 2);

        EXPECT_EQ(arch.chances[3].first, (byte)'r');
        EXPECT_EQ(arch.chances[3].second, 1);
    }

    TEST(ShannonFano, PackFileTest)
    {
        ShannonFano arch;
        std::string test_path = "../../test/test_data/archiver_test_2";
        arch.pack_file(test_path);
    }
}