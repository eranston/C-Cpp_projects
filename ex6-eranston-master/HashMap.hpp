#ifndef HASH_MAP_FILE
#define HASH_MAP_FILE


#include <iostream>
#include <vector>
#include <set>
#include <algorithm>


#define STARTING_CAPACITY 16
#define MIN_ALPHA_RATIO 0.25
#define MAX_ALPHA_RATIO 0.75



template <class KeyT,class ValueT>
class HashMap
{
private:
    typedef std::vector<std::vector<std::pair<KeyT,ValueT>>*>* database_type;
    size_t _size;
    size_t _capacity;
    database_type _data_base;
protected:
    //the hashing function
    size_t hash_func(const KeyT key) const
    {
       //ToDo: use std::hash to convert key to
       size_t output = std::hash<KeyT>()(key);
       return (output&(_capacity-1));
    }

    /**
     * add element to the database and resize it if neccesery
     * @param element the element we want to add
     */
    void add_element(const std::pair<KeyT,ValueT>& element)
    {
        int index = hash_func(element.first);
        (*_data_base)[index]->push_back(element);
        _size++;
    }


    //helper function that remove all items in the hashmap
    void remove_element(const KeyT key)
    {
        int index = hash_func(key);
        auto inner_vec_ptr = (*_data_base)[index];
        for(size_t i =0; i < (*inner_vec_ptr).size() ; i++)
        {
            if((*inner_vec_ptr)[i].first == key)
            {
                (*(*_data_base)[index]).erase((*inner_vec_ptr).begin() + i);
                _size--;
                break;
            }
        }
    }



    /**
     * pop all items from database and return it as a vector
     * @return vector of all the items in database
     */
    std::vector<std::pair<KeyT,ValueT>> pop_all_items()
    {
        std::vector<std::pair<KeyT,ValueT>> holding_vec; //hold all values
        for(size_t i = 0 ; i< _capacity ; i++)
        {
            auto inner_vector_ptr = (*_data_base)[i];
            auto size_of_inner_vec = (*inner_vector_ptr).size();
            if(size_of_inner_vec > 0)
            {
                for(size_t j =size_of_inner_vec ; j>0 ; j--)
                {
                    std::pair<KeyT,ValueT> copy_pair =
                            (*inner_vector_ptr)[j-1];
                    holding_vec.push_back(copy_pair);
                    (*inner_vector_ptr).pop_back();
                }
            }
        }
        return holding_vec;
    }


    //helper fucntion that decrease the database size(capacity)
    void decrease_map_and_update()
    {
        auto items = pop_all_items();
        for(size_t i = _capacity/2; i<_capacity ; i++ )
        {
            delete (*_data_base)[i];
            (*_data_base).pop_back();
        }
        _capacity = _capacity /2;
        _size = 0;
        for(auto item:items)
        {
            (*this).insert(item.first , item.second);
        }

    }



    //helper function that increase the database size (capacity)
    void increase_map_and_update()
    {
        auto items = pop_all_items();
        for(size_t i =0; i<_capacity ; i++)
        {
            (*_data_base).push_back(new std::vector<std::pair<KeyT,ValueT>>);
        }
        _capacity = _capacity *2;
        _size = 0;
        for(auto item:items)
        {

            (*this).insert(item.first , item.second);
        }
    }


public:
    //default constructor
    HashMap()
    {
        _size = 0;
        _capacity = STARTING_CAPACITY;
        _data_base = new std::vector<std::vector<std::pair<KeyT,ValueT>>*>;
        for(size_t i = 0; i< _capacity ; i++)
        {
            _data_base->push_back(new std::vector<std::pair<KeyT,ValueT>>);
        }
    }

    //constrctor
    HashMap( std::vector<KeyT> keys  ,  std::vector<ValueT> values )
    {

        if(keys.size() != values.size())
        {
            throw std::length_error("vector not same size");
        }
        _capacity = STARTING_CAPACITY;
        _size = 0;
        _data_base = new std::vector<std::vector<std::pair<KeyT,ValueT>>*>;
        for(size_t i = 0; i< _capacity ; i++)
        {
            _data_base->push_back(new std::vector<std::pair<KeyT,ValueT>>);
        }

        for(size_t i = 0 ; i< keys.size() ; i++)
        {
            (*this)[keys[i]]= values[i];
        }
    }

    // destructor
    virtual ~HashMap()
    {
        for(size_t i =0; i<_capacity;i++)
        {
            delete (*_data_base)[i];
        }
        delete _data_base;
    }


