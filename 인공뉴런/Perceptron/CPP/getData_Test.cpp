// cd '/workspace/�ΰ�����/Perceptron/CPP'
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
    REQUIRE(Rounding(normalArray[0],4) == -0.0055f);
    REQUIRE(Rounding(normalArray[50],4) == 0.0311f);
    REQUIRE(Rounding(normalArray[99],4) == -0.0024f);
}

TEST_CASE("Normal Distribution Vector Class", "[Normal_Distribution_Vector_Class]") {
    // Arrange
    int seed = 1;
    int size = 100;
    IRandomeVector* randomVectorPtr = new Normal_Distribution_Vector_Class(size, seed);

    // Act
    std::vector<float> normalVector = randomVectorPtr->getData();

    // Assert
    REQUIRE(Rounding(normalVector[0],4) == -0.0055f);
    REQUIRE(Rounding(normalVector[50],4) == 0.0311f);
    REQUIRE(Rounding(normalVector[99],4) == -0.0024f);
}

TEST_CASE("Uniform Distribution Array Class", "[Uniform_Distribution_Array_Class]") {
    // Arrange
    int seed = 1;
    IRandomeArray<100>* randomArrayPtr = new Uniform_Distribution_Array_Class<100>(seed);

    // Act
    std::array<float, 100> normalArray = randomArrayPtr->getData();

    // Assert
    REQUIRE(Rounding(normalArray[0],4) == 0.1315f);
    REQUIRE(Rounding(normalArray[50],4) == 0.4679f);
    REQUIRE(Rounding(normalArray[99],4) == 0.8246f);
}

TEST_CASE("Uniform Distribution Vector Class", "[Uniform_Distribution_Vector_Class]") {
    // Arrange
    int seed = 1;
    int size = 100;
    IRandomeVector* randomVectorPtr = new Uniform_Distribution_Vector_Class(size, seed);

    // Act
    std::vector<float> normalVector = randomVectorPtr->getData();

    // Assert
    REQUIRE(Rounding(normalVector[0],4) == 0.1315f);
    REQUIRE(Rounding(normalVector[50],4) == 0.4679f);
    REQUIRE(Rounding(normalVector[99],4) == 0.8246f);
}

TEST_CASE("Normal Distribution Array Class Set Value", "[Normal_Distribution_Array_Class_Value]") {
    // Arrange
    int seed = 2;
    IRandomeArray<100>* randomArrayPtr = new Normal_Distribution_Array_Class<100>(seed);

    // Act
    std::array<float, 100> normalArray = randomArrayPtr->getData();

    // Assert
    REQUIRE(Rounding(normalArray[0],4) == -0.0003f);
    REQUIRE(Rounding(normalArray[50],4) == 0.0105f);
    REQUIRE(Rounding(normalArray[99],4) == 0.0047f);
}

TEST_CASE("Normal Distribution Vector Class Set Value", "[Normal_Distribution_Vector_Class_Value]") {
    // Arrange
    int seed = 3;
    int size = 100;
    IRandomeVector* randomVectorPtr = new Normal_Distribution_Vector_Class(size, seed, 0.1, 0.02);

    // Act
    std::vector<float> normalVector = randomVectorPtr->getData();

    // Assert
    REQUIRE(Rounding(normalVector[0],4) == 0.1036f);
    REQUIRE(Rounding(normalVector[50],4) == 0.1257f);
    REQUIRE(Rounding(normalVector[99],4) == 0.083f);
}

TEST_CASE("Uniform Distribution Array Class Set Value", "[Uniform_Distribution_Array_Class_Value]") {
    // Arrange
    int seed = 2;
    IRandomeArray<100>* randomArrayPtr = new Uniform_Distribution_Array_Class<100>(seed, -1.0, 1.0);

    // Act
    std::array<float, 100> normalArray = randomArrayPtr->getData();

    // Assert
    REQUIRE(Rounding(normalArray[0],4) == -0.4739f);
    REQUIRE(Rounding(normalArray[50],4) == 0.8716f);
    REQUIRE(Rounding(normalArray[99],4) == 0.2987f);
}

TEST_CASE("Uniform Distribution Vector Set Value", "[Uniform_Distribution_Vector_Value]") {
    // Arrange
    int seed = 3;
    int size = 100;
    IRandomeVector* randomVectorPtr = new Uniform_Distribution_Vector_Class(size, seed, -1.0, 1.0);

    // Act
    std::vector<float> normalVector = randomVectorPtr->getData();

    // Assert
    REQUIRE(Rounding(normalVector[0],4) == -0.2108f);
    REQUIRE(Rounding(normalVector[50],4) == -0.1925f);
    REQUIRE(Rounding(normalVector[99],4) == -0.0519f);
}