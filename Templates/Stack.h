#ifndef STACK_H_
#define STACK_H_


#define MAX_STACK_SIZE 50

template <typename T>
class Stack
{
public:
    Stack()
    {
        items_quantity = 0;
        items_max_quantity = 0;
    }
    void set_items_source( T * o, int source_max_size )
    {
        items_buffer = o;
        items_max_quantity = source_max_size;
    }
    int get_stack_size()
    {
        return items_quantity;
    }
    int get_stack_max_size()
    {
        return items_max_quantity;
    }
    int push( T item )
    {
        if (items_quantity >= items_max_quantity)
            return -1;
        items_buffer[items_quantity] = item;
        items_quantity++;
        return 0;
    }
    T pop( )
    {
        if (items_quantity == 0)
            return items_buffer[0];
        items_quantity--;
        return items_buffer[items_quantity];
    }
private:
    T * items_buffer;
    int items_quantity;
    int items_max_quantity;
};


#endif