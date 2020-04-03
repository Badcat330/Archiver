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
     * Method for packing file from current path
     * @param path to dir
     */
    void pack(std::string path);

    /**
     * Method for packing all files in dir
     * @param path to dir
     */
    void packDir(std::string path);


}; // class LZ77
} //namespace archiver

#endif //KDZ_ARCHIVER_LZ77_H
