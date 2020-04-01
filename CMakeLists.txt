cmake_minimum_required(VERSION 3.15)
project(KDZ_archiver)

set(CMAKE_CXX_STANDARD 11)

add_executable(KDZ_archiver main.cpp LZ77.h ReadWrite.h ShannonFano.h Timer.h EntropyCalculator.h)