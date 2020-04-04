include_directories(../src)

include_directories(.)

add_executable(tests 
    # utility tests
    ReadWriteTest.cpp
    # archivers tests
    ShannonFanoTest.cpp
    # utility sources
    ../src/EntropyCalculator.h
    ../src/Timer.h
    ../src/ReadWrite.h
    ../src/ReadWrite.cpp
    # archivers sources
    ../src/LZ77.h
    ../src/ShannonFano.h
    ../src/ShannonFano.cpp
    # gtest sources
    gtest/gtest-all.cc
    gtest/gtest_main.cc
)

# add pthread for unix systems
if (UNIX)
    target_link_libraries(tests pthread)
endif ()