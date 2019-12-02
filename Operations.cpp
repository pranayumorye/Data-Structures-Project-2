#include "Dictionary.hpp"

class Operations {
	
	virtual Dictionary create();
	virtual bool isEmpty(Dictionary d);
	virtual void insert(Dictionary d,int key, int value);
	virtual string get(Dictionary d, Key k);
	virtual delete(Dictionary d, Key k);
	virtual destroy(Dictionary d);
};