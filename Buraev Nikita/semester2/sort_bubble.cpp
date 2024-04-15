#include <iostream>
using namespace std;

void bubbleSort(int array[], int size) {

  for (int step = 0; step < size; ++step) {
      
    for (int i = 0; i < size - step; ++i) {

      if (array[i] > array[i + 1]) {

        int temp = array[i];
        array[i] = array[i + 1];
        array[i + 1] = temp;
      }
    }
  }
}
