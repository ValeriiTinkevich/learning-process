#include<inttypes.h>
#include<stdio.h>
#include<malloc.h>

// вы можете реализовать эти функции для более удобного считывания чисел
int64_t read_int64(){
    int64_t x;
    scanf( "%" SCNd64, &x );
    return x;
}
size_t read_size() {
    size_t x;
    scanf("%zu", &x);
    return x;
}

// заполнить уже выделенный массив array размера size числами
// числа нужно считывать из потока ввода
void array_int_fill( int64_t* array, size_t size ) {
    for (size_t i = 0; i < size; i++ ) {
        array[i] = read_int64();
    }
}

// Считать размер массива в *size, выделить память под массив и заполнить его числами, вызвав array_int_fill
int64_t* array_int_read( size_t* size ) {
    *size = read_size();
    int64_t* array = malloc(sizeof(int64_t) * *size);
    array_int_fill(array, *size);
    return array;
}

int main() {
    size_t size;
    int64_t* arr = array_int_read(&size);
    for(size_t i = 0; i < size; i++) {
        printf( " %" PRId64, arr[i] );
    }
}

