#ifndef MOVING_AVERAGE_FILTER_H_
#define MOVING_AVERAGE_FILTER_H_
/*
*класс реализует фильтр "скользящее среднее"
*/

#include "IFilter.h"

class MovingAverageFilter: public IFilter
{
public:
    static MovingAverageFilter * get_instance();
    
    int get_result(int * buffer, int buffer_size);
private:
    static MovingAverageFilter * instance;
    MovingAverageFilter();
};




#endif