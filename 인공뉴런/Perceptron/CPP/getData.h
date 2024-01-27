#include <iostream>
#include <vector>
#include <array>
#include <sstream>
#include <string>
#include <algorithm>
#include <random>

// Interface
class IRandomeVector {
public:
    int size;
    virtual std::vector<float> getData() = 0;
};

template <int N>
class IRandomeArray {
public:
    virtual std::array<float, N> getData() = 0;
};

// Class
class Normal_Distribution_Vector_Class : public IRandomeVector {
private:
    int seed;
public:
    float loc;
    float scale;
    
    Normal_Distribution_Vector_Class(int size = 100, int seed = 1, float loc = 0.0, float scale = 0.01) : seed(seed), loc(loc), scale(scale) {
        this->size = size;
    }
    Normal_Distribution_Vector_Class(int size = 100, float loc = 0.0, float scale = 0.01, int seed = 1) : seed(seed), loc(loc), scale(scale) {
        this->size = size;    
    }

    std::vector<float> getData() override {
        std::vector<float> result;
        std::random_device rd;
        std::mt19937 gen(seed);
        std::normal_distribution<double> dist(loc, scale);
        double randomNumber;

        for(int repeat_num = 0; repeat_num < size; repeat_num++){
            randomNumber = dist(gen);
            result.push_back(randomNumber);
        }

        return result;
    }
};

class Uniform_Distribution_Vector_Class : public IRandomeVector {
private:
    int seed;
public:
    float min = 0.0;
    float max = 0.1;
    
    Uniform_Distribution_Vector_Class(int size = 100, float min = 0.0, float max = 1.0, int seed = 1) : seed(seed), min(min), max(max) {
        this->size = size;
     }
    Uniform_Distribution_Vector_Class(int size = 100, int seed = 1, float min = 0.0, float max = 1.0) : seed(seed), min(min), max(max) {
        this->size = size;
     }

    std::vector<float> getData() override {
        std::vector<float> result;
        std::default_random_engine engine(seed);
        std::uniform_real_distribution<double> uniformDist(min, max);
        double randomNumber;

        for(int repeat_num = 0; repeat_num < size; repeat_num++){
            randomNumber = uniformDist(engine);
            result.push_back(randomNumber);
        }

        return result;
    }
};

template <int N>
class Normal_Distribution_Array_Class : public IRandomeArray<N> {
private:
    int seed;
public:
    float loc;
    float scale;
    
    Normal_Distribution_Array_Class(int seed = 1, float loc = 0.0, float scale = 0.01) : seed(seed), loc(loc), scale(scale) { }
    Normal_Distribution_Array_Class(float loc = 0.0, float scale = 0.01, int seed = 1) : seed(seed), loc(loc), scale(scale) { }

    std::array<float, N> getData() override {
        std::array<float, N> result;
        std::random_device rd;
        std::mt19937 gen(seed);
        std::normal_distribution<double> dist(loc, scale);
        double randomNumber;

        for(int repeat_num = 0; repeat_num < N; repeat_num++){
            randomNumber = dist(gen);
            result[repeat_num] = randomNumber;
        }

        return result;
    }
};

template <int N>
class Uniform_Distribution_Array_Class : public IRandomeArray<N> {
private:
    int seed;
public:
    float min = 0.0;
    float max = 0.1;
    
    Uniform_Distribution_Array_Class(float min = 0.0, float max = 1.0, int seed = 1) : seed(seed), min(min), max(max) { }
    Uniform_Distribution_Array_Class(int seed = 1, float min = 0.0, float max = 1.0) : seed(seed), min(min), max(max) { }

    std::array<float, N> getData() override {
        std::array<float, N> result;
        std::default_random_engine engine(seed);
        std::uniform_real_distribution<double> uniformDist(min, max);
        double randomNumber;

        for(int repeat_num = 0; repeat_num < N; repeat_num++){
            randomNumber = uniformDist(engine);
            result[repeat_num] = randomNumber;
        }

        return result;
    }
};