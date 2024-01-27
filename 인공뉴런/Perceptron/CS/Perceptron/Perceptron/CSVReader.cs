namespace CSVReader;

public static class CSVReader
{
    public static string[][] Load(string filePath)
    {
        List<string[]> dataArray = new List<string[]>();

        using (StreamReader sr = new StreamReader(filePath))
            while (!sr.EndOfStream)
            {
                string line = sr.ReadLine();
                string[] data = line.Split(',');

                dataArray.Add(data);
            };

        return dataArray.ToArray();
    }

    public static string[,] Array2DLoad(string filePath)
    {
        string[][] dataArray = Load(filePath);

        int numRows = dataArray.Length;
        int numCols = dataArray[0].Length;

        string[,] data2DArray = new string[numRows, numCols];

        for (int i = 0; i < numRows; i++)
        {
            for (int j = 0; j < numCols; j++)
            {
                data2DArray[i, j] = dataArray[i][j];
            }
        }

        return data2DArray;
    }
}
