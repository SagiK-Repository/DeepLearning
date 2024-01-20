// cd '/workspace/인공뉴런/Perceptron/CPP'
// g++ -std=c++11 -o getData_Test getData_Test.cpp
// ./getData_Test

#define CATCH_CONFIG_MAIN
#include "/workspace/CPP Unit Test/catch.hpp"

#include "Perceptron.h"

TEST_CASE("Perceptron", "[Perceptron]") {
    // Arrange
    Normal_Distribution getData;
    Perceptron(0.1, 10, &getData);

    // Act
    Perceptron.fit(X, y);

    // Assert
    // REQUIRE(Rounding(normalArray[0],4) == -0.0055f);
}