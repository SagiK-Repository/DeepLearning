namespace CSVReader;

public static class CSVReader
{
    public static bool IsExistFile(string filePath)
    {
        if (File.Exists(filePath) == false)
        {
            Console.WriteLine("Not Exist CSV File");
            return false;
        }
        return true;
    }
    public static string[][] Load(string filePath)
    {
        List<string[]> dataArray = new List<string[]>();

        if (IsExistFile(filePath) == false)
            throw new FileNotFoundException(filePath + " is Not Exist");

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
        string[] lines = File.ReadAllLines(filePath);
        int numRows = lines.Length;
        int numCols = lines[0].Split(',').Length;

        string[,] arrayData = new string[numRows, numCols];

        for (int i = 0; i < numRows; i++)
        {
            string[] rowData = lines[i].Split(',');

            for (int j = 0; j < numCols; j++)
                arrayData[i, j] = rowData[j];
        }

        return arrayData;
    }
}
