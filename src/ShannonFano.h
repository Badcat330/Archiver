//
// Created by Alex Glushko on 01.04.2020.
//

#ifndef KDZ_ARCHIVER_SHANNONFANO_H
#define KDZ_ARCHIVER_SHANNONFANO_H

#include <string>
#include <map>
#include <iterator>
#include <vector>

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
    std::vector<std::string> code_words;

    /**
     * build code from chances map
     * and write code in code map
     * @param left ???
     * @param right ???
     * @param current_code
     */
    void code_builder(int left, int right, std::string current_code);

    /**
     * Find median of chances map
     * @param left
     * @param right
     * @return median
     */
    int find_median(int left, int right);

    /**
     * Fill chances map
     * @param path to file
     */
    void chances_add(ReadWrite read_write);

}; // class ShannonFano

} // namespace archiver
#endif //KDZ_ARCHIVER_SHANNONFANO_H
