//
// Created by Alex Glushko on 03.04.2020.
//

#include <vector>
#include "ReadWrite.h"

namespace archiver
{

ReadWrite::ReadWrite(const std::string& in, const std::string& out)
{
    if(!in.empty())
    {
        fin.open(in, std::ios::in);

        if (!fin.is_open())
        {
            throw std::invalid_argument("Invalid in path");
        }

        path_in = in;
    }

    if(!out.empty())
    {
        fout.open(out, std::ios::out);

        if (!fout.is_open())
        {
            throw std::invalid_argument("Invalid out path");
        }
    }
}

ReadWrite::~ReadWrite()
{
    if(fin.is_open())
        fin.close();

    if(fout.is_open())
        fout.close();
}

bool ReadWrite::read_byte(byte &symbol)
{
    if(fin.is_open())
    {
        char ch;
        fin.get(ch);
        symbol = ch;
        return !fin.eof();
    }
    else
    {
        throw std::invalid_argument("No input stream was initialized");
    }
}

void ReadWrite::write_byte(byte param)
{
    if (fout.is_open())
    {
        fout << param;
    }
    else
    {
        throw std::invalid_argument("No output stream was initialized");
    }
}

void ReadWrite::write_int(int param)
{
    if(fout.is_open())
    {
        fout << param;
    }
    else
    {
        throw std::invalid_argument("No output stream was initialized");
    }
}

void ReadWrite::write_bitset(const std::bitset<8> &param)
{
    if(fout.is_open())
    {
        fout << (char)param.to_ulong();
    }
    else
    {
        throw std::invalid_argument("No output stream was initialized");
    }
}

void ReadWrite::reset_reader()
{
    fin.close();
    fin.open(path_in);
}

} // namespace archiver