//
// Created by Alex Glushko on 01.04.2020.
//

#ifndef KDZ_ARCHIVER_SHANNONFANO_H
#define KDZ_ARCHIVER_SHANNONFANO_H

#include <string>
#include <map>

typedef unsigned char byte;

namespace archiver
{

class ShannonFano
{

public:

    /**
     * Method for packing file from current path
     * @param dir path
     */
    void pack(std::string& path);

    /**
     * Method for packing all files in dir
     * @param dir path
     */
    void unpack(std::string& path);

private:

    std::map<byte, int> chances;
    std::map<byte, std::string> code_words;

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

}; // class ShannonFano

} // namespace archiver
#endif //KDZ_ARCHIVER_SHANNONFANO_H
