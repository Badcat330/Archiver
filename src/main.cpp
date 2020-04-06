#include "ReadWrite.h"
#include "LZ77.h"

int main(int argc, char* argv[])
{
    using namespace archiver;

    LZ77 arch;

    std::string test_path1 = "../../test/test_data/archiver_test_2";

    arch.pack_file(test_path1, 8 * 1024, 2 * 1024);
    
    return 0;
}