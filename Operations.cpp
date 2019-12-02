class Operations {
	virtual bool isEmpty();
	virtual void insert(string key, string value);
	virtual string get(string k);
	virtual void remove(string k);
	virtual void destroy();
};