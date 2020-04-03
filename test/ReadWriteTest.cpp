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