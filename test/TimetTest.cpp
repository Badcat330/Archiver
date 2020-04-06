//
// Created by Alex Glushko on 06.04.2020.
//

#include <gtest/gtest.h>

#include "Timer.h"
#include "ShannonFano.h"

TEST(TimerTest, SimpelShanTimerTest)
{
    using namespace archiver;

    ShannonFano shan;
    Timer timer;

    std::string test_path1 = "../../test/test_data/archiver_test_3";
    std::string test_path2 = "../../test/test_data/archiver_test_3.shan";

    timer.start();
    shan.pack_file(test_path1);
    timer.finish();

    std::cout << "Shannon - Fano pack time " + timer.result_string() << std::endl;

    timer.start();
    shan.unpack_file(test_path2);
    timer.finish();

    std::cout << "Shannon - Fano unpack time " + timer.result_string() << std::endl;

}