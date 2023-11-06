#include<inttypes.h>
#include<stdio.h>
#include<malloc.h>
#include <stdbool.h>


struct maybe_int64 {
  bool valid;
  int64_t value;
};

// Первый случай; создаем функцию в помощь
// Не бойтесь за производительность
struct maybe_int64 some_int64( int64_t i ) {
  return (struct maybe_int64) { .value = i, .valid = true };
}

// Второй случай; можно создать не функцию, 
// а константный экземпляр структуры
// Все поля инициализированы нулями
// .value = 0, .valid = false

void maybe_int64_print( struct maybe_int64 i ) {
    printf(" %" PRId64, i.value);
}

// Если обе упаковки содержат ошибку, то результат ошибка
// Если ровно одна упаковка содержит ошибку, то результат -- вторая
// Если обе упаковки содержат число, то результат это минимум из двух чисел.
struct maybe_int64 maybe_int64_min(struct maybe_int64 a, struct maybe_int64 b) {
   if (!a.valid && b.valid) { return b; }
   if (!b.valid && a.valid) { return a; }
   if ( a.value < b.value ) { return a; } else { return b; }   

}                                                                                                                                                         


int main() {
    
}