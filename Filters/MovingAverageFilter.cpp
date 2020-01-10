#include "MovingAverageFilter.h"


MovingAverageFilter * MovingAverageFilter::get_instance()
{
    return instance;
}
MovingAverageFilter::MovingAverageFilter()
{
    
}
int MovingAverageFilter::get_result(int * buffer, int buffer_size)
{
    int tmp = 0;
    int result = 0;
    for (int i = 0 ; i < buffer_size; i++)
    {
        tmp += buffer[i];
    }
    result = tmp/buffer_size;
    return result;
}