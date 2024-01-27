// cd '/workspace/인공뉴런/Perceptron/CPP'
// g++ -std=c++11 -o Perceptron_Test Perceptron_Test.cpp
// ./Perceptron_Test

#define CATCH_CONFIG_MAIN
#include "../../../CPP Unit Test/catch.hpp"

#include "Perceptron.h"
#include "csvReader.h"

TEST_CASE("Perceptron_Vector", "[Perceptron_Vector]") {
    // Arrange
    std::string filename = "data.csv";
    std::vector<std::vector<float>> input_data = processCSV_vector(filename);
    IRandomeVector* randomVectorPtr = new Normal_Distribution_Vector_Class(2, 1);
    IPerceptron_Vector* perceptronvector = new Perceptron_Vector(randomVectorPtr, 0.1, 10);
    std::vector<float> result_data;
    for(int i = 0; i < input_data.size(); i++)
        result_data.push_back((i >= 50)?1:0);

    // Act
    perceptronvector->fit(input_data, result_data);

    // Assert
    std::vector<float> myVector = {4.5, 1};
    REQUIRE(perceptronvector->Predict(myVector) == 0);
    myVector = { 5.0, 2 };
    REQUIRE(perceptronvector->Predict(myVector) == 0);
    myVector = { 6.0, 3 };
    REQUIRE(perceptronvector->Predict(myVector) == 0);
    myVector = { 7.0, 4 };
    REQUIRE(perceptronvector->Predict(myVector) == 0);
    myVector = { 7.0, 5 };
    REQUIRE(perceptronvector->Predict(myVector) == 0);
    myVector = { 7.0, 6 };
    REQUIRE(perceptronvector->Predict(myVector) == 0);
    myVector = { 5.0, 4 };
    REQUIRE(perceptronvector->Predict(myVector) == 0);
}

// print(ppn.predict([4.5, 1])) 0
// print(ppn.predict([5.0, 2])) 0
// print(ppn.predict([6.0, 3])) 0
// print(ppn.predict([7.0, 4])) 0
// print(ppn.predict([7.0, 5])) 1
// print(ppn.predict([7.0, 6])) 1
// print(ppn.predict([5.0, 4])) 1