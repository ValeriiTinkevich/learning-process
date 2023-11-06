size_t read_size() 
{ 
    size_t i; 
    scanf("%zu", &i); 
    return i; 
}

struct maybe_array_int 
{
  struct array_int value;
  bool valid;
};

struct array_array_int 
{
  struct array_int* data;
  size_t size;
};

struct array_array_int array_array_int_read() 
{
    struct array_array_int array_array = {.data = NULL, .size = 0};
    size_t size = read_size();
    if (!size)
        return array_array;
    array_array.data = malloc(size * sizeof(struct array_int));
    array_array.size = size;  
    for (size_t i = 0; i < array_array.size; i++)
    {
        size = read_size();
        if (size == 0)
        {
            array_array.data[i].data = NULL;
            array_array.data[i].size = 0;
        }
        else
        {
            array_array.data[i].data = malloc(size * sizeof(int64_t));
            array_array.data[i].size = size;
            for (size_t j = 0; j < array_array.data[i].size; j++)
            {
                scanf("%" SCNd64, &array_array.data[i].data[j]);
            }
        }
    }

    return array_array;   
}

void array_array_int_print( struct array_array_int array) 
{
    for (size_t i = 0; i < array.size; i++)
    {
        for (size_t j = 0; j < array.data[i].size; j++)
            printf("%" PRId64 " ", array.data[i].data[j]);
        putchar('\n');
    }  
}

struct maybe_int64 array_array_int_min( struct array_array_int array ) 
{
    bool first_found = false;
    struct maybe_int64 min = { .valid = false };
    if (array.data && array.size)
    {
        for (size_t i = 0; i < array.size; i++)
        {
            for (size_t j = 0; j < array.data[i].size; j++)
            {
                if (!first_found)                   
                {
                    min.value = array.data[i].data[0];
                    min.valid = true;
                    first_found = true;
                    continue;
                }
                if (min.value > array.data[i].data[j])
                    min.value = array.data[i].data[j];
            }
        }
    }

    return min;
}

void array_array_int_normalize( struct array_array_int array, int64_t m) 
{
    for (size_t i = 0; i < array.size; i++)
        for (size_t j = 0; j < array.data[i].size; j++)
            array.data[i].data[j] -= m;
}

void array_array_int_free( struct array_array_int array ) 
{
    for (size_t i = 0; i < array.size; i++)
        if(array.data[i].data)
            free(array.data[i].data);
    free(array.data);
}