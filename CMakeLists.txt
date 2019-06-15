cmake_minimum_required (VERSION 3.0)
project (FFNeuralNet)

find_package(Eigen3 3.3 REQUIRED NO_MODULE)

add_library(FFNeuralNetLib src/BackPropagation.cpp src/FFNetCommon.cpp src/LayeredFeedForwardNeuralNet.cpp src/UnaryExpressionParser.cpp)
target_link_libraries (FFNeuralNetLib Eigen3::Eigen)


find_package(Catch2 REQUIRED)

add_executable(FFNeuralNetTests test/FFNeuralNetTests.cpp)
include_directories(FFNeuralNetTests src)
target_link_libraries (FFNeuralNetTests FFNeuralNetLib Catch2::Catch2)
