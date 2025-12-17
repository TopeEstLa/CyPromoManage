#include <memory_utils.h>
#include <stdlib.h>
#include <stdio.h>

void* swap_order(void* data, int size, int count) {
    if (data == NULL) return NULL;

    if (size != 2 && size != 4 && size != 8) return NULL;

    void* newData = malloc(size * count);
    if (newData == NULL) return NULL;

    for (int i = 0; i < count; i++) {
        //unsigned char cause its byte per byte operation and can't do it with a void* type (idk if its can broke somethings)
        unsigned char* srcItem = data + (i * size);
        unsigned char* dstItem = newData + (i * size);

        for (int j = 0; j < size; j++) {
            dstItem[j] = srcItem[size - 1 - j];
        }
    }

    return newData;
}