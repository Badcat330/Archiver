//
// Created by Alex Glushko on 03.04.2020.
//

#include "ShannonFano.h"

namespace archiver
{

int ShannonFano::find_median(int left, int right)
{
    int left_sum = chances[left].second;
    int right_sum = chances[right].second;

    int i = left + 1;
    int j = right - 1;

    while (i <= j)
    {
        if(left_sum >= right_sum)
        {
            right_sum +=  chances[j].second;
            --j;
        }
        else
        {
            left_sum += chances[i].second;
            ++i;
        }
    }

    return i - 1;
}

void ShannonFano::code_builder(int left, int right, std::string current_code)
{
    if(left < right)
    {
        int median = find_median(left, right);
        code_builder(left, median, current_code + '0');
        code_builder(median + 1, right, current_code + '1');
    }
    else{
        code_words[chances[left].first] = current_code;
    }
}

} // namespace archiver