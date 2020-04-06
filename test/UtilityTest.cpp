//
// Created by Alex Glushko on 05.04.2020.
//

#include <gtest/gtest.h>

#include "Utility.h"

TEST(EntropyTest, SimpelFileEntropyTest)
{
    using namespace archiver;

    Utility utility;
    std::string test_path1 = "../../test/test_data/archiver_test_1";

    utility.entropy_file(test_path1);
}

TEST(EntropyTest, FileEntropyTest)
{
    using namespace archiver;

    Utility utility;
    std::string test_path1 = "../../test/test_data/";

    utility.entropy_dir(test_path1);
}

TEST(AspectRatio, SimpelAspectRatio)
{
    using namespace archiver;

    Utility utility;
    std::string test_path1 = "../../test/test_data/";
    std::string test_type = ".shan";

    utility.aspect_ratio(test_path1, test_type);
}