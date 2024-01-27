// cd '/workspace/인공뉴런/Perceptron/CPP'
// g++ -std=c++11 -o getData_Test getData_Test.cpp
// ./getData_Test

#define CATCH_CONFIG_MAIN
#include "../../../CPP Unit Test/catch.hpp"

#include "getData.h"

float Rounding(float input, int point) {
    int dec = pow(10, point);
    float sub = input * dec;
    sub = floor(sub);
    return sub / dec;
}

TEST_CASE("Normal Distribution Array Class", "[Normal_Distribution_Array_Class]") {
    // Arrange
    int seed = 1;
    IRandomeArray<100>* randomArrayPtr = new Normal_Distribution_Array_Class<100>(seed);

    // Act
    std::array<float, 100> normalArray = randomArrayPtr->getData();

    // Assert
    REQUIRE(Rounding(normalArray[0],4) == -0.0141f);
    REQUIRE(Rounding(normalArray[50],4) == -0.0054f);
    REQUIRE(Rounding(normalArray[99],4) == -0.0089f);
}

TEST_CASE("Normal Distribution Vector Class", "[Normal_Distribution_Vector_Class]") {
    // Arrange
    int seed = 1;
    int size = 100;
    IRandomeVector* randomVectorPtr = new Normal_Distribution_Vector_Class(size, seed);

    // Act
    std::vector<float> normalVector = randomVectorPtr->getData();

    // Assert
    REQUIRE(Rounding(normalVector[0],4) == -0.0141f);
    REQUIRE(Rounding(normalVector[50],4) == -0.0054f);
    REQUIRE(Rounding(normalVector[99],4) == -0.0089f);
}

TEST_CASE("Uniform Distribution Array Class", "[Uniform_Distribution_Array_Class]") {
    // Arrange
    int seed = 1;
    IRandomeArray<100>* randomArrayPtr = new Uniform_Distribution_Array_Class<100>(seed);

    // Act
    std::array<float, 100> normalArray = randomArrayPtr->getData();

    // Assert
    REQUIRE(Rounding(normalArray[0],4) == 0.9971f);
    REQUIRE(Rounding(normalArray[50],4) == 0.0836f);
    REQUIRE(Rounding(normalArray[99],4) == 0.1529f);
}

TEST_CASE("Uniform Distribution Vector Class", "[Uniform_Distribution_Vector_Class]") {
    // Arrange
    int seed = 1;
    int size = 100;
    IRandomeVector* randomVectorPtr = new Uniform_Distribution_Vector_Class(size, seed);

    // Act
    std::vector<float> normalVector = randomVectorPtr->getData();

    // Assert
    REQUIRE(Rounding(normalVector[0],4) == 0.9971f);
    REQUIRE(Rounding(normalVector[50],4) == 0.0836f);
    REQUIRE(Rounding(normalVector[99],4) == 0.1529f);
}

TEST_CASE("Normal Distribution Array Class Set Value", "[Normal_Distribution_Array_Class_Value]") {
    // Arrange
    int seed = 2;
    IRandomeArray<100>* randomArrayPtr = new Normal_Distribution_Array_Class<100>(seed);

    // Act
    std::array<float, 100> normalArray = randomArrayPtr->getData();

    // Assert
    REQUIRE(Rounding(normalArray[0],4) == 0.0066f);
    REQUIRE(Rounding(normalArray[50],4) == 0.0103f);
    REQUIRE(Rounding(normalArray[99],4) == -0.004f);
}

TEST_CASE("Normal Distribution Vector Class Set Value", "[Normal_Distribution_Vector_Class_Value]") {
    // Arrange
    int seed = 3;
    int size = 100;
    IRandomeVector* randomVectorPtr = new Normal_Distribution_Vector_Class(size, seed, 0.1, 0.02);

    // Act
    std::vector<float> normalVector = randomVectorPtr->getData();

    // Assert
    REQUIRE(Rounding(normalVector[0],4) == 0.0798f);
    REQUIRE(Rounding(normalVector[50],4) == 0.1031f);
    REQUIRE(Rounding(normalVector[99],4) == 0.0811f);
}

TEST_CASE("Uniform Distribution Array Class Set Value", "[Uniform_Distribution_Array_Class_Value]") {
    // Arrange
    int seed = 2;
    IRandomeArray<100>* randomArrayPtr = new Uniform_Distribution_Array_Class<100>(seed, -1.0, 1.0);

    // Act
    std::array<float, 100> normalArray = randomArrayPtr->getData();

    // Assert
    REQUIRE(Rounding(normalArray[0],4) == -0.6299f);
    REQUIRE(Rounding(normalArray[50],4) == 0.6282f);
    REQUIRE(Rounding(normalArray[99],4) == 0.9365f);
}

TEST_CASE("Uniform Distribution Vector Set Value", "[Uniform_Distribution_Vector_Value]") {
    // Arrange
    int seed = 3;
    int size = 100;
    IRandomeVector* randomVectorPtr = new Uniform_Distribution_Vector_Class(size, seed, -1.0, 1.0);

    // Act
    std::vector<float> normalVector = randomVectorPtr->getData();

    // Assert
    REQUIRE(Rounding(normalVector[0],4) == -0.8586f);
    REQUIRE(Rounding(normalVector[50],4) == 0.5211f);
    REQUIRE(Rounding(normalVector[99],4) == 0.656f);
}