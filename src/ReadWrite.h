//
// Created by Alex Glushko on 01.04.2020.
//

#ifndef KDZ_ARCHIVER_READWRITE_H
#define KDZ_ARCHIVER_READWRITE_H

#include <fstream>

typedef unsigned char byte;

namespace archiver
{

class ReadWrite
{

public:

    /**
     * Constructor from file path
     * @param in to reading file
     * @param path to writing file
     */
    ReadWrite(std::string in, std::string out);

    /**
     * Destructor
     * Free streams
     */
    ~ReadWrite();

    /**
     * Function for reading byte from stream
     * @return read byte
     */
    byte read_byte();

    /**
     * Function for writing byte into stream
     * @param param which we should write
     */
    void write_byte(byte param);

    /**
     * Function for writing int into stream
     * @param param which we should write
     */
    void write_int(int param);

private:

    std::fstream fin;
    std::fstream fout;

}; // class ReadWrite

} // namespace archiver

#endif //KDZ_ARCHIVER_READWRITE_H
