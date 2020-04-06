//
// Created by Alex Glushko on 01.04.2020.
//

#ifndef KDZ_ARCHIVER_LZ77_H
#define KDZ_ARCHIVER_LZ77_H

#include <string>

namespace archiver
{

class LZ777
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
    void pack_file(const std::string &path);

    /**
     * Method for unpacking file
     * @param path to file
     */
    void unpack_file(const std::string &path);


}; // class LZ77
} //namespace archiver

#endif //KDZ_ARCHIVER_LZ77_H
