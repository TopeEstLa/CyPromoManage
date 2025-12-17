#include <memory_utils.h>
#include <stdlib.h>
#include <stdio.h>

void* swap_order(void* data, int size, int count) {
    if (data == NULL || size <= 0 || count <= 0) {
        return data;
    }

    char* byteData = (char*)data;
    for (int i = 0; i < count / 2; i++) {
        for (int j = 0; j < size; j++) {
            char temp = byteData[i * size + j];
            byteData[i * size + j] = byteData[(count - 1 - i) * size + j];
            byteData[(count - 1 - i) * size + j] = temp;
        }
    }

    return data;
}