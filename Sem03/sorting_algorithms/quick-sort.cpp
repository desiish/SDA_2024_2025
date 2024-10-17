#include <iostream>
using namespace std;

template <class T>
int partition(T* arr, size_t size) {
    int pivot = arr[size / 2];
    int beg = 0, end = size - 1;

    while (true) {
        while (arr[beg] < pivot) {
            beg++;
        }

        while (arr[end] > pivot)
            end--;

        if (beg >= end) //ако указателите ни се срещнат (разминат), брейкваме !!!
            break;

        if (arr[beg] == arr[end]) // за случаи, в които имаме повтарящи се елементи - иначе ще swap-ваме до безкрай
            beg++;

        std::swap(arr[beg], arr[end]);
    }
    return beg; //там ще ни стои pivot-a
}

template <class T>
void quickSort(T* arr, size_t size) {
    if (size <= 1)
        return;
    int pIdx = partition(arr, size);
    quickSort(arr, pIdx); // сортираме първата половина до индекса на pivot-a 
    quickSort(arr + pIdx + 1, size - pIdx - 1); //сортираме втората половина след индекса на pivot-a 
}


const int SIZE = 7;
int main()
{
    int arr1[] = { 2, 1, 0, 9, 7, 4, 3};
    quickSort(arr1, SIZE);

    for (int i = 0; i < SIZE; i++)
        cout << arr1[i] << " ";
}
