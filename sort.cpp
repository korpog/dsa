#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
using namespace std;
using namespace std::chrono;

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(int arr[], int n)
{
    int i, j, min_idx;

    for (i = 0; i < n - 1; i++)
    {
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;

        swap(arr[min_idx], arr[i]);
    }
}

void countingSort(int array[], int size, int place)
{
    const int max = 10;
    int output[size];
    int count[max];

    for (int i = 0; i < max; ++i)
        count[i] = 0;

    for (int i = 0; i < size; i++)
        count[(array[i] / place) % max]++;

    for (int i = 1; i < max; i++)
        count[i] += count[i - 1];

    for (int i = size - 1; i >= 0; i--)
    {
        output[count[(array[i] / place) % max] - 1] = array[i];
        count[(array[i] / place) % max]--;
    }

    for (int i = 0; i < size; i++)
        array[i] = output[i];
}

void radixSort(int array[], int size)
{
    int max = array[0];
    for (int i = 1; i < size; i++)
        if (array[i] > max)
            max = array[i];

    for (int place = 1; max / place > 0; place *= 10)
        countingSort(array, size, place);
}

void printArray(int array[], int size)
{
    for (int i = 0; i < size; i++)
        cout << array[i] << " ";
    cout << endl;
}

void fillArray(int array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        array[i] = rand();
    }
}

void fillArrayAsc(int array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        array[i] = i;
    }
}

void fillArrayDesc(int array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        array[i] = size - i;
    }
}

int main()
{
    srand(static_cast<unsigned>(time(0)));

    // mergeSort(arr1k, 0, n1);
    // quickSort(arr1k, 0, n1 - 1);
    // insertionSort(arr1k, n1);
    // selectionSort(arr1k, n1);
    // radixSort(arr1k, n1);

    int n1 = 1000;
    int n2 = 10000;
    int n3 = 100000;
    int *arr1k = new int[n1];
    int *arr10k = new int[n2];
    int *arr100k = new int[n3];

    int *average = new int[30];

    for (int i = 0; i < 30; i++)
    {
        fillArrayDesc(arr100k, n3);
        //printArray(arr1k, n1);

        auto start = high_resolution_clock::now();
        radixSort(arr100k, n3);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        average[i] = duration.count();

        cout << "Time taken by function: "
             << duration.count() << " microseconds" << endl;
    }

    int sum = 0;
    for (int i = 0; i < 30; i++)
    {
        sum += average[i];
    }
    double avg = static_cast<double>(sum) / 30;

    cout << "Average time taken by function: "
         << avg << " microseconds" << endl;

    //printArray(arr1k, n1);

    return 0;
}