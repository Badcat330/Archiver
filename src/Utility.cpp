//
// Created by Alex Glushko on 05.04.2020.
//

#include <vector>
#include <string>
#include <cmath>

#include "Utility.h"
#include "ReadWrite.h"

namespace archiver
{

    const int BYTE_SIZE = 256;

    void Utility::entropy_file(std::string &path)
    {
        ReadWrite read_write(path, path + ".csv");
        std::vector<int> symbols(256);

        double count = 0;
        double entropy = 0;

        byte symbol;
        while (read_write.read_byte(symbol))
        {
            ++count;
            symbols[symbol] += 1;
        }

        std::string buf;
        buf += "symbol,frequency\n";
        read_write.write<std::string>(buf);

        for (int i = 0; i < BYTE_SIZE; ++i)
        {
            double frequency = symbols[i] / count;
            buf = "";
            buf += std::to_string(i);
            buf += ",";
            buf += std::to_string(std::floor(frequency * 100.0 + 0.5) / 100.0) + "\n";
            read_write.write<std::string>(buf);

            if(frequency != 0)
                entropy += frequency + log2(frequency);
        }

        buf = "entropy," + std::to_string(-entropy);
        read_write.write<std::string>(buf);
    }

    void Utility::entropy_dir(std::string &path)
    {
        std::vector<std::string> table(258);

        table[0] += "file/symbol";
        for (int j = 1; j < 257; ++j)
        {
            table[j] += std::to_string(j);
        }
        table[table.size() - 1] += "entropy";

        for (const auto & entry : std::__fs::filesystem::directory_iterator(path))
        {
            std::string name = entry.path().filename();
            if(name[0] != '.' &&
               name.substr(name.length() - 5, 5) != ".shan" &&
               name.substr(name.length() - 7, 7) != ".unshan" &&
               name.substr(name.length() - 4, 4) != ".csv")//ToDo:: Add check for others types of files
            {
                ReadWrite read_write(entry.path());
                std::vector<int> symbols(256);

                double count = 0;
                double entropy = 0;

                byte symbol;
                while (read_write.read_byte(symbol))
                {
                    ++count;
                    symbols[symbol] += 1;
                }

                table[0] += "," + entry.path().filename().string();

                for (int i = 0; i < BYTE_SIZE; ++i)
                {
                    double frequency = symbols[i] / count;

                    table[i + 1] += "," + std::to_string(frequency);

                    if(frequency != 0)
                        entropy += frequency + log2(frequency);
                }

                table[table.size() - 1] += "," + std::to_string(-entropy);
            }
        }

        ReadWrite read_write("", path + "entropy.csv");

        for (const auto & j : table)
        {
            read_write.write<std::string>(j + "\n");
        }
    }

    size_t Utility::size_count(const std::string path)
    {
        std::fstream file;
        file.open(path, std::ios::in);
        size_t count = 0;
        if(file.is_open())
        {
            while (!file.eof())
            {
                file.get();
                ++count;
            }
            --count;

            file.close();

        }
        return count;
    }

    void Utility::aspect_ratio(const std::string &path, const std::string &type)
    {
        ReadWrite read_write("", path + "aspect_ratio" + type +".csv");

        for (const auto & entry : std::__fs::filesystem::directory_iterator(path))
        {
            std::string name = entry.path().filename();

            if(name[0] != '.' &&
               name.substr(name.length() - 5, 5) != ".shan" &&
               name.substr(name.length() - 7, 7) != ".unshan" &&
               name.substr(name.length() - 4, 4) != ".csv")//ToDo:: Add check for others types of files
            {
                size_t file_size = size_count(entry.path());
                size_t pack_size = size_count(entry.path().string() + type);
                if(pack_size != 0)
                {
                    double ratio = (double)pack_size / (double)file_size;
                    read_write.write<std::string>(name + "," +
                                                  std::to_string(file_size) + "," +
                                                  std::to_string(pack_size) + "," +
                                                  std::to_string(ratio) + "\n");
                }
            }
        }
    }
}
