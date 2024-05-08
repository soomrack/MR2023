void merge_Sort(int* arr, int size)
{
    int mid = size / 2;
    if (size % 2 == 1)
        mid++;
    int s = 1;
    int* arr1 = new int[size];
    int step;
    while (s < size)
    {
        step = s;
        int path1_i = 0;
        int path2_i = mid;
        int res_i = 0;
        while (step <= mid)
        {
            while ((path1_i < step) && (path2_i < size) && (path2_i < (mid + step))) 
            {
                if (arr[path1_i] < arr[path2_i])
                {
                    arr1[res_i] = arr[path1_i];
                    path1_i++; res_i++;
                }
                else {
                    arr1[res_i] = arr[path2_i];
                    path2_i++; res_i++;
                }
            }
            while (path1_i < step)
            {
                arr1[res_i] = arr[path1_i];
                path1_i++; res_i++;
            }
            while ((path2_i < (mid + step)) && (path2_i < size))
            {
                arr1[res_i] = arr[path2_i];
                path2_i++; res_i++;
            }
            step = step + s;
        }
      
        s = s * 2;

        for (int i = 0; i < size; i++)
            arr[i] = arr1[i];
    }

    delete[] arr1;
}
