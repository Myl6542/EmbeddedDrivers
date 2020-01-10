#ifndef LIST_H_
#define LIST_H_


#define MAX_LIST_SIZE 50

template<typename T>
class List
{
public:
    List()
    {
        items_quantity = 0;
        list_max_size = 0;
    }
    void set_items_source( T * items_source, int source_buffer_size )
    {
        items_buffer = items_source;
        list_max_size = source_buffer_size;
    }
    T * get_items_source ()
    {
        return items_buffer;
    }
    int add_item ( T item )
    {
        if (items_quantity >= list_max_size)
            return -1;
        items_buffer[items_quantity] = item;
        items_quantity++;
        return 0;
    }
    int get_items_quantity ()
    {
        return items_quantity;
    }
    T get_item ( int num )
    {
        return items_buffer[num];
    }
    int remove_item( int num )
    {
        shift_objects(num);
        items_quantity--;
        return 0;
    }
    int is_item_exist( T item )
    {
        for (int i = 0; i < items_quantity; i++)
        {
            if ( items_buffer[i] == item )
                return 1;
        }
        return -1;
    }
    int reload()
    {
        items_quantity = 0;
        return 0;
    }
private:
    T * items_buffer;
    int items_quantity;
    int list_max_size;
    
    
    
    //сдвигает все элементы, на место указанной позиции
    int shift_objects(int position)
    {
        for ( int i = position; i < items_quantity - 1; i++ )
        {
            items_buffer[i] = items_buffer[i + 1];
        }
        return 0;
    }
};







#endif
