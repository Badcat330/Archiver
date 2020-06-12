//
// Created by Alex Glushko on 01.04.2020.
//

#ifndef KDZ_ARCHIVER_UTILITY_H
#define KDZ_ARCHIVER_UTILITY_H

#include <string>

namespace archiver
{
class Utility
{
public:
    /**
     * Method which count entropy for file
     * @param path to the file
     */
    void entropy_file(std::string &path);

    /**
     * Method which count entropy in all files in dir
     * @param path to the dir
     */
    void entropy_dir(std::string &path);

    /**
     * Method which count aspect rate for current type
     * @param path to the dir with files
     * @param type of algorithm
     */
    void aspect_ratio(const std::string &path, const std::string &type);

    /**
     * Count size of file
     * @param path to file
     * @return number of bytes in file
     */
    size_t size_count(const std::string path);

};
}

#endif //KDZ_ARCHIVER_UTILITY_H
