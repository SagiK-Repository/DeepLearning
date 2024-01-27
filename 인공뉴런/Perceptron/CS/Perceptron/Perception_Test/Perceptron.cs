using System;
using System.IO;
using Perception;

namespace Perception_Test;

public class Perceptron_Test
{
    [Fact(DisplayName = "Perceptron List Test")]
    public void Percepton_List_Test()
    {
        // Arrange
        string[][] input = CSVReader.CSVReader.Load("data.csv");
        string[][] select2 = input.Select(x => new string[]{ x[0], x[2]}).ToArray();
        List<List<float>> inputList = select2.Select(row => row.Select(float.Parse).ToList()).ToList();
        List<float> resultList = input.Select(row => row.Last() == "Iris-setosa" ? 0.0f : 1.0f).ToList();

        inputList.RemoveAt(0); resultList.RemoveAt(0);
        inputList.RemoveRange(100, 50); resultList.RemoveRange(100, 50);

        Perceptron perceptron = new Perceptron(0.1f, 10);

        // Act
        perceptron.Fit(inputList, resultList);

        // Assert
        perceptron.Predict(new List<float> { 5.0f, 2.0f }).Should().Be(0);
        perceptron.Predict(new List<float> { 6.0f, 2.0f }).Should().Be(0);
        perceptron.Predict(new List<float> { 7.0f, 1.0f }).Should().Be(0);
        perceptron.Predict(new List<float> { 7.0f, 2.0f }).Should().Be(0);
        perceptron.Predict(new List<float> { 7.0f, 7.0f }).Should().Be(1);
        perceptron.Predict(new List<float> { 7.0f, 6.0f }).Should().Be(1);
        perceptron.Predict(new List<float> { 5.0f, 4.0f }).Should().Be(1);
    }
}