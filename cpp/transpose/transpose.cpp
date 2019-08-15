#include <iostream>

using namespace std;

void transpose(int *collection, int dimension)
{
    for(int i = 0; i < dimension / 2; i++)
    {
        for(int j = i; j < dimension - i - 1; j++)
        {
            int temp = collection[i * dimension + j];
            collection[i * dimension + j] = collection[j * dimension + dimension - i - 1];
            collection[j * dimension + dimension - i - 1] = collection[(dimension - i - 1) * dimension + dimension - j - 1];
            collection[(dimension - i - 1) * dimension + dimension - j - 1] = collection[(dimension - j - 1) * dimension + i];
            collection[(dimension - j - 1) * dimension + i] = temp;
        }   
    }   
}


int main() {

    const int dimension = 5;
    int numbers[dimension][dimension];
    for(int i = 0; i < dimension; i++)
        for(int j = 0; j < dimension; j++)
            numbers[i][j] = j;

    cout << "____BEFORE____" << endl;
    for(int i = 0; i < dimension; i++)
    {
        for(int j = 0; j < dimension; j++)
            cout << numbers[i][j] << "  ";
        cout << endl;
    }

    cout << endl;
    transpose((int *) numbers, dimension);

    cout << "____AFTER____" << endl;
    for(int i = 0; i < dimension; i++)
    {
        for(int j = 0; j < dimension; j++)
            cout << numbers[i][j] << "  ";
        cout << endl;
    }

} 
