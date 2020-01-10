#ifndef MEDIANE_FILTER_H_
#define MEDIANE_FILTER_H_
/*
*ћедианный фильтр
*класс реализует медианный фильтр
*значени€ добавл€ютс€ в массив, сортируютс€ в пор€дке возрастани€
*из отсортированного массива выбираетс€ значение посередине массива
*/
#include "IFilter.h"

class MedianFilter: public IFilter
{
public:
    static MedianFilter * get_instance();
    MedianFilter();
   //override
    int get_result( int * buffer, int buffer_size );
private:
    static MedianFilter * instance;
    void sort_buffer(int * buffer, int buffer_size);
    
};

#endif