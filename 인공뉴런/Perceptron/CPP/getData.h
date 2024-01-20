#include <iostream>
#include <vector>
#include <array>
#include <sstream>
#include <string>
#include <algorithm>
#include <random>

// Seed First
std::vector<float> Normal_Distribution_Vector(int size, int seed);

template <int N>
std::array<float, N> Normal_Distribution_Array(int seed);

std::vector<float> Uniform_Distribution_Vector(int size, int seed);

template <int N>
std::array<float, N> Uniform_Distribution_Array(int seed);

// 표준편차 데이터 획득
std::vector<float> Normal_Distribution_Vector(int size, float loc = 0.0, float scale = 0.01, int seed = 1);

template <int N>
std::array<float, N> Normal_Distribution_Array(float loc = 0.0, float scale = 0.01, int seed = 1);

// 균일분포 데이터 획득
std::vector<float> Uniform_Distribution_Vector(int size, float min = 0.0, float max = 1.0, int seed = 1);

template <int N>
std::array<float, N> Uniform_Distribution_Array(float min = 0.0, float max = 1.0, int seed = 1);


// 표준편차 데이터 획득
std::vector<float> Normal_Distribution_Vector(int size, float loc, float scale, int seed) {
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

template <int N>
std::array<float, N> Normal_Distribution_Array(float loc, float scale, int seed) {
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

// 균일분포(uniform distribution) 데이터 획득
std::vector<float> Uniform_Distribution_Vector(int size, float min, float max, int seed) {
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

template <int N>
std::array<float, N> Uniform_Distribution_Array(float min, float max, int seed) {
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

// Seed First
std::vector<float> Normal_Distribution_Vector(int size, int seed) {
    return Normal_Distribution_Vector(size, 0.0f, 0.01f, seed);
}
template <int N>
std::array<float, N> Normal_Distribution_Array(int seed) {
    return Normal_Distribution_Array<N>(0.0f, 0.01f, seed);
}
std::vector<float> Uniform_Distribution_Vector(int size, int seed) {
    return Uniform_Distribution_Vector(size, 0.0f, 1.0f, seed);
}

template <int N>
std::array<float, N> Uniform_Distribution_Array(int seed) {
    return Uniform_Distribution_Array<N>(0.0f, 1.0f, seed);
}


// Class --------------------------------------------------------------------------------

// Interface
class IRandomeVector {
public:
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
    int size;
    float loc;
    float scale;
    
    Normal_Distribution_Vector_Class(int size = 100, int seed = 1, float loc = 0.0, float scale = 0.01) : seed(seed), size(size), loc(loc), scale(scale) { }
    Normal_Distribution_Vector_Class(int size = 100, float loc = 0.0, float scale = 0.01, int seed = 1) : seed(seed), size(size), loc(loc), scale(scale) { }

    std::vector<float> getData() override {
        return Normal_Distribution_Vector(size, loc, scale, seed);
    }
};

class Uniform_Distribution_Vector_Class : public IRandomeVector {
private:
    int seed;
public:
    int size;
    float min = 0.0;
    float max = 0.1;
    
    Uniform_Distribution_Vector_Class(int size = 100, float min = 0.0, float max = 1.0, int seed = 1) : seed(seed), size(size), min(min), max(max) { }
    Uniform_Distribution_Vector_Class(int size = 100, int seed = 1, float min = 0.0, float max = 1.0) : seed(seed), size(size), min(min), max(max) { }

    std::vector<float> getData() override {
        return Uniform_Distribution_Vector(size, min, max, seed);
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
        return Normal_Distribution_Array<N>(loc, scale, seed);
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
        return Uniform_Distribution_Array<N>(min, max, seed);
    }
};
