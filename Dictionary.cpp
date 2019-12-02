#include "Dictionary.hpp"

class Dictionary
{
    private:
        DataStructs *ds;
    public:

        Dictionary(DataStructs *datastructure)
        {
            this->ds = datastructure;
        }

        bool isEmpty()
        {
            return ds->isEmpty();
        }

        void insert(string key, string value)
        {
            ds->insert(key, value);
        }

        string get(string k)
        {

        }

        void remove(string k)
        {

        }

        void destroy()
        {

        }
        

};