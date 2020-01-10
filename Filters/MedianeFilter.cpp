#include "MedianeFilter.h"
#include "stdlib.h"

MedianFilter * MedianFilter::get_instance()
{
    return instance;
}
MedianFilter::MedianFilter()
{
    
}

int MedianFilter::get_result( int * buffer, int buffer_size )
{
    if (buffer_size > 20)
        return -1;
    
    int sort_buffer[20];
    for ( int i = 0; i < buffer_size; i++ )
    {
        sort_buffer[i] = buffer[i];
    }
    //сортировка буфера
    this->sort_buffer( sort_buffer, buffer_size );
    //выбор среднего значения
    return sort_buffer[buffer_size/2];
}

int compare(const void * arg1, const void * arg2)
{
    return *((int *)arg1) - *((int *)arg2);
}
void MedianFilter::sort_buffer(int * buffer, int buffer_size)
{
    qsort( (void*)buffer, (size_t) buffer_size, sizeof(int), &compare );
}

