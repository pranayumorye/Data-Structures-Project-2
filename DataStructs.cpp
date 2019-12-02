using namespace std;
#include <string>

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