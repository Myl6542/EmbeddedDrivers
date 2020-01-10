#ifndef EXTENDED_LIST_TEMPLATE_H_
#define EXTENDED_LIST_TEMPLATE_H_

#include "stddef.h"


#define MAX_EXTENDED_LIST_OBJECTS 50



class IExtendedList
{
public:
    virtual void clone(IExtendedList * object) = 0;
    virtual int is_equal(IExtendedList * object ) = 0;
	virtual ~IExtendedList(){ }
};





template <typename T>
class ExtendedList
{
public:
    //�����������
    ExtendedList()
    {
        objects_quantity = 0;
        list_max_size = 0;
    }
    //���������� �������� ��������(���������� ������ ��� �������)
    void set_items_source( T * o, int source_max_size )
    {
        objects = o;
        list_max_size = source_max_size;
    }
    //������� ������ ������
    int get_list_size()
    {
        return objects_quantity;
    }
    //�������� ������ � ������
    int add_object( IExtendedList * object )
    {
        object->clone(&objects[objects_quantity]);
        objects_quantity++;
        return 0;
    }
    //������� ������ �� ������ �� ������
    T * get_object( int num )
    {
        if (num >= objects_quantity)
            return NULL;
        return &objects[num];
    }
    //�������� ���������� �� ����� ������ � ������
    int is_object_exist ( IExtendedList * o )
    {
        for (int i = 0; i < objects_quantity; i++ )
        {
            if ( o->is_equal( (IExtendedList*)&objects[i] ) == 1 )
                return 1;
        }
        return -1;
    }
    //������� ������ ��������� � ��������
    int remove_object ( IExtendedList * o )
    {
        //���������� ������� ������� � ������
        int object_position = get_object_position(o);
        //�������� ��� �������� �����, �� ����� ��������� �������
        shift_objects(object_position);
        //��������� ���-�� �������� � ������
        objects_quantity--;
        return 0;
    }
    //������� ������ �� ������
    int remove_object ( int num )
    {
        //�������� ��� �������� �����, �� ����� ��������� �������
        shift_objects(num);
        //��������� ���-�� �������� � ������
        objects_quantity--;
        return 0;
    }    
    
private:
    int get_object_position( IExtendedList * o )
    {
        //���������� ������� ������� � ������
        for ( int i = 0; i < objects_quantity; i++ )
        {
            if ( o->is_equal( (IExtendedList*)&objects[i] ) == 1 )
                return i;
        }
        return -1;
    }
    
    //�������� ��� ��������, �� ����� ��������� �������
    int shift_objects(int position)
    {
        for ( int i = position; i < objects_quantity - 1; i++ )
        {
            objects[i + 1].clone( &objects[i] );
        }
        return 0;
    }
    
    //������ �������� � ������
    T * objects;
    //���-�� �������� � ������
    int objects_quantity;
    //������������ ���-�� �������� � ������
    int list_max_size;
};



#endif