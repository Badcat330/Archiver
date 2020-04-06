//
// Created by Alex Glushko on 01.04.2020.
//

#ifndef KDZ_ARCHIVER_TIMER_H
#define KDZ_ARCHIVER_TIMER_H

#include <string>
#include <ctime>

namespace archiver
{

class Timer
{

public:

    /**
     * Start timer
     * write start time in time_start
     */
    void start();

    /**
     * Finish timer
     * write finish time un time_finish
     */
    void finish();

    /**
     * Count difference between time_start and time_finish
     * and transform it into seconds and milliseconds
     * @return result string
     */
    std::string result_string();

    /**
     * Reset timer
     * put time_start and time_finish to 0
     */
    void reset();

private:

    double time_start;
    double time_finish;

};

}

#endif //KDZ_ARCHIVER_TIMER_H
