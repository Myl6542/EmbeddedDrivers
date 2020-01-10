#ifndef STACK_TEMPLATE_H_
#define STACK_TEMPLATE_H_

#include "stddef.h"


class ICloneable
{
public:
    virtual void clone(ICloneable * object) = 0;
	virtual ~ICloneable(){}
};

template <typename T>
class Stack
{
public:
    Stack()
    {
        objects_quantity = 0;
        max_objects = 0;
    }
    void set_items_source( T * o, int max_objects )
    {
        objects = o;
    }
    int get_stack_size()
    {
        return objects_quantity;
    }
    int get_stack_max_size()
    {
        return max_objects;
    }
    int push( ICloneable * object )
    {
        if (objects_quantity > max_objects)
            return -1;
        object->clone(&objects[objects_quantity]);
        objects_quantity++;
        return 0;
    }
    T * pop( )
    {
        if (objects_quantity <= 0)
            return NULL;
        objects_quantity--;
        return &objects[objects_quantity];
    }
private:
    T * objects;
    int objects_quantity;
    int max_objects;
};



#endif