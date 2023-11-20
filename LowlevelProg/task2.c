#include<inttypes.h>
#include<stdio.h>
#include<malloc.h>

int64_t* array_int_min( int64_t* array, size_t size ) {
    int64_t* min = array;
    for(size_t i = 0; i < size; i++) {
        if(array[i] < *min ) {
            min = &array[i];
        }
    }
    return min;
}


int main() {
    size_t size = 5;
    int64_t array[5] = {5, 2, 1, 6, 3};
    int64_t* min = array_int_min(array, size);
    printf( " %" PRId64, *min );
    printf(" ");
}