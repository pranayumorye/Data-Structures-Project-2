#ifndef DATASTRUCTS_HPP
#define DATASTRUCTS_HPP


#include <string>
#include "Operations.cpp"

using namespace std;

class DataStructs
{
    public:
        void create();
        bool isEmpty();
        void insert(string key, string value);
        string get(string k);
        void remove(string k);
        void destroy();
};

#endif