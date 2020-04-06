//
// Created by Alex Glushko on 01.04.2020.
//

#ifndef KDZ_ARCHIVER_LZ77_H
#define KDZ_ARCHIVER_LZ77_H

#include <string>
#include <bitset>

typedef std::bitset<1> bit;

namespace archiver
{

class LZ77
{

public:
    /**
     * Method for packing all files in dir
     * @param path to dir
     * @param dictionary_len length of the dictionary in Kb
     * @param buffer_len length of preview buffer in Kb
     */
    void pack_dir(std::string& path, int dictionary_len, int buffer_len);

    /**
     * Method for unpacking all files in dir
     * @param path to
     * @param dictionary_len length of the dictionary in Kb
     * @param buffer_len length of preview buffer in Kb
     */
    void unpack_dir(std::string& path, int dictionary_len, int buffer_len);

    /**
     * Method for packing file
     * @param path to file
     * @param dictionary_len length of the dictionary in Kb
     * @param buffer_len length of preview buffer in Kb
     */
    void pack_file(const std::string &path, int dictionary_len, int buffer_len);

    /**
     * Method for unpacking file
     * @param path to file
     * @param dictionary_len length of the dictionary in Kb
     * @param buffer_len length of preview buffer in Kb
     */
    void unpack_file(const std::string &path, int dictionary_len, int buffer_len);

private:
    void read_triplet(int symbol, std::vector<bit> &triplet, int len);

    int write_triplet(std::vector<bit> &triplet, int len);

}; // class LZ77
} //namespace archiver

#endif //KDZ_ARCHIVER_LZ77_H
