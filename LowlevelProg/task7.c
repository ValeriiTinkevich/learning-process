#include <stdio.h>
#include <inttypes.h>
#include <malloc.h>
#include <stdbool.h>

/* --- числа --- */

// проверка на число и его значение
struct maybe_int64 {
int64_t value;
bool valid;
};

// создание структуры с числом
struct maybe_int64 some_int64(int64_t i) {
return (struct maybe_int64) {.value = i, .valid = true};
}

// не число
const struct maybe_int64 none_int64 = {0};

// напечатать возможное число
void maybe_int64_print(struct maybe_int64 i) {
if (i.valid) {
printf("%" PRId64, i.value);
}
}

// напечатать число
void print_int64(int64_t i) {
printf("%" PRId64, i);
}


/* ---- массивы ---- */

// массив чисел и его размер
struct array_int {
int64_t *data;
size_t size;
};

// создание массива чисел размеров sz
struct array_int array_int_create(size_t sz) {
return (struct array_int) {.data = malloc(sizeof(int64_t) * sz), .size = sz};
}

// возвращает указатель на последнюю ячейку в массиве
int64_t *array_int_last(struct array_int a) {
return a.data + (a.size - 1);
}

// получить число из массива структуры a под индексом i
struct maybe_int64 array_int_get(struct array_int a, size_t i) {
if (0 <= i && i < a.size) { return some_int64(a.data[i]); }
else { return none_int64; }
}

// вставляет число в массив по индексу и возвращает true,
bool array_int_set(struct array_int a, size_t i, int64_t value) {
if (i < a.size) {
a.data[i] = value;
return true;
} else { return false; }
}

// печатает массив чисел
void array_int_print(struct array_int array) {
for (size_t i = 0; i < array.size; i = i + 1) {
printf("%" PRId64 " ", array_int_get(array, i).value);
}
}

// освобождает память массива в структуре по его адресу
void array_int_free(struct array_int *a) {
free(a->data);
}

