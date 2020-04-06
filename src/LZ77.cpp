//
// Created by Alex Glushko on 06.04.2020.
//

#include <cmath>
#include <vector>

#include "LZ77.h"
#include "ReadWrite.h"

namespace archiver
{
    const int LONG_SIZE = 64;

    void LZ77::read_triplet(int symbol, std::vector<bit> &triplet, int len)
    {
        std::bitset<LONG_SIZE> set(symbol);
        for (int j = len - 1; j >= 0; --j)
        {
            triplet.emplace_back(set[j]);
        }
    }

    void LZ77::pack_file(const std::string &path, int dictionary_len, int buffer_len)
    {
        int offset_len = std::log2(dictionary_len);
        int maxLen_len = std::log2(buffer_len);

        ReadWrite read_write(path, path + ".lz77" + std::to_string((dictionary_len + buffer_len) / 1024));

        std::vector<std::vector<bit>> triplets;

        std::vector<byte> str;
        byte buf;
        bool flag = false;

        // Male buffer
        for (int i = 0; i < buffer_len; ++i)
        {
            if(read_write.read_byte(buf))
            {
                str.emplace(str.begin(), buf);
            }
            else
            {
                if(flag)
                {
                    str.emplace(str.begin(), buf);
                }
                else
                {
                    str.emplace(str.begin(), 3);
                    flag = true;
                }
            }
        }

        while (true)
        {
            // Initializing
            int best_offset = 0;
            int max_len = 0;
            byte max_char = str[buffer_len - 1];

            // Find best len for offset
            for (int i = buffer_len; i < str.size(); ++i)
            {
                int len = 0;
                while ((len < buffer_len) &&
                       str[buffer_len - 1 - len] != 0 &&
                       str[i - len] == str[buffer_len - 1 - len])
                    ++len;
                if(len >= max_len && len != 0)
                {
                    max_len = len;
                    best_offset = i - buffer_len + 1;
                    max_char = str[buffer_len - 1 - len];
                }
            }

            // Write triplet
            std::vector<bit> triplet;
            read_triplet(best_offset, triplet, offset_len);
            read_triplet(max_len, triplet, maxLen_len);
            read_triplet(max_char, triplet, 8);
            triplets.push_back(triplet);


            // Move window
            while (max_len + 1 != 0)
            {
                --max_len;
                if(read_write.read_byte(buf))
                {
                    if(str.size() == dictionary_len + buffer_len)
                    {
                        str.pop_back();
                        str.emplace(str.begin(), buf);
                    }
                    else
                    {
                        str.emplace(str.begin(), buf);
                    }
                }
                else
                {
                    if(str.size() == dictionary_len + buffer_len)
                    {
                        if (flag)
                        {
                            str.pop_back();
                            str.emplace(str.begin(), buf);
                        } else
                        {
                            str.pop_back();
                            str.emplace(str.begin(), 3);
                            flag = true;
                        }
                    }
                    else
                    {
                        if (flag)
                        {
                            str.emplace(str.begin(), buf);
                        } else
                        {
                            str.emplace(str.begin(), 3);
                            flag = true;
                        }
                    }

                    if(str[buffer_len - 1] == 0)
                    {
                        break;
                    }
                }
            }

            if(str[buffer_len - 1] == 0)
            {
                break;
            }
        }

        // Write down triplets
        std::bitset<8> set;
        int index = 7;

        for (const auto& triplet : triplets)
        {
            for (auto bit : triplet)
            {
                set[index] = bit[0];
                --index;

                if(index == -1)
                {
                    read_write.write_bitset(set);
                    index = 7;
                    set.reset();
                }
            }
        }

        if(index != 7)
            read_write.write_bitset(set);
    }

    int LZ77::write_triplet(std::vector<bit> &triplet, int len)
    {
        std::bitset<LONG_SIZE> set(0);
        for (int i = len - 1; i >= 0; --i)
        {
            set[i] = triplet[0][0];
            triplet.erase(triplet.begin());
        }

        return set.to_ulong();
    }

    void LZ77::unpack_file(const std::string &path, int dictionary_len, int buffer_len)
    {
        if(path.substr(path.length() - 6, 6) != ".lz775" &&
           path.substr(path.length() - 7, 7) != ".lz7710" &&
           path.substr(path.length() - 7, 7) != ".lz7720")
            throw std::invalid_argument("Invalid file extension");

        std::string out_path;

        if((dictionary_len + buffer_len) / 1024 == 5)
        {
            out_path = path.substr(0, path.size() - 6) + ".unlz775";
        }
        else
        {
            out_path = path.substr(0, path.size() - 7);
            out_path += ((dictionary_len + buffer_len) / 1024) == 10 ? ".unlz7710" : ".unlz7720";
        }

        ReadWrite read_write(path, out_path);

        int offset_len = std::log2(dictionary_len);
        int maxLen_len = std::log2(buffer_len);

        int offset = 0;
        int len = 0;
        char symbol = 0;

        std::vector<byte> str;

        int triplet_len = offset_len + maxLen_len + 8;

        std::vector<bit> triplet;

        byte buf;
        while (read_write.read_byte(buf))
        {
            std::bitset<8> buf_set(buf);

            for (int i = 7; i >= 0; --i)
            {
                triplet.emplace_back(buf_set[i]);

                if(triplet_len == triplet.size())
                {
                    offset = write_triplet(triplet, offset_len);
                    len = write_triplet(triplet, maxLen_len);
                    symbol = (byte)write_triplet(triplet, 8);

                    int str_len = str.size();
                    for (int j = 0; j < len; ++j)
                    {
                        str.push_back(str[str_len - offset + j]);
                    }

                    if(symbol == 3)
                        break;

                    str.push_back(symbol);

                    while (str.size() > dictionary_len + buffer_len)
                    {
                        read_write.write_byte(str[0]);
                        str.erase(str.begin());
                    }

                    triplet.clear();


                }
            }

            if(symbol == 3)
                break;
        }
        for (auto byte : str)
        {
            read_write.write_byte(byte);
        }
    }
}