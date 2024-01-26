#include "getData.h"

class IPerceptron_Vector {
public:
    virtual void Initialize(std::vector<std::vector<float>> input_data) = 0;
    virtual void fit(std::vector<std::vector<float>> input_data, std::vector<float> result_data) = 0;
    virtual int Predict(std::vector<float> input_data) = 0;
};

template <int N, int Epoch, int Length>
class IPerceptron_Array {
public:
    virtual void Initialize(std::array<std::array<float, Length>, N> input_data) = 0;
    virtual void fit(std::array<std::array<float, Length>, N> input_data, std::array<float, N> result_data) = 0;
    virtual int Predict(std::array<float, Length> input_data) = 0;
};

// Perceptron
class Perceptron_Vector : public IPerceptron {
private :
    int eta;
    int epoch;
    int random_state;
    std::vector<float> bias;
    std::vector<float> weight;
    IRandomeVector* randomVectorPtr;

public :
    std::vector<int> errors;

    Perceptron_Vector(IRandomeVector* randomVectorPtr, int eta = 0.01, int epoch = 50, int random_state = 1)
     : eta(eta), epoch(epoch), random_state(random_state), randomVectorPtr(randomVectorPtr) {
    }

    void Initialize(std::vector<std::vector<float>> input_data) override {
        bias(epoch, 0.0f);
        randomVectorPtr.size = input_data[0].size(); // 행 input_data.size(), 열 input_data[0].size()
        weight = randomVectorPtr->getData();
    }

    void fit(std::vector<std::vector<float>> input_data, std::vector<float> result_data) override {
        Initialize(input_data);
        for(int e = 0; e < epoch; e++) {
            int error = 0;
            for(int i = 0; i < input_data.size(); i++) {
                float delta = eta * (result_data[i] - Predict(input_data[i]));
                for(int l = 0; l < input_data[0].size(); l++)
                    weight[l] += input_data[i][l] * delta;
                bias += delta;
                error += int(delta != 0.0);
            }
            errors[e] = error;
            std::cout << "-----epoch (" << e << "/" << epoch << ")-------- error:" << error << std::endl;
        }
    }

    int Predict(std::vector<float> input_data) override {
        result (Caculator_Perceptron(input_data) >= 0.0f)? 1 : 0;
    }

    float Caculator_Perceptron(std::vector<float> input_data) {
        return Multiplex_Array(input_data) + bias;
    }

    float Multiplex_Array(std::vector<float> input_data) {
        float result = 0.0f;
        for (int i = 0; i < input_data[0].size(); i++)
            result += input_data[i] * weight[i];
        return result;
    }
};

template <int N, int Epoch, int Length>
class Perceptron_Array : public IPerceptron<N> {
private :
    int eta;
    int random_state;
    float bias;
    std::array<float, Length> weight;
    IRandomeArray<N>* randomArrayPtr;

public :
    std::array<int, Epoch> errors;

    Perceptron_Array(IRandomeArray<N>* randomArrayPtr, int eta = 0.01, int random_state = 1)
     : eta(eta), random_state(random_state), randomArrayPtr(randomArrayPtr) {
    }

    void Initialize(std::array<std::array<float, Length>, N> input_data) {
        bias = 0.0f;
        randomArrayPtr.size = Length;
        weight = randomArrayPtr->getData();
    }
    
    void fit(std::array<std::array<float, Length>, N> input_data, std::array<float, N> result_data) {
        Initialize(input_data);
        for(int e = 0; e < Epoch; e++) {
            int error = 0.0f;
            for(int i = 0; i < N; i++) {
                float delta = eta * (result_data[i] - Predict(input_data[i]));
                for(int l = 0; l < Length; l++)
                    weight[l] += input_data[i][l] * delta;
                bias += delta;
                error += int(delta != 0.0);
            }
            errors[e] = error;
            std::cout << "-----epoch (" << e << "/" << Epoch << ")-------- error:" << error << std::endl;
        }
    }

    int Predict(std::array<float, Length> input_data) {
        result (Caculator_Perceptron(input_data) >= 0.0f)? 1 : 0;
    }

    float Caculator_Perceptron(std::array<float, Length> input_data) {
        return Multiplex_Array(input_data) + bias;
    }

    float Multiplex_Array(std::array<float, Length> input_data) {
        float result = 0.0f;
        for (int i = 0; i < Length; i++)
            result += input_data[i] * weight[i];
        return result;
    }
};