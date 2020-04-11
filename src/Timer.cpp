//
// Created by Alex Glushko on 06.04.2020.
//

#include "Timer.h"

namespace archiver
{

void Timer::start()
{
    time_start = clock();
}

void Timer::finish()
{
    time_finish = clock();
}

std::string Timer::result_string()
{
    std::string buf;
    buf += std::to_string(int(time_finish - time_start) / CLOCKS_PER_SEC) + "s " +
           std::to_string(int(time_finish - time_start) % (CLOCKS_PER_SEC / 1000)) + "ms";

    return buf;
}

double Timer::result()
{
    return time_finish - time_start;
}

void Timer::reset()
{
    time_start = 0;
    time_finish = 0;
}

}