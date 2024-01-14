// dotnet new console
// dotnet build
// dotnet run --project read_csv_data_cspj.csproj
// dotnet run --project './workspace/인공뉴런/csv data/read_csv_data_cspj/read_csv_data_cspj.csproj'

using System;
using System.IO;
using System.Collections.Generic;

class Program
{
    static void Main()
    {
        string filename = "../data.csv";
        ProcessCSV(filename);
    }

    static void ProcessCSV(string filename)
    {
        if (!File.Exists(filename))
        {
            Console.WriteLine("파일을 찾을 수 없습니다.");
            return;
        }

        List<List<string>> data = new List<List<string>>();

        // CSV 파일을 한 줄씩 읽어서 데이터를 저장
        using (var reader = new StreamReader(filename))
        {
            while (!reader.EndOfStream)
            {
                string line = reader.ReadLine();
                string[] values = line.Split(',');

                List<string> row = new List<string>(values);
                data.Add(row);
            }
        }

        // 데이터 처리 예시: 각 행의 데이터 출력
        foreach (List<string> row in data)
        {
            foreach (string value in row)
            {
                Console.Write(value + " ");
            }
            Console.WriteLine();
        }
    }
}
