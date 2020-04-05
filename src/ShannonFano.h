//
// Created by Alex Glushko on 01.04.2020.
//

#ifndef KDZ_ARCHIVER_SHANNONFANO_H
#define KDZ_ARCHIVER_SHANNONFANO_H

#include <string>
#include <map>
#include <iterator>
#include <vector>

#include "../test/gtest/gtest_prod.h"
#include "ReadWrite.h"

namespace archiver
{

class ShannonFano
{

public:

    /**
     * Method for packing all files in dir
     * @param path to dir
     */
    void pack_dir(std::string& path);

    /**
     * Method for unpacking all files in dir
     * @param path to dir
     */
    void unpack_dir(std::string& path);

    /**
     * Method for packing file
     * @param path to file
     */
    void pack_file(std::string& path);

    /**
     * Method for unpacking file
     * @param path to file
     */
    void unpack_file(std::string& path);

private:

    std::vector<std::pair<byte, int>> chances;
    std::map<byte, bit_code> code_words;

    /**
     * Comparator for vector chance sorting
     */
    struct pair_comparator
    {
        bool operator()(const std::pair<byte, int> &left,const std::pair<byte, int> &right)
        {
            return left.second > right.second;
        }
    };

    /**
     * build code from chances map
     * and write code in code map
     * @param left index of vector
     * @param right right index of vector
     * @param current_code
     */
    void code_builder(int left, int right, bit_code current_code, int &max_lenght);

    /**
     * Find median of chances map
     * @param left index of vector
     * @param right index of vector
     * @return median
     */
    int find_median(int left, int right);

    /**
     * Fill chances map
     * @param path to file
     */
    void chances_add(ReadWrite &read_write);

    // Friend_Tests

    FRIEND_TEST(ShennonFano, AddChanceTest);

}; // class ShannonFano

} // namespace archiver
#endif //KDZ_ARCHIVER_SHANNONFANO_H
