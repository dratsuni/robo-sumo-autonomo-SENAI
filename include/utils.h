#ifndef UTILS_H
#define UTILS_H

__attribute__((always_inline))
inline void insertion_sort(unsigned int *array, uint8_t size){
  unsigned long key = 0;
  for (uint8_t i = 0; i < size; i++){
    for (uint8_t j = i; j > 0; j--){
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