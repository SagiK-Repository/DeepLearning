using FluentAssertions;
using System.ComponentModel.DataAnnotations;
using System.Reflection;
using Xunit.Sdk;

namespace Perception_Test;

public class CSVReader_Test
{
    [AttributeUsage(AttributeTargets.Method, AllowMultiple = true)]
    public class TestCSVFile : BeforeAfterTestAttribute
    {
        private string FilePath = "test.csv";

        public override void Before(MethodInfo methodUnderTest)
        {
            string[] csvData = new string[]
            {
            "John,Doe,john.doe@example.com",
            "Jane,Smith,jane.smith@example.com",
            };

            File.WriteAllLines(FilePath, csvData);
        }

        public override void After(MethodInfo methodUnderTest)
        {
            File.Delete(FilePath);
        }
    }

    [Fact]
    [TestCSVFile]
    public void CreateTestFile_Should_Exists()
    {
        // Assert
        File.Exists("test.csv").Should().BeTrue();
    }

    [TestCSVFile]
    [Fact(DisplayName = "CSVReader.Load Test")]
    public void Load_Should_Return_Correct_CSV_Data()
    {
        // Act
        string[][] result = CSVReader.CSVReader.Load("test.csv");

        // Assert
        result[0][0].Should().Be("John");
        result[1][1].Should().Be("Smith");
        result[0][2].Should().Be("john.doe@example.com");
    }

    [TestCSVFile]
    [Fact(DisplayName = "CSVReader.Array2DLoad Test")]
    public void Load_Should_Return_Correct_CSV_Data_2D_Array()
    {
        // Act
        string[,] result = CSVReader.CSVReader.Array2DLoad("test.csv");

        // Assert
        result[0, 0].Should().Be("John");
        result[1, 1].Should().Be("Smith");
        result[0, 2].Should().Be("john.doe@example.com");
    }
}
