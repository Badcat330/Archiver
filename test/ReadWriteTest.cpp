//
// Created by Alex Glushko on 03.04.2020.
//

#include <gtest/gtest.h>

#include "ReadWrite.h"

TEST(ReadWriteTest, CreationTest)
{
    using namespace archiver;

    ReadWrite r("Makefile", "output.txt");
    std::remove("output.txt");
}

TEST(ReadWriteTest, ReadTest)
{
    using namespace archiver;

    // Create file with special symbols
    std::fstream fout;
    fout.open("output.txt", std::ios::out);
    std::string test = "qjdµbvp \n edcwe®fv \t \t   fasdv";
    fout << test;
    fout.close();

    // Crate ReadWriter
    ReadWrite readWrite("output.txt");

    // Read file in string
    std::string out_string;
    byte buf = 0;
    while (readWrite.read_byte(buf))
    {
        out_string += buf;
    }

    // Check test string and our output
    EXPECT_EQ(test, out_string);

    // Clean after test
    std::remove("output.txt");
}

TEST(ReadWriteTest, WritingTest)
{
    using namespace archiver;

    //Write test string in file by REadWriter
    std::string test = "qwert \n ¥fad";
    int test_number = 134132;

    {
        ReadWrite readWrite("", "output.txt");

        for (byte i : test)
        {
            readWrite.write_byte(i);
        }


        readWrite.write_byte('\n');

        readWrite.write_int(test_number);
    }

    // Open stream and check is everything okay
    std::fstream fin;
    fin.open("output.txt", std::ios::in);

    for (byte i  : test)
    {
        char ch;
        fin.get(ch);

        EXPECT_EQ(i, (byte)ch);
    }

    char ch;
    fin.get(ch);
    EXPECT_EQ('\n', ch);

    int out_number;
    fin >> out_number;
    EXPECT_EQ(out_number, test_number);

    // Clean after testing
    std::remove("output.txt");
}

TEST(ReadWriteTest, ResetTest)
{
    using namespace archiver;

    // Create file with special symbols
    std::fstream fout;
    fout.open("output.txt", std::ios::out);
    std::string test = "qjdµbvp \n edcwe®fv \t \t   fasdv";
    fout << test;
    fout.close();

    // Crate ReadWriter
    ReadWrite readWrite("output.txt");

    // Read file in string
    std::string out_string_first;
    byte buf = 0;
    while (readWrite.read_byte(buf))
    {
        out_string_first += buf;
    }

    readWrite.reset_reader();

    std::string out_string_second;
    while (readWrite.read_byte(buf))
    {
        out_string_second += buf;
    }

    EXPECT_EQ(out_string_first, test);
    EXPECT_EQ(out_string_second, test);
}