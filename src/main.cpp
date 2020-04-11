#include "ReadWrite.h"
#include "LZ77.h"
#include "ShannonFano.h"
#include "Timer.h"
#include "Utility.h"

int main(int argc, char* argv[])
{
    using namespace archiver;

    LZ77 lz77;
    ShannonFano shan;
    Timer timer;
    Utility utility;

    std::string path = "../../data/";

    auto direcoris = std::__fs::filesystem::directory_iterator(path);

    utility.entropy_dir(path);

    std::string buf;
    for (const auto & entry : direcoris)
    {
        std::string name = entry.path().filename();
        if(name[0] != '.')
        {
            buf += name + ", ,";
            buf += std::to_string(utility.size_count(entry.path())) + ",";
            double sum = 0;
            for (int i = 0; i < 10; ++i)
            {
                timer.start();
                shan.pack_file(entry.path());
                timer.finish();
                sum += timer.result();
                timer.reset();
            }
            buf += std::to_string(int(sum / 10) / CLOCKS_PER_SEC) + "s " +
                   std::to_string(int(sum / 10) % (CLOCKS_PER_SEC / 1000)) + "ms,";

            sum = 0;
            for (int i = 0; i < 10; ++i)
            {
                timer.start();
                shan.unpack_file(entry.path().string() + ".shan");
                timer.finish();
                sum += timer.result();
                timer.reset();
            }
            buf += std::to_string(int(sum / 10) / CLOCKS_PER_SEC) + "s " +
                   std::to_string(int(sum / 10) % (CLOCKS_PER_SEC / 1000)) + "ms,";

            sum = 0;
            for (int i = 0; i < 10; ++i)
            {
                timer.start();
                lz77.pack_file(entry.path(), 4 * 1024, 1024);
                timer.finish();
                sum += timer.result();
                timer.reset();
            }
            buf += std::to_string(int(sum / 10) / CLOCKS_PER_SEC) + "s " +
                   std::to_string(int(sum / 10) % (CLOCKS_PER_SEC / 1000)) + "ms,";

            sum = 0;
            for (int i = 0; i < 10; ++i)
            {
                timer.start();
                lz77.unpack_file(entry.path().string() + ".lz775", 4 * 1024, 1024);
                timer.finish();
                sum += timer.result();
                timer.reset();
            }
            buf += std::to_string(int(sum / 10) / CLOCKS_PER_SEC) + "s " +
                   std::to_string(int(sum / 10) % (CLOCKS_PER_SEC / 1000)) + "ms,";

            sum = 0;
            for (int i = 0; i < 10; ++i)
            {
                timer.start();
                lz77.pack_file(entry.path(), 8 * 1024, 2*1024);
                timer.finish();
                sum += timer.result();
                timer.reset();
            }
            buf += std::to_string(int(sum / 10) / CLOCKS_PER_SEC) + "s " +
                   std::to_string(int(sum / 10) % (CLOCKS_PER_SEC / 1000)) + "ms,";

            sum = 0;
            for (int i = 0; i < 10; ++i)
            {
                timer.start();
                lz77.unpack_file(entry.path().string() + ".lz7710", 8 * 1024, 2*1024);
                timer.finish();
                sum += timer.result();
                timer.reset();
            }
            buf += std::to_string(int(sum / 10) / CLOCKS_PER_SEC) + "s " +
                   std::to_string(int(sum / 10) % (CLOCKS_PER_SEC / 1000)) + "ms,";

            sum = 0;
            for (int i = 0; i < 10; ++i)
            {
                timer.start();
                lz77.pack_file(entry.path(), 16 * 1024, 4*1024);
                timer.finish();
                sum += timer.result();
                timer.reset();
            }
            buf += std::to_string(int(sum / 10) / CLOCKS_PER_SEC) + "s " +
                   std::to_string(int(sum / 10) % (CLOCKS_PER_SEC / 1000)) + "ms,";

            sum = 0;
            for (int i = 0; i < 10; ++i)
            {
                timer.start();
                lz77.unpack_file(entry.path().string() + ".lz7720", 16 * 1024, 4*1024);
                timer.finish();
                sum += timer.result();
                timer.reset();
            }
            buf += std::to_string(int(sum / 10) / CLOCKS_PER_SEC) + "s " +
                   std::to_string(int(sum / 10) % (CLOCKS_PER_SEC / 1000)) + "ms \n";
        }
    }


    std::fstream fout;
    fout.open(path + "time.csv", std::ios::out);
    fout << buf;
    fout.close();

    utility.aspect_ratio(path, ".shan");
    utility.aspect_ratio(path, ".lz775");
    utility.aspect_ratio(path, ".lz7710");
    utility.aspect_ratio(path, ".lz7720");

    return 0;
}