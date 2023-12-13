#include <stdio.h>
#include <inttypes.h>
#include <malloc.h>
#include <stdbool.h>
#include <string.h>


// контекст для обработчиков событий
// нас интересует, сколько раз мы уже нажали на первую кнопку
struct context { int64_t counter; };

// У кнопки есть имя и обработчик
struct button {
  const char* label;
  void (*handler)( struct button*, struct context* );
};

// Для удобства создадим тип обработчика
typedef void (onclick_handler)(struct button*, struct context*);

// Массив из нескольких кнопок
struct buttons { struct button* array; size_t count; } ;


// Вызвать событие "Нажатие на кнопку"
void click(const struct button* b, struct context* ctx) {
  b->handler( b, ctx );
}


// Обработчик нажатия на первую кнопку
void print_meow_handler(const struct button* b, struct context* ctx) {
  printf("Meow!\n");
  ctx-> counter = ctx-> counter + 1;
}

// Обработчик нажатия на вторую кнопку
void print_ctx_handler(const struct button* b, struct context* c) {
  printf("Said \"Meow!\" %" PRId64 " times.\n", c->counter );
}

// Показать кнопки
void print_buttons( struct buttons buttons ) {
  for (size_t i = 0; i < buttons.count; i = i + 1 ) {
    printf("%zu : %s \n", i, buttons.array[i].label );
  }
}

// Цикл для ввода номера кнопки и нажатия на неё
void prompt_click_button( struct buttons buttons, struct context* ctx ) {
  for(;;) {
    print_buttons( buttons );
    printf("Input button index: ");
    const size_t idx = read_size();
    if ( idx >= buttons.count ) { printf("No such button, bye.\n"); break; }
    else { click( buttons.array + idx, ctx ); }
  }
}


int main() {

// Две кнопки
  struct button buttons[] = {
    { "Say Meow" , print_meow_handler },
    { "Status", print_ctx_handler },
  };
// Количество кнопок
  const size_t count = sizeof(buttons) / sizeof(buttons[0]);

// Экземпляр контекста
  struct context ctx = { 0 };

  prompt_click_button( (struct buttons) { buttons, count } , &ctx );

  return 0;
}