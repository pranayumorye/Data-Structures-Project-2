#ifndef DATASTRUCTS_HPP
#define DATASTRUCTS_HPP

#include <string>
#ifndef OPERATIONS_CPP
#define OPERATIONS_CPP
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
#endif