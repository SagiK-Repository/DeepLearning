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
}
