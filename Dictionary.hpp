#include <string>
#include "DataStructs.cpp"

using namespace std;

class Dictionary
{
    private:
        string key, value;

    public:
        Dictionary(DataStructs *datastructure);
        bool isEmpty();
        void insert(string key, string value);
        string get(string k);
        void remove(string k);
        void destroy();
};