    // copy constructor
    HashMap(const HashMap& hm_obj)
    {

        _size = hm_obj.size();
        _capacity = hm_obj.capacity();
        _data_base = new std::vector<std::vector<std::pair<KeyT,ValueT>> *>;
        for (size_t i = 0; i < _capacity; i++)
        {
            _data_base->push_back(new std::vector<std::pair<KeyT,ValueT>>);
        }

        for (size_t i = 0; i < hm_obj._capacity; i++)
        {
            auto inner_vec = *((*(hm_obj._data_base))[i]);
            for (size_t j = 0; j < inner_vec.size(); j++)
            {
                std::pair<KeyT,ValueT> new_pair = inner_vec[j];
                (*((*_data_base)[i])).push_back(new_pair);
            }
        }
    }

    /**
     * insert key and value pair to the hashmap, make the hashmap bigger if
     * needed
     * @param key
     * @param value
     * @return true if added the pair successfully  , return false if key in
     * map allready
     */
    bool insert(KeyT key , ValueT value)
    {
        if(contains_key(key))
        {
            return false;
        }
        add_element(std::pair<KeyT,ValueT>(key,value));
        if(get_load_factor() > MAX_ALPHA_RATIO)
        {
            increase_map_and_update();
        }
        return true;

    }


    /**
     * check if a key is in the hashmap
     * @param key the key we check
     * @return true if the key in the map , false otherwise
     */
    bool contains_key(const KeyT key) const
    {
        size_t index = hash_func(key);
        auto inner_vector = *((*_data_base)[index]);
        for(const auto& it : inner_vector)
        {
            if(it.first == key)
            {
                return true;
            }
        }
        return false;
    }

    /**
     * check if the hashmap is empty
     * @return true if empty and false otherwise
     */
    bool empty() const
    {
        return !(_size > 0);
    }


    /**
     * getter function
     * @return the current load factor of the hashmap
     */
    double get_load_factor() const
    {
        return (((double)_size)/((double)_capacity));
    }


    /**
     * getter function
     * @return the number of items in the hashmap
     */
    size_t size() const
    {
        return _size;
    }


    /**
     * getter function
     * @return return the maximum items the hashmap can handle
     */
    size_t capacity() const
    {
        return _capacity;
    }


    /***
     * return the value at the given key ,throw exception if not in hashmap
     * @param key
     * @return the value of the corresponding key
     */
    ValueT& at(const KeyT key) const
    {
        int index = hash_func(key);
        auto inner_vector = ((*_data_base)[index]);
        for(size_t i = 0; i< inner_vector->size(); i++)
        {
            if((*inner_vector)[i].first == key)
            {
                return ((*inner_vector)[i]).second;
            }
        }
        throw std::runtime_error("key not found");
    }

    const ValueT& operator[](const KeyT key) const
    {
        size_t index = hash_func(key);
        auto inner_vector = *((*_data_base)[index]);
        for(size_t i =0 ; i< inner_vector.size() ; i++)
        {
            if(inner_vector[i] == key)
            {
                return inner_vector[i].second;
            }
        }
    }

    ValueT& operator[](const KeyT _key)
    {
        int index = hash_func(_key);
        auto inner_function_ptr = ((*_data_base)[index]);
        for(size_t i =0 ; i< (*inner_function_ptr).size() ; i++)
        {
            if((*inner_function_ptr)[i].first == _key)
            {
                return (*inner_function_ptr)[i].second;
            }
        }
        (*this).insert(_key, ValueT());

        return ((*this).at(_key));

    }

    /**
     * virtual function , get a key and erase the item coorespond to that key,
     * change size of the _data_base of the hashmap if needed
     * @param key the key of the item we want to delete
     * @return true if item not in _data_base and we erased it successfully,
     *          false otherwise
     */
    virtual bool erase(const KeyT& key)
    {
        if(!contains_key(key))
        {
            return false;
        }
        remove_element(key);
        while(get_load_factor() < MIN_ALPHA_RATIO && (_capacity>1))
        {
            decrease_map_and_update();
        }
        return true;
    }


    /**
     * return the index of the bucket where the key is in
     * @param key
     * @return return the index of the bucket where the key is in
     */
    int bucket_index(const KeyT& key) const
    {
        int index = hash_func(key);
        (*this).at(key);
        return index;
    }


    /**
     * the size of the bucket that the key is in
     * @param key key for the hashmap
     * @return the size of the bucket size the index is in
     */
    int bucket_size(const KeyT key) const
    {
        int index = hash_func(key);
        auto inner_vector_index = (*_data_base)[index];
        (*this).at(key);
        return inner_vector_index->size();
    }

