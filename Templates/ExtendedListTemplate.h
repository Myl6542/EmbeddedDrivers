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
    //конструктор
    ExtendedList()
    {
        objects_quantity = 0;
        list_max_size = 0;
    }
    //установить источник объектов(выделенная память под объекты)
    void set_items_source( T * o, int source_max_size )
    {
        objects = o;
        list_max_size = source_max_size;
    }
    //вернуть размер списка
    int get_list_size()
    {
        return objects_quantity;
    }
    //добавить объект в список
    int add_object( IExtendedList * object )
    {
        object->clone(&objects[objects_quantity]);
        objects_quantity++;
        return 0;
    }
    //вернуть объект из списка по номеру
    T * get_object( int num )
    {
        if (num >= objects_quantity)
            return NULL;
        return &objects[num];
    }
    //проверка существует ли такой объект в списке
    int is_object_exist ( IExtendedList * o )
    {
        for (int i = 0; i < objects_quantity; i++ )
        {
            if ( o->is_equal( (IExtendedList*)&objects[i] ) == 1 )
                return 1;
        }
        return -1;
    }
    //удалить объект сравнивая с заданным
    int remove_object ( IExtendedList * o )
    {
        //вычисление позиции объекта в списке
        int object_position = get_object_position(o);
        //сдвигает все элементы влево, на место указанной позиции
        shift_objects(object_position);
        //уменьшить кол-во объектов в списке
        objects_quantity--;
        return 0;
    }
    //удалить объект по номеру
    int remove_object ( int num )
    {
        //сдвигает все элементы влево, на место указанной позиции
        shift_objects(num);
        //уменьшить кол-во объектов в списке
        objects_quantity--;
        return 0;
    }    
    
private:
    int get_object_position( IExtendedList * o )
    {
        //вычисление позиции объекта в списке
        for ( int i = 0; i < objects_quantity; i++ )
        {
            if ( o->is_equal( (IExtendedList*)&objects[i] ) == 1 )
                return i;
        }
        return -1;
    }
    
    //сдвигает все элементы, на место указанной позиции
    int shift_objects(int position)
    {
        for ( int i = position; i < objects_quantity - 1; i++ )
        {
            objects[i + 1].clone( &objects[i] );
        }
        return 0;
    }
    
    //список объектов в списке
    T * objects;
    //кол-во объектов в списке
    int objects_quantity;
    //максимальное кол-во объектов в списке
    int list_max_size;
};



#endif