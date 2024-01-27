namespace ArrayHandler;

public static class ArrayHandler
{
    public static T[] RemoveFirstElement<T>(T[] array)
    {
        return array.Skip(1).ToArray();
    }

    public static T[] RemoveRange<T>(T[] array, int startIndex, int count)
    {
        return array.Take(startIndex).Concat(array.Skip(startIndex + count)).ToArray();
    }

    public static T[,] RemoveFirstElement<T>(T[,] array)
    {
        int rows = array.GetLength(0);
        int cols = array.GetLength(1);
        T[,] result = new T[rows - 1, cols];
        for (int i = 1; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                result[i - 1, j] = array[i, j];
            }
        }
        return result;
    }

    public static T[,] RemoveRange<T>(T[,] array, int startRow, int rowCount)
    {
        int rows = array.GetLength(0);
        int cols = array.GetLength(1);
        T[,] result = new T[rows - rowCount, cols];
        int targetRow = 0;
        for (int i = 0; i < rows; i++)
        {
            if (i < startRow || i >= startRow + rowCount)
            {
                for (int j = 0; j < cols; j++)
                {
                    result[targetRow, j] = array[i, j];
                }
                targetRow++;
            }
        }
        return result;
    }

    public static T[,] ToArray2D<T>(this T[][] source)
    {
        int rows = source.Length;
        int cols = source[0].Length;

        T[,] result = new T[rows, cols];
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                result[i, j] = source[i][j];

        return result;
    }
}
