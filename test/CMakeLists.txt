include_directories(../src)

include_directories(.)

add_executable(tests 
    # utility tests
    ReadWriteTest.cpp
    UtilityTest.cpp
    TimetTest.cpp
    # archivers tests
    ShannonFanoTest.cpp
    LZ77Test.cpp
    # utility sources
    ../src/Utility.h
    ../src/Utility.cpp
    ../src/Timer.h
    ../src/Timer.cpp
    ../src/ReadWrite.h
    ../src/ReadWrite.cpp
    # archivers sources
    ../src/LZ77.h
    ../src/LZ77.cpp
    ../src/ShannonFano.h
    ../src/ShannonFano.cpp
    # gtest sources
    gtest/gtest-all.cc
    gtest/gtest_main.cc )

# add pthread for unix systems
if (UNIX)
    target_link_libraries(tests pthread)
endif ()