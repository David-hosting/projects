#include <cs50.h>
#include <stdio.h>

void MergeSort(int arr[], int length);
void MergeSortRecursive(int arr[], int l, int r);
void MergeSortedArrays(int arr[], int l, int m, int r);

int main(void)
{
    const int length = 6;
    int arr[length] = {5,2,1,3,6,4};

    MergeSort(arr, length);
    for(int i = 0; i < length; i++)
        printf("%i", arr[i]);
    printf("\n");
}

void MergeSort(int arr[], int length)
{
    MergeSortRecursive(arr, 0, length - 1);
}

void MergeSortRecursive(int arr[], int l, int r)
{
    if (!(l < r)) // If (right >= Left)
        return;

    int m = l + (r - l) / 2; // Adding the left index to the product of (right index - left index) divided by 2.
    MergeSortRecursive(arr, l, m); // Sort Left half of array.
    MergeSortRecursive(arr, m + 1, r); // Sort Right half of array.

    MergeSortedArrays(arr, l, m, r); // Merge the two sorted arrays.
}

void MergeSortedArrays(int arr[], int l, int m, int r)
{
    int lenL = m - l + 1; // Left Length
    int lenR = r - m; // Right Length

    int L[lenL];
    int R[lenR];

    int i, j, k;

    for (i = 0; i < lenL; i++)
    {
        L[i] = arr[l + i]; // starts at L and goes up to lenL ( the L is if we are at the right half and we want the left half of it )
    }

    for (i = 0; i < lenR; i++)
    {
        R[i] = arr[m + 1 + i]; // starts at m + 1 and goes up until lenR (the m + 1 is for the right half of the right half )
    }

    /*
    |   i, j are indexs for L[] and R[] while k is for indexing the actual array (arr[]).
    |   k starts at l and stops at r (from the start of the selected array up to the end of the selected array)
    */
    for (i = 0, j = 0, k = l; k <= r; k++)
    {
        /*
        |   we check if (i < lenL), this is for if we reach the end of one of these arrays. If i is not less than lenL it means I is bigger than lenL
        |   thus meaning L[] is complete we wont be coppying anything from L[] any more.
        |                     --------------------------------------------------------------|
        |                    \/                                                             |
        |   we check if L[i] <= R[i] meaning comparing the first of each array and if true put in a[k] the number in L[i] else do the same but with R[j]
        |   we also check if this other condition - if (j >= lenR) meaning that we reached the end of the right array. And when that is True we dont need to compare
        |   L[] and R[] anymore. Just take the left over in L[].
        */
        if ((i < lenL) && (j >= lenR || L[i] <= R[j]))
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
    }
}
