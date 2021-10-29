#include <iostream>
using namespace std;

// REQUIRES: A: increasing order array of non-negative numbers
//           B: decreasing order array of non-negative numbers
//           C: empty array
//           A, B, C have same size size
// EFFECTS: merge A and B into C
// MODIFIES: array C
void merge(int *A, int *B, int *C, size_t size) {
    size_t i = size-1, j = 0, k = size-1;
    while (i >= 0 && j < size)
    {
        // append the remain
        if (A[i]==0)
        {
            for (j; j < size; j++)
            {
                if (B[j]==0)
                {
                    C[k]=0;
                    break;
                }
                C[k]=B[j];
                k--;
            }
            break;
        }
        if (B[j]==0)
        {
            for (i; i >= 0; i--)
            {
                if (A[i]==0)
                {
                    C[k]=0;
                    break;
                }
                C[k]=A[i];
                k++;
            }
            break;
        }
        // compare and copy the larger value to C
        if (A[i]>=B[j])
        {
            C[k]=A[i];
            i--;
            k--;
        }
        else if (A[i]<B[j])
        {
            C[k]=B[j];
            j++;
            k--;
        }
    }
}

int main(){
    int A[5] = {-4, -1, 0, 3, 10};
    size_t sizeA = 5;
    int B[sizeA] = {0};
    int C[sizeA] = {0};
    size_t pos_0 = -1;
    for (size_t i = 0; i < sizeA; i++) { //Calculate the square of input array
        if (A[i] == 0)
        {
            pos_0 = i;
        }
        if (pos_0 != -1 && i >= pos_0)
        {
            A[i] = A[i] * A[i];
        }
        else
        {
            B[i] = A[i] * A[i];
            A[i] = 0;
        }
    }
    // B: the square of the negative numbers, in decreasing order
    // A: the square of the positive numbers, in increasing order
    // merge A and B;
    merge(A,B,C,sizeA);
    for (auto item: C) {
        cout << item << ' ';
    }
    cout << endl;
    return 0;
}