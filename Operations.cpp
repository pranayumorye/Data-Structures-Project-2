#ifndef OPERATIONS_HPP
#define OPERATIONS_HPP

using namespace std;

class Operations {
	virtual bool isEmpty();
	virtual void insert(string key, string value);
	virtual string get(string k);
	virtual void remove(string k);
	virtual void destroy();
};

#endif