    /**
     * clear all items in the _data_base of the map , _capacity stays the same
     */
    void clear()
    {
        (*this).pop_all_items();
        _size = 0;
    }

    friend bool operator!=(const HashMap rhs , const HashMap lhs)
    {
        auto rhs_copy = rhs;
        auto lhs_copy = lhs;
        auto lhs_items = lhs_copy.pop_all_items();
        auto rhs_items = rhs_copy.pop_all_items();
        return (rhs_items != lhs_items);
    }

    friend bool operator==(const HashMap rhs , const HashMap lhs)
    {
        auto rhs_copy = rhs;
        auto lhs_copy = lhs;
        auto lhs_items = lhs_copy.pop_all_items();
        auto rhs_items = rhs_copy.pop_all_items();
        return (rhs_items == lhs_items);
    }

    HashMap& operator=(const HashMap& rhs)
    {
        if(this == &rhs)
        {
            return *this;
        }
        for(size_t i =0; i<_capacity;i++)
        {
            delete (*_data_base)[i];
        }
        delete _data_base;
        _size = rhs.size();
        _capacity = rhs.capacity();
        _data_base = new std::vector<std::vector<std::pair<KeyT,ValueT>>*>;
        for(int i = 0; i< _capacity ; i++)
        {
            _data_base->push_back(new std::vector<std::pair<KeyT,ValueT>>);
            auto rhs_inner_vec = *(*rhs._data_base)[i];
            for(auto pair: rhs_inner_vec)
            {
                std::pair<KeyT,ValueT> new_pair = pair;
                (*(*_data_base)[i]).push_back(new_pair);
            }
        }
        return (*this);
    }

    class ConstIterator {
    private:
        const HashMap& map;
        size_t rows; // current index of rows in the _data_base of map
        size_t cols; // current index of cols in the _data_base of map


    public:
        /* ITERATOR TRAITS - must be defined (and public) in the iterator,
         *
         * for it to work with all STL algorithms.
         * Comment this out and attempt to call std::find with this iterator
         * to watch the runtime error
         * you will get if you don't define iterator traits */
        typedef  std::pair<KeyT,ValueT> value_type;
        typedef const std::pair<KeyT,ValueT>& reference;
        typedef const std::pair<KeyT,ValueT>* pointer;
        typedef std::ptrdiff_t difference_type; // irrelevant here, as we have
        // no difference - but still required
        typedef std::forward_iterator_tag iterator_category;

        ConstIterator( size_t row , size_t col , const HashMap& h_map)
        :map(h_map) , rows(row) , cols(col)
        {

            if(rows < map.capacity())
            {
                auto row_vec = *(*map._data_base)[rows];
                if(row_vec.size() == 0)
                {
                    ++(*this);
                }
            }
        }


        ConstIterator operator++(int)
        {
            auto it = ConstIterator(rows , cols ,map);
            cols++;
            auto current_row = *(*map._data_base)[rows];
            while(cols >= current_row.size() && rows < map._capacity)
            {
                cols = 0;
                rows++;
                if(rows >= map.capacity())
                {
                    break;
                }
                current_row = *(*map._data_base)[rows];
            }
            return it;
        }

        ConstIterator& operator++()
        {

            cols++;
            auto current_row = *(*map._data_base)[rows];
            while(cols >= current_row.size() && rows < map._capacity)
            {
                cols = 0;
                rows++;
                if(rows >= map.capacity())
                {
                    break;
                }
                current_row = *(*map._data_base)[rows];
            }
            return *this;
        }


        bool operator==(const ConstIterator& rhs) const
        {

            return ((&map == &rhs.map) && (rows == rhs.rows) &&
            (cols == rhs.cols));
        }

        bool operator!=(const ConstIterator& rhs) const
        {

            return ((&map != &rhs.map) || (rows != rhs.rows) ||
            (cols != rhs.cols));
        }

        reference operator*() const
        {
            return (*(*map._data_base)[rows])[cols];
        }

        pointer operator->() const
        {
            return &((*(*map._data_base)[rows])[cols]);

        }
    };
    using const_iterator = ConstIterator;
    const_iterator begin() const { return ConstIterator(0,0,*this); }
    const_iterator end() const{return ConstIterator(_capacity , 0,(*this));}
    const_iterator cend() const{return ConstIterator(_capacity , 0,(*this));}
    const_iterator cbegin() const { return ConstIterator(0,0,*this); }
};




#endif