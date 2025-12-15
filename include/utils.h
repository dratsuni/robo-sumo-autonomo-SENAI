#ifndef UTILS_H
#define UTILS_H


__attribute__((always_inline))
inline void insertion_sort(int *array, size_t size){
  int key = 0;
  for (int i = 0; i < size; i++){
    for (int j = i; j > 0; j--){
       if (array[j - 1] > array[j]){
          key = array[j];
          array[j] = array[j - 1];
          array[j - 1] = key;
       } else {
          break;
       }
    }
  }
}

#endif