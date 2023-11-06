#include <inttypes.h>
#include <stdio.h>

void f() {
    int64_t i64 = -10;
    uint64_t u64 = 100;
    printf( "Signed 64-bit integer:   %" PRId64  "\n", i64 );
    printf( "Unsigned 64-bit integer: %" PRIu64  "\n", u64 );
    printf( "Pointer, hexadecimal     %" PRIxPTR "\n", &i64 );

    //scanf( "%" SCNd64, &i64 );
    //scanf( "%" SCNu64, &u64 );
}


int main() {
    f();
}