#include <array_util.hpp>
#include <iostream>

using namespace std;


int main()
{
    array<unsigned int, 10> arr = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    cout << "Initial array:" << endl;
    for (const auto &item : arr)
    {
        cout << item << " ";
    }
    cout << endl;

    cout << "Swapping [1, 4) & [7, 8)..." << endl << endl;

    swapInPlace(arr, 1, 4, 7, 8);

    cout << "Swapped array:" << endl;
    for (const auto &item : arr)
    {
        cout << item << " ";
    }
    cout << endl;
}