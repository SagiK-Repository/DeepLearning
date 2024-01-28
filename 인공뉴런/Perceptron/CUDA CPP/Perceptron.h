#include <iostream>
#include <vector>
#include <cuda_runtime.h>
#include "../CPP/getData.h"

__device__ float calculatePredict(float* input_data, float* weight, float bias, int idx, int length) {
    float predict = 0.0f;
    for (int i = 0; i < length; i++)
        predict += input_data[idx * length + i] * weight[i];
    predict += bias;
    return predict >= 0.0f ? 1.0f : 0.0f;
}

__global__ void updateWeights(float* weights, float* input_data, float* result_data, float* bias, float eta, int size, int length, float* error) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < size) {
        float delta = eta / size * (result_data[idx] - calculatePredict(input_data, weights, *bias, idx, length));
        __syncthreads();
        for(int i = 0; i < length; i++)
            atomicAdd(&weights[i], input_data[idx * length + i] * delta);
        atomicAdd(bias, delta);
        atomicAdd(error, (float)(int(delta != 0.0)) / size);
    }
}

// CUDA kernel for predicting in parallel
__global__ void cuda_predict(float* weights, float* input_data, float* bias, int* predictions, int size, int length) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < size) {
        predictions[idx] = calculatePredict(input_data, weights, *bias, idx, length);
    }
}

class CudaPerceptron {
private:
    float eta;
    int epoch;
    float bias;
    float* d_weights;
    float* d_input_data;
    float* d_result_data;
    float* d_bias;
    int random_state;
    std::vector<float> weight;
    float error;
    float* d_error;
    std::vector<float> errors;
    IRandomeVector* randomVectorPtr;

public:
    CudaPerceptron(IRandomeVector* randomVectorPtr, float eta = 0.01, int epoch = 50, int random_state = 1) : eta(eta), epoch(epoch), random_state(random_state), randomVectorPtr(randomVectorPtr) {
        cudaMalloc(&d_bias, sizeof(float));
    }

    ~CudaPerceptron() {
        cudaFree(d_weights);
        cudaFree(d_input_data);
        cudaFree(d_result_data);
        cudaFree(d_bias);
        cudaFree(d_error);
    }

    void Initialize_Data(int length) {
        bias = 0.0f;
        randomVectorPtr->size = length;
        weight = randomVectorPtr->getData();
        
        cudaMalloc(&d_weights, length * sizeof(float));
        cudaMemcpy(d_weights, weight.data(), length * sizeof(float), cudaMemcpyHostToDevice);
        cudaMemcpy(d_bias, &bias, sizeof(float), cudaMemcpyHostToDevice);

        error = 0.0f;
        cudaMalloc(&d_error, sizeof(float));
        cudaMemcpy(d_error, &error, sizeof(float), cudaMemcpyHostToDevice);
    }

    void Initialize_Input_Result_Data(int size, int length, std::vector<std::vector<float>> input_data, std::vector<float> result_data) {
        
        float* input_data_array = convertToCUDAStyleArray(input_data);
        float* result_data_array = convertToCStyleArray(result_data);
        
        // Copy data from host to device
        cudaMalloc(&d_input_data, length * sizeof(float) * size);
        cudaMalloc(&d_result_data, sizeof(float) * size);
        cudaMemcpy(d_input_data, input_data_array, length * sizeof(float) * size, cudaMemcpyHostToDevice);
        cudaMemcpy(d_result_data, result_data_array, sizeof(float) * size, cudaMemcpyHostToDevice);
    }

    void fit(std::vector<std::vector<float>> input_data, std::vector<float> result_data) {
        int ylength = input_data.size();
        int xlength = input_data[0].size();
        Initialize_Data(xlength);
        Initialize_Input_Result_Data(ylength, xlength, input_data, result_data);

        float weights[2]{0.0f, 0.0f};
        // Train the perceptron using CUDA
        for (int e = 0; e < epoch; e++) {
            error = 0.0f;
            cudaMemcpy(d_error, &error, sizeof(float), cudaMemcpyHostToDevice);
            // cudaMemcpy(d_weights, weight.data(), sizeof(float) * xlength, cudaMemcpyHostToDevice);

            updateWeights<<<1, ylength>>>(d_weights, d_input_data, d_result_data, d_bias, eta, ylength, xlength, d_error);
            cudaDeviceSynchronize();
            
            cudaMemcpy(&error, d_error, sizeof(float), cudaMemcpyDeviceToHost);
            cudaMemcpy(&weights, d_weights, sizeof(float) * xlength, cudaMemcpyDeviceToHost);
            std::cout << "-----epoch (" << e + 1 << "/" << epoch << ")--------"<< error << "----" << weights[0] << "," << weights[1]<< std::endl;
            errors.push_back(error);
        }
    }

    int predict(std::vector<float> input_data) {
        int* d_predictions;
        int h_predictions = 0;
        int xlength = input_data.size();
        float* input_data_array = convertToCStyleArray(input_data);

        cudaMalloc(&d_predictions, sizeof(int));

        float* d_input_datas;
        cudaMalloc(&d_input_datas, xlength * sizeof(float));
        cudaMemcpy(d_input_datas, input_data_array, xlength * sizeof(float), cudaMemcpyHostToDevice);

        cuda_predict<<<1, 1>>>(d_weights, d_input_datas, d_bias, d_predictions, 1, xlength);
        cudaDeviceSynchronize();

        cudaMemcpy(&h_predictions, d_predictions, sizeof(int), cudaMemcpyDeviceToHost);
        cudaFree(d_predictions);
        cudaFree(d_input_data);

        return h_predictions;
    }

    float* convertToCStyleArray(const std::vector<float>& input) {
        int size = input.size();
        float* arr = new float[size];
        for (int i = 0; i < size; i++)
            arr[i] = input[i];
        return arr;
    }

    float* convertToCUDAStyleArray(const std::vector<std::vector<float>>& input) {
        int rows = input.size();
        int cols = input[0].size();
        float* arr = new float[rows * cols];
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                arr[i * cols + j] = input[i][j];
        return arr;
    }
};
