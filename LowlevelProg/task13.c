#include <stdio.h>
#include <inttypes.h>
#include <malloc.h>
#include <stdbool.h>
#include <string.h>

struct heap_string {
  char* addr;
};

// скопировать в кучу
struct heap_string halloc( const char* s ){
    char* newString;
    struct heap_string heapstr;
    int64_t length = 0;
    length = strlen(s);
    newString = malloc(sizeof(char) * len);

    strcpy(newString, s);
    heapstr.addr = newString;
    return heapstr;
}

// освободить память
void heap_string_free( struct heap_string h) {
    free(h.addr);
}