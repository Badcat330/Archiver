//
// Created by Alex Glushko on 03.04.2020.
//

#include "ReadWrite.h"

namespace archiver
{

ReadWrite::ReadWrite(std::string in, std::string out)
{
    fin.open(in, std::ios::in);

    if(!fin.is_open())
    {
        throw std::exception();
    }

    fout.open(out, std::ios::out);

    if(!fout.is_open())
    {
        throw std::exception();
    }
}

ReadWrite::~ReadWrite()
{
    fin.close();
    fout.close();
}

byte ReadWrite::read_byte()
{
    byte new_byte;
    fin >> new_byte;
    return new_byte;
}

void ReadWrite::write_byte(byte param)
{
    fout << param;
}

void ReadWrite::write_int(int param)
{
    fout << param;
}

} // namespace archiver