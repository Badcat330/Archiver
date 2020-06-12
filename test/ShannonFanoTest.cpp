//
// Created by Alex Glushko on 03.04.2020.
//

#include <gtest/gtest.h>

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

    TEST(ShannonFano, SimpelPackFileTest)
    {
        ShannonFano arch;
        std::string test_path1 = "../../test/test_data/archiver_test_1";
        std::string test_path2 = "../../test/test_data/archiver_test_2";

        std::remove("../../test/test_data/archiver_test_1.shan");
        std::remove("../../test/test_data/archiver_test_2.shan");


        arch.pack_file(test_path1);
        arch.pack_file(test_path2);
    }

    TEST(ShannonFano, SimpelUnPackTest)
    {
        ShannonFano arch;
        std::string test_path1 = "../../test/test_data/archiver_test_1.shan";
        std::string test_path2 = "../../test/test_data/archiver_test_2.shan";

        std::remove("../../test/test_data/archiver_test_1.unshan");
        std::remove("../../test/test_data/archiver_test_2.unshan");

        arch.unpack_file(test_path1);
        arch.unpack_file(test_path2);
    }

    TEST(ShannonFano, SimpelPackUnPackTest)
    {
        ShannonFano arch;
        std::string test_path1 = "../../test/test_data/archiver_test_2";
        std::string test_path2 = "../../test/test_data/archiver_test_2.shan";

        std::remove("../../test/test_data/archiver_test_2.shan");
        std::remove("../../test/test_data/archiver_test_2.unshan");

        arch.pack_file(test_path1);
        arch.unpack_file(test_path2);
    }

    TEST(ShannonFano, PackUnPackTest)
    {
        ShannonFano arch;
        std::string test_path1 = "../../test/test_data/archiver_test_3";
        std::string test_path2 = "../../test/test_data/archiver_test_3.shan";

        std::remove("../../test/test_data/archiver_test_3.shan");
        std::remove("../../test/test_data/archiver_test_3.unshan");

        arch.pack_file(test_path1);
        arch.unpack_file(test_path2);

        std::fstream fin1;
        std::fstream fin2;
        fin1.open("../../test/test_data/archiver_test_3.unshan", std::ios::in);
        fin2.open(test_path1, std::ios::in);

        do
        {
            char ch1, ch2;
            fin1.get(ch1);
            fin2.get(ch2);
            EXPECT_EQ(ch1, ch2);
        }while (!fin1.eof());
    }

    TEST(ShannonFano, SimpelDirPack)
    {
        ShannonFano arch;
        std::string path = "../../test/test_data/";
        arch.pack_dir(path);
    }

    TEST(ShannonFano, SimpelDirUnPack)
    {
        ShannonFano arch;
        std::string path = "../../test/test_data/";

        arch.unpack_dir(path);
    }
}