#ifndef LIST_TEMPLATE_H_
#define LIST_TEMPLATE_H_

#define MAX_LIST_OBJECTS 50



class ICloneable
{
public:
    virtual void clone(ICloneable * object) = 0;
	virtual ~ICloneable() {  }
};





template <typename T>
class List_s
{
public:
    List_s()
    {
        objects_quantity = 0;
    }
    void set_items_source( T * o )
    {
        objects = o;
    }
    int get_list_size()
    {
        return objects_quantity;
    }
    int get_list_max_size()
    {
        return MAX_LIST_OBJECTS;
    }
    int add_object( ICloneable * object )
    {
        object->clone(&objects[objects_quantity]);
        objects_quantity++;
        return 0;
    }
    T * get_object( int num )
    {
        if (num >= objects_quantity)
            return NULL;
        return &objects[num];
    }
    void remove_object ( int num )
    {
        shift_objects(num);
        objects_quantity--;
    }
private:
    T * objects;
    int objects_quantity;
    
    
    
    //сдвигает все элементы, на место указанной позиции
    int shift_objects(int position)
    {
        for ( int i = position; i < objects_quantity - 1; i++ )
        {
            objects[i + 1].clone( &objects[i] );
        }
    }
};



#endif