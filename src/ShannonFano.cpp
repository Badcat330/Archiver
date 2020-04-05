//
// Created by Alex Glushko on 03.04.2020.
//

#include "ShannonFano.h"

namespace archiver
{

const int BYTE_SIZE = 256;

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

void ShannonFano::code_builder(int left, int right, bit_code current_code, int &max_length)
{
    if(left < right)
    {
        int median = find_median(left, right);
        bit_code left_code = current_code;
        left_code.push_back(bit(0));
        bit_code right_code = current_code;
        right_code.push_back(bit(1));
        code_builder(left, median, left_code, max_length);
        code_builder(median + 1, right, right_code, max_length);
    }
    else{
        code_words[chances[left].first] = current_code;

        if(max_length < current_code.size())
        {
            max_length = current_code.size();
        }
    }
}

void ShannonFano::chances_add(ReadWrite &read_write)
{
    for (int i = 0; i < BYTE_SIZE; ++i)
    {
        chances.emplace_back(i, 0);
    }

    // We will write end of text symbol in the end of the file,
    // that is why we need to increase it's chance
    chances[3].second += 1;

    byte buf;
    while (read_write.read_byte(buf))
    {
        chances[buf].second += 1;
    }

    std::sort(chances.begin(), chances.end(), pair_comparator());

    while (chances[chances.size() - 1].second == 0)
    {
        chances.pop_back();
    }
}

void ShannonFano::pack_file(std::string &path)
{
    // Create pack file name
    std::string out_path = path + ".shan";

    // Create class for reading and writing
    ReadWrite read_write(path, out_path);

    // Add chances to vector
    chances_add(read_write);

    // Build codes and find it's max length
    int max_length = 0;
    code_builder(0, chances.size() - 1, bit_code(), max_length);

    // Write down number of symbols
    read_write.write_byte((byte)code_words.size());

    // Write number of 8 length bit set for codes
    int number_bitset = (max_length + 1) % 8 != 0 ? (max_length + 1) / 8 + 1 : (max_length + 1) / 8;
    read_write.write_byte(number_bitset);

    // Write down symbol and it's code
    std::bitset<8> buf_bitset;
    std::size_t index = 7;
    int write_count = 0;
    for (const auto& pair : code_words)
    {
        read_write.write_byte(pair.first);
        for (bit current_bit : pair.second)
        {
            buf_bitset[index] = current_bit[0];
            --index;
            if(index == -1)
            {
                read_write.write_bitset(buf_bitset);
                index = 7;
                buf_bitset.reset();
                ++write_count;
            }
        }
        if(index != 7)
        {
            buf_bitset[index] = true;
            read_write.write_bitset(buf_bitset);
            buf_bitset.reset();
            ++write_count;
        }
        while (write_count < number_bitset)
        {
            read_write.write_bitset(buf_bitset);
            ++write_count;
        }
        index = 7;
        write_count = 0;
    }

    // Reset stream
    read_write.reset_reader();

    // Read symbols, find bit set for them and accumulate them in bit set with 8 bits
    byte buf_symbol;
    index = 7;
    while (read_write.read_byte(buf_symbol))
    {
        bit_code current = code_words[buf_symbol];
        for (bit current_bit : current)
        {
            buf_bitset[index] = current_bit[0];
            --index;
            if(index == -1)
            {
                read_write.write_bitset(buf_bitset);
                index = 7;
                buf_bitset.reset();
            }
        }
    }

    // Write end of text symbol
    for (bit current_bit : code_words[3])
    {
        buf_bitset[index] = current_bit[0];
        --index;
        if(index == -1)
        {
            read_write.write_bitset(buf_bitset);
            index = 7;
            buf_bitset.reset();
        }
    }

    // Write last set if it not clear
    if(index != 7)
        read_write.write_bitset(buf_bitset);
}

} // namespace archiver