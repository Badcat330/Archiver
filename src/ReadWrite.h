//
// Created by Alex Glushko on 01.04.2020.
//

#ifndef KDZ_ARCHIVER_READWRITE_H
#define KDZ_ARCHIVER_READWRITE_H

#include <fstream>


namespace archiver
{

typedef unsigned char byte;
typedef std::vector<std::bitset<1>> bit_code;
typedef std::bitset<1> bit;

class ReadWrite
{

public:

    /**
     * Constructor from file path
     * @param in to reading file
     * @param path to writing file
     */
    ReadWrite(const std::string& in, const std::string& out = "");

    /**
     * Destructor
     * Free streams
     */
    ~ReadWrite();

    /**
     * Function for reading byte from stream
     * @return read byte
     */
    bool read_byte(byte &symbol);

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

    /**
     * Function for writing string into stream
     * @param param which we should write
     */
    void write_bitset(const std::bitset<8> &param);

    /**
     * Put stream input in to begin
     */
    void reset_reader();

private:
    std::string path_in;
    std::fstream fin;
    std::fstream fout;

}; // class ReadWrite

} // namespace archiver

#endif //KDZ_ARCHIVER_READWRITE_H
