﻿namespace Perceptron;

public interface IPerceptron
{
    public float Bias { get; set; }
    public float LearningRate { get; }
    public int Epoch { get; }
    public int Random_state { get; }
}

public class Perceptron : IPerceptron
{
    public float Bias { get; set; }
    public float LearningRate { get; private set; }
    public int Epoch { get; private set; }
    public int Random_state { get; private set; }
    public List<int> Errors { get; set; }
    public List<float> Weight { get; set; }

    public Perceptron(float learningRate = 0.01f, int epoch = 50, int random_state = 1)
    {
        Errors = new List<int>();
        Weight = new List<float>();
        LearningRate = learningRate;
        Epoch = epoch;
        Random_state = random_state;
    }

    public void Initailize(List<List<float>> input_data)
    {
        Bias = 0.0f;
        InitializeWeight(input_data);
    }

    public void Fit(List<List<float>> input_data, List<float> result_data)
    {
        Initailize(input_data);
        for (int e = 0; e < Epoch; e++)
        {
            int error = 0;
            error = Training(input_data, result_data, error);
            Errors.Add(error);
            Console.WriteLine($"-----epoch ({e + 1}/{Epoch})-----error:{error}");
        }
    }

    private int Training(List<List<float>> input_data, List<float> result_data, int error)
    {
        var dataAndResult = input_data.Zip(result_data, (data, result) => (data, result));
        foreach (var (data, result) in dataAndResult)
        {
            float delta = LearningRate * (result - Predict(data));
            Weight = Weight.Select((w, i) => w + data[i] * delta).ToList();
            Bias = delta;
            error += delta != 0.0f ? 1 : 0;
        }

        return error;
    }

    public int Predict(List<float> input_data) => Caculate_Perceptron(input_data) >= 0.0f ? 1 : 0;
    public float Caculate_Perceptron(List<float> input_data) => Multiplex(input_data) + Bias;
    public float Multiplex(List<float> input_data) => input_data.Zip(Weight, (data, weight) => data * weight).Sum();

    public void InitializeWeight(List<List<float>> input_data)
    {
        Random rgen = new Random(Random_state);

        Weight = input_data[0].Select(_ => (float)rgen.NextDouble()).ToList();
    }
}

public class Perceptron_Array : IPerceptron
{
    public float Bias { get; set; }
    public float LearningRate { get; private set; }
    public int Epoch { get; private set; }
    public int Random_state { get; private set; }
    public int[] Errors { get; set; }
    public float[] Weight { get; set; }

    public Perceptron_Array(float learningRate = 0.01f, int epoch = 50, int random_state = 1)
    {
        LearningRate = learningRate;
        Epoch = epoch;
        Random_state = random_state;
        Weight = new float[0];
        Errors = new int[Epoch];
    }

    public void Initailize(float[][] input_data)
    {
        Bias = 0.0f;
        InitializeWeight(input_data);
    }

    public void Fit(float[][] input_data, float[] result_data)
    {
        Initailize(input_data);
        for (int e = 0; e < Epoch; e++)
        {
            int error = 0;
            error = Training(input_data, result_data, error);
            Errors[e] = error;
            Console.WriteLine($"-----epoch ({e + 1}/{Epoch})-----error:{error}");
        }
    }

    private int Training(float[][] input_data, float[] result_data, int error)
    {
        var dataAndResult = input_data.Zip(result_data, (data, result) => (data, result));
        foreach (var (data, result) in dataAndResult)
        {
            float delta = LearningRate * (result - Predict(data));
            Weight = Weight.Select((w, i) => w + data[i] * delta).ToArray();
            Bias = delta;
            error += delta != 0.0f ? 1 : 0;
        }

        return error;
    }

    public int Predict(float[] input_data) => Caculate_Perceptron(input_data) >= 0.0f ? 1 : 0;
    public float Caculate_Perceptron(float[] input_data) => Multiplex(input_data) + Bias;
    public float Multiplex(float[] input_data) => input_data.Zip(Weight, (data, weight) => data * weight).Sum();

    public void InitializeWeight(float[][] input_data)
    {
        Random rgen = new Random(Random_state);
        Weight = input_data[0].Select(_ => (float)rgen.NextDouble()).ToArray();
    }
}
public class Perceptron_Array2D : IPerceptron
{
    public float Bias { get; set; }
    public float LearningRate { get; private set; }
    public int Epoch { get; private set; }
    public int Random_state { get; private set; }
    public int[] Errors { get; set; }
    public float[] Weight { get; set; }

