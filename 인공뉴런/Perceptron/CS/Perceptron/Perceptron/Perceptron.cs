namespace Perception;

public interface IPerception
{
    public float Bias { get; set; }
    public float LearningRate { get; }
    public int Epoch { get; }
    public int Random_state { get; }
}

public class Perceptron : IPerception
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
