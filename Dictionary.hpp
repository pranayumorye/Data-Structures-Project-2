#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP


#include <string>
#include "DataStructs.hpp"

using namespace std;

class Dictionary
{
    private:
        string key, value;
        DataStructs *ds;

    public:
        Dictionary();
        Dictionary(DataStructs *datastructure);
        // bool isEmpty();
        void insert(string key, string value);
        string get(string k);
        void remove(string k);
        void destroy();
};

#endif