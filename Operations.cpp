#include "Dictionary.hpp"

class Operations {
	
	virtual Dictionary create();
	virtual bool isEmpty(Dictionary d);
	virtual void insert(Dictionary d,string key, string value);
	virtual string get(Dictionary d, string k);
	virtual void remove(Dictionary d, string k);
	virtual void destroy(Dictionary d);
};