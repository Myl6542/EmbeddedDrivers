#ifndef IFILTER_H_
#define IFILTER_H_

/*
*�������� ��� ����������
*/
class IFilter
{
public:
    virtual int get_result( int * buffer, int buffer_size ) = 0;
};


#endif