    public Perceptron_Array2D(float learningRate = 0.01f, int epoch = 50, int random_state = 1)
    {
        LearningRate = learningRate;
        Epoch = epoch;
        Random_state = random_state;
        Weight = new float[0];
        Errors = new int[Epoch];
    }

    public void Initailize(float[,] input_data)
    {
        Bias = 0.0f;
        InitializeWeight(input_data);
    }

    public void Fit(float[,] input_data, float[] result_data)
    {
        Initailize(input_data);
        for (int e = 0; e < Epoch; e++)
        {
            int error = 0;
            error = Training(input_data, result_data, error);
            Errors[e] = error;
            Console.WriteLine($"-----epoch ({e + 1}/{Epoch})-----error:{error}");
        }
    }

    private int Training(float[,] input_data, float[] result_data, int error)
    {
        for (int i = 0; i < input_data.GetLength(0); i++)
        {
            float[] data = new float[input_data.GetLength(1)];
            for (int j = 0; j < input_data.GetLength(1); j++)
                data[j] = input_data[i, j];

            float result = result_data[i];
            float delta = LearningRate * (result - Predict(data));
            Weight = Weight.Select((w, i) => w + data[i] * delta).ToArray();
            Bias = delta;
            error += delta != 0.0f ? 1 : 0;
        }

        return error;
    }

    public int Predict(float[] input_data) => Caculate_Perceptron(input_data) >= 0.0f ? 1 : 0;
    public float Caculate_Perceptron(float[] input_data) => Multiplex(input_data) + Bias;
    public float Multiplex(float[] input_data) => input_data.Zip(Weight, (data, weight) => data * weight).Sum();

    public void InitializeWeight(float[,] input_data)
    {
        Random rgen = new Random(Random_state);
        Weight = new float[input_data.GetLength(1)];
        for (int i = 0; i < Weight.Length; i++)
        {
            Weight[i] = (float)rgen.NextDouble();
        }
    }
}

public interface IPerceptron_Double
{
    public double Bias { get; set; }
    public double LearningRate { get; }
    public int Epoch { get; }
    public int Random_state { get; }
}

public class Perceptron_Double : IPerceptron_Double
{
    public double Bias { get; set; }
    public double LearningRate { get; private set; }
    public int Epoch { get; private set; }
    public int Random_state { get; private set; }
    public List<int> Errors { get; set; }
    public List<double> Weight { get; set; }

    public Perceptron_Double(double learningRate = 0.01, int epoch = 50, int random_state = 1)
    {
        Errors = new List<int>();
        Weight = new List<double>();
        LearningRate = learningRate;
        Epoch = epoch;
        Random_state = random_state;
    }

    public void Initailize(List<List<double>> input_data)
    {
        Bias = 0.0;
        InitializeWeight(input_data);
    }

    public void Fit(List<List<double>> input_data, List<double> result_data)
    {
        Initailize(input_data);
        for (int e = 0; e < Epoch; e++)
        {
            int error = 0;
            error = Training(input_data, result_data, error);
            Errors.Add(error);
            Console.WriteLine($"-----epoch ({e + 1}/{Epoch})-----error:{error}");
        }
    }

    private int Training(List<List<double>> input_data, List<double> result_data, int error)
    {
        var dataAndResult = input_data.Zip(result_data, (data, result) => (data, result));
        foreach (var (data, result) in dataAndResult)
        {
            double delta = LearningRate * (result - Predict(data));
            Weight = Weight.Select((w, i) => w + data[i] * delta).ToList();
            Bias = delta;
            error += delta != 0.0 ? 1 : 0;
        }

        return error;
    }

    public int Predict(List<double> input_data) => Caculate_Perceptron(input_data) >= 0.0 ? 1 : 0;
    public double Caculate_Perceptron(List<double> input_data) => Multiplex(input_data) + Bias;
    public double Multiplex(List<double> input_data) => input_data.Zip(Weight, (data, weight) => data * weight).Sum();

    public void InitializeWeight(List<List<double>> input_data)
    {
        Random rgen = new Random(Random_state);

        Weight = input_data[0].Select(_ => rgen.NextDouble()).ToList();
    }
}

