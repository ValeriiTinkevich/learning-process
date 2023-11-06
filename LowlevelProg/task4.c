#include<inttypes.h>
#include<stdio.h>
#include<malloc.h>


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


int64_t** marray_read( size_t* rows, size_t** sizes ) {
    *rows = read_size();
    int64_t **marray;
    marray = (int64_t**) malloc(*rows * sizeof(int64_t*));
    *sizes = (size_t*) malloc(*rows * sizeof(size_t));
    for (size_t i = 0; i < *rows; i++) {
        marray[i] = array_int_read(&(*sizes)[i]);
    }
    return marray;
}

int64_t* int_ptr_min( int64_t* x, int64_t* y ) {
   if (!x) { return y; }
   if (!y) { return x; }
   if ( *x < *y ) { return x; } else { return y; }   
}

int64_t* array_int_min( int64_t* array, size_t size ) {
   int64_t* min = NULL;
   for ( size_t i = 0; i < size; i = i + 1 ) {
      min = int_ptr_min( min, array + i );
   }
   return min;
}

// Вернуть адрес минимального элемента массива массивов
int64_t* marray_int_min( int64_t** marray, size_t* sizes, size_t rows ) {
    int64_t* min = NULL;
    for(size_t i = 0; i < rows; i++) {
        min = int_ptr_min(min, array_int_min(marray[i], sizes[i]));
    }
    return min;
}

// Вычесть m изо всех элементов массива
void marray_normalize( int64_t** marray, size_t sizes[], size_t rows, int64_t m ) {
    for(size_t i = 0; i < rows; i++) {
        for(size_t j = 0; j < sizes[i]; j++) {
            marray[i][j] = marray[i][j] - m;
        }
    }
}


// Прочитать, найти минимум и нормализовать массив, вывести результат
void perform() {
    size_t rows;
    size_t* sizes;
    int64_t** marray = marray_read(&rows, &sizes);

    int64_t* min = marray_int_min(marray, sizes, rows);

    if (min) {
    marray_normalize( marray, sizes, rows, *min );
    marray_print( marray, sizes, rows );
    }

    marray_free( marray, rows );
    free( sizes );
}




int main() {
    size_t* sizes = 0;
    int64_t rows = 0;
    int64_t** arr = marray_read(&rows, &sizes);

    int64_t* min = marray_int_min(arr, sizes, rows);

    printf("%" PRId64, *min);
    printf("\n");
    
    marray_normalize(arr, sizes, rows, *min);

    for(size_t i = 0; i < rows; i++) {
        for(size_t j = 0; j < sizes[i]; j++) {
            printf(" %" PRId64, arr[i][j]);
        }
        printf("\n");
    }



}