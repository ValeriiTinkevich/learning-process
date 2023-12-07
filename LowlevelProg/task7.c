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

struct stack {
  size_t count;
  struct array_int data;
};

// Количество элементов в стеке
size_t stack_count( const struct stack* s ) {
    return s->count;
}

// Создаем и деинициализируем стек
struct stack stack_create( size_t size ) {
    return (struct stack) {.data = array_int_create(size), .count = 0};
}

void stack_destroy( struct stack* s ) {
    array_int_free(&s->data);
}

// Стек полный
bool stack_is_full( const struct stack * s){
    if(s->data.size == s->count) return true;
    else return false;
}
// Стек пустой
bool stack_is_empty( const struct stack * s) {
    if(s->count == 0) return true;
    else return false;
}

// Поместить значение в стек
bool stack_push( struct stack* s, int64_t value ) {
    if (stack_is_full(s)) return false;
    array_int_set(s->data, s->count, value);
    s->count++;
    return true;
}

// Вынуть значение с вершины стека. Может вернуть none_int64
struct maybe_int64
stack_pop( struct stack* s ) {
    s->count--;
    return array_int_get(s->data, s->count);
}

void stack_print( const struct stack* s ) {
  for (size_t i = 0; i < stack_count( s ); i = i + 1 ) {
    print_int64( array_int_get( s->data, i).value );
    printf(" ");
  }
}


int main() {
    struct stack s;
    struct maybe_int64 digit;
    s = stack_create(5);
    stack_push(&s, 5);
    stack_push(&s, 6);
    stack_push(&s, 7);
    stack_push(&s, 8);
    stack_push(&s, 9);
    digit = stack_pop(&s);
    maybe_int64_print(digit);
    printf("%d", stack_is_full(&s));
    printf("\n");
    stack_print(&s);
    return 0;
}