public class Perceptron_Array_Double : IPerceptron_Double
{
    public double Bias { get; set; }
    public double LearningRate { get; private set; }
    public int Epoch { get; private set; }
    public int Random_state { get; private set; }
    public int[] Errors { get; set; }
    public double[] Weight { get; set; }

    public Perceptron_Array_Double(double learningRate = 0.01, int epoch = 50, int random_state = 1)
    {
        LearningRate = learningRate;
        Epoch = epoch;
        Random_state = random_state;
        Weight = new double[0];
        Errors = new int[Epoch];
    }

    public void Initailize(double[][] input_data)
    {
        Bias = 0.0f;
        InitializeWeight(input_data);
    }

    public void Fit(double[][] input_data, double[] result_data)
    {
        Initailize(input_data);
        for (int e = 0; e < Epoch; e++)
        {
            int error = 0;
            error = Training(input_data, result_data, error);
            Errors[e] = error;
            Console.WriteLine($"-----epoch ({e + 1}/{Epoch})-----error:{error}");
        }
    }

    private int Training(double[][] input_data, double[] result_data, int error)
    {
        var dataAndResult = input_data.Zip(result_data, (data, result) => (data, result));
        foreach (var (data, result) in dataAndResult)
        {
            double delta = LearningRate * (result - Predict(data));
            Weight = Weight.Select((w, i) => w + data[i] * delta).ToArray();
            Bias = delta;
            error += delta != 0.0f ? 1 : 0;
        }

        return error;
    }

    public int Predict(double[] input_data) => Caculate_Perceptron(input_data) >= 0.0 ? 1 : 0;
    public double Caculate_Perceptron(double[] input_data) => Multiplex(input_data) + Bias;
    public double Multiplex(double[] input_data) => input_data.Zip(Weight, (data, weight) => data * weight).Sum();

    public void InitializeWeight(double[][] input_data)
    {
        Random rgen = new Random(Random_state);
        Weight = input_data[0].Select(_ => rgen.NextDouble()).ToArray();
    }
}
public class Perceptron_Array2D_Double : IPerceptron_Double
{
    public double Bias { get; set; }
    public double LearningRate { get; private set; }
    public int Epoch { get; private set; }
    public int Random_state { get; private set; }
    public int[] Errors { get; set; }
    public double[] Weight { get; set; }

    public Perceptron_Array2D_Double(double learningRate = 0.01f, int epoch = 50, int random_state = 1)
    {
        LearningRate = learningRate;
        Epoch = epoch;
        Random_state = random_state;
        Weight = new double[0];
        Errors = new int[Epoch];
    }

    public void Initailize(double[,] input_data)
    {
        Bias = 0.0;
        InitializeWeight(input_data);
    }

    public void Fit(double[,] input_data, double[] result_data)
    {
        Initailize(input_data);
        for (int e = 0; e < Epoch; e++)
        {
            int error = 0;
            error = Training(input_data, result_data, error);
            Errors[e] = error;
            Console.WriteLine($"-----epoch ({e + 1}/{Epoch})-----error:{error}");
        }
    }

    private int Training(double[,] input_data, double[] result_data, int error)
    {
        for (int i = 0; i < input_data.GetLength(0); i++)
        {
            double[] data = new double[input_data.GetLength(1)];
            for (int j = 0; j < input_data.GetLength(1); j++)
                data[j] = input_data[i, j];

            double result = result_data[i];
            double delta = LearningRate * (result - Predict(data));
            Weight = Weight.Select((w, i) => w + data[i] * delta).ToArray();
            Bias = delta;
            error += delta != 0.0f ? 1 : 0;
        }

        return error;
    }

    public int Predict(double[] input_data) => Caculate_Perceptron(input_data) >= 0.0f ? 1 : 0;
    public double Caculate_Perceptron(double[] input_data) => Multiplex(input_data) + Bias;
    public double Multiplex(double[] input_data) => input_data.Zip(Weight, (data, weight) => data * weight).Sum();

    public void InitializeWeight(double[,] input_data)
    {
        Random rgen = new Random(Random_state);
        Weight = new double[input_data.GetLength(1)];
        for (int i = 0; i < Weight.Length; i++)
        {
            Weight[i] = rgen.NextDouble();
        }
    }
}