/*

Our binary search makes two test inside the loop, when one would suffice
(at the price of more tests outside). Write a version with only one test
inside the loop and measure the difference in run-time.

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int*, int*);
void printArr(int*, unsigned);
void bubbleSort(int*, unsigned);
int binSearch1(int, int*, unsigned); // original function
int binSearch2(int, int*, unsigned); // Our solution to exercise 3.1.

void swap(int* x, int* y)
{
  int temp;

  temp = *x;
  *x = *y;
  *y = temp;
}

void printArr(int arr[], unsigned len)
{
  int i;

  for(i = 0; i < len; ++i)
    printf("%d ", arr[i]);
  printf("\n");
}

void bubbleSort(int arr[], unsigned len)
{
  int i, j;

  for(i = 0; i < len; ++i)
    for(j = 0; j < len - 1 - i; ++j)
      if(arr[j] > arr[j+1])
        swap(&arr[j], &arr[j+1]);
}

int binSearch1(int x, int arr[], unsigned len)
{
  int low, high, mid;

  low = 0;
  high = len - 1;

  while(low <= high) {
    mid = (low + high) / 2;
    if(x < arr[mid])
      high = mid + 1;
    else if(x > arr[mid])
      low = mid + 1;
    else
      return mid;
  }

  return -1;
}

int binSearch2(int x, int arr[], unsigned len)
{
  int low, high, mid;

  low = 0;
  high = len - 1;

  while(low <= high && x != arr[mid]) {
    mid = (low + high) / 2;
    if (x < arr[mid])
      high = mid + 1;
    else
      low = mid + 1;
  }
  if (x == arr[mid])
    return mid;
  else
    return -1;
}

int main(int argc, char *argv[])
{
  int arr[] = {34, 53, 12, 85, 58, 95, 34, 65, 88, 98};
  unsigned len = sizeof(arr) / sizeof(arr[0]);
  int x = 58; // The number you want to seach for.
  clock_t time_taken = clock();

  printArr(arr, len);
  bubbleSort(arr, len);
  printArr(arr, len);

  printf("binSearch1 result:%d\n", (binSearch1(x, arr, len)));
  time_taken = clock() - time_taken;
  printf("binSearch1 time %lu clocks\n", (unsigned long)time_taken); 

  printf("binSearch2 result:%d\n", (binSearch2(x, arr, len)));
  time_taken = clock() - time_taken;
  printf("binSearch2 time %lu clocks\n", (unsigned long)time_taken);

  return 0;
}
