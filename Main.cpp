#include "AVL.cpp"
#include "Dictionary.hpp"
#include <iostream>


int main()
{
    
    AVL *dictusingavl = new AVL();

    Dictionary *dict = new Dictionary(dictusingavl);

    cout<<dict->isEmpty();

    //perform operations using the object created


}