#include "Dictionary.hpp"


    Dictionary::Dictionary()
    {
        this->ds =  NULL;
    }

    Dictionary::Dictionary(DataStructs *datastructure)
    {
        this->ds = datastructure;
    }

    bool Dictionary::isEmpty()
    {
        return ds->isEmpty();
    }

    void Dictionary::insert(string key, string value)
    {
        ds->insert(key, value);
    }

    string Dictionary::get(string k)
    {
        return ds->get(k);
    }

    void Dictionary::remove(string k)
    {
        ds->remove(k);
    }

    void Dictionary::destroy()
    {
        ds->destroy();
    }
    
