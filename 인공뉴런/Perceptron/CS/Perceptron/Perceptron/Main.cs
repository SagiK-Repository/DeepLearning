using Perceptron;

Console.WriteLine("Hello, World!");

// Arrange
string[][] input = CSVReader.CSVReader.Load("..\\..\\..\\data.csv");
string[][] select2 = input.Select(x => new string[] { x[0], x[2] }).ToArray();
List<List<float>> inputList = select2.Select(row => row.Select(float.Parse).ToList()).ToList();
List<float> resultList = input.Select(row => row.Last() == "Iris-setosa" ? 0.0f : 1.0f).ToList();

inputList.RemoveAt(0); resultList.RemoveAt(0);
inputList.RemoveRange(100, 50); resultList.RemoveRange(100, 50);

//Act
Perceptron perceptron = new Perceptron(0.1f, 10);
perceptron.Fit(inputList, resultList);