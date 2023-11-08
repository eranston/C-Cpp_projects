#ifndef DICTINERY_FILE
#define DICTINERY_FILE

#include "HashMap.hpp"



// new exception
class InvalidKey : public std::invalid_argument
{


public:
    InvalidKey(const std::string& msg) : std::invalid_argument(msg){}
    InvalidKey() : std::invalid_argument(""){}
};


/**
 * dictionary class that inherit from hashmap
 */
class Dictionary : public HashMap<std::string, std::string>
{
private:


public:
    // constructors
    Dictionary(){}
    Dictionary(std::vector<std::string> keys  ,
               std::vector<std::string> values) :
            HashMap(  keys  , values ){}
    //destructor
    ~Dictionary(){}

    //overloaded erase , erase a item and throw InavlidKey exception
    bool erase(const std::string &key) override
    {

        if(!contains_key(key))
        {
            throw InvalidKey("invalid key");
        }
        remove_element(key);
        while(get_load_factor() < MIN_ALPHA_RATIO && ((*this).capacity()>1))
        {
            decrease_map_and_update();
        }
        return true;
    }

    //enter all items from type std::pair<std::string, std::strin> to the data
    //base of Dictionary;
    template <class It>
    void update(It begin , It end)
    {
        while(begin != end)
        {
            if(contains_key((*begin).first))
            {
                (*this)[(*begin).first] = (*begin).second;
            }
            (*this).insert((*begin).first , (*begin).second);
            begin++;
        }
    }

};


#endif