#include <bits/stdc++.h>
#include <time.h>
int TCSIZE = 500;

using namespace std;
// using namespace std::chrono;

const int T_S = 100000;


class HashTable
{
   public:
      string k;
      string v;
      HashTable(string k, string v)
      {
         this->k = k;
         this->v = v;
      }
};
class DelNode:public HashTable
{
   private:
      static DelNode *en;
      DelNode():HashTable("", "") {}
   public:
      static DelNode *getNode() {
         if (en == NULL)
            en = new DelNode();
         return en;
      }
};

DelNode *DelNode::en = NULL;

class HashMapTable
{
   private:
    HashTable **ht;
   public:
    HashMapTable()
    {
        ht = new HashTable* [T_S];
        for (int i = 0; i < T_S; i++)
        {
        ht[i] = NULL;
        }
    }
    
    int myHash(string s)
    {
        int len = s.length();
        unsigned int hash = 5381;
        int c, i=0;

        while (i<len)
        {
            c = int(s[i++]);
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
        }
        return hash%T_S;
    }


      void Insert(string k, string v) {
        int hash_val = myHash(k);
        int init = -1;
        int delindex = -1;
        while (hash_val != init && (ht[hash_val]  == DelNode::getNode() || ht[hash_val] != NULL && ht[hash_val]->k != k)) {
        if (init == -1)
            init = hash_val;
        if (ht[hash_val] == DelNode::getNode())
            delindex = hash_val;
            hash_val = (hash_val + 1)%T_S;
        }
        if (ht[hash_val] == NULL || hash_val == init) {
        if(delindex != -1)
            ht[delindex] = new HashTable(k, v);
        else
            ht[hash_val] = new HashTable(k, v);
        }
        if(init != hash_val) {
        if (ht[hash_val] != DelNode::getNode()) {
            if (ht[hash_val] != NULL) {
                if (ht[hash_val]->k== k)
                    ht[hash_val]->v = v;
            }
        } else
        ht[hash_val] = new HashTable(k, v);
        }
    }
      string SearchKey(string k) {
        int hash_val = myHash(k);
        int init = -1;
        while (hash_val != init && (ht[hash_val] == DelNode::getNode() || ht[hash_val] != NULL && ht[hash_val]->k!= k)) {
        if (init == -1)
            init = hash_val;
            hash_val = (hash_val + 1)%T_S;
        }
        if (ht[hash_val] == NULL || hash_val == init)
        return "";
        else
        return ht[hash_val]->v;
    }
    void Remove(string k)
    {
        int hash_val = myHash(k);
        int init = -1;
        while (hash_val != init && (ht[hash_val] == DelNode::getNode() || ht[hash_val] != NULL && ht[hash_val]->k!= k))
        {
        if (init == -1)
            init = hash_val;
            hash_val = (hash_val + 1)%T_S;
        }
        if (hash_val != init && ht[hash_val] != NULL) {
        delete ht[hash_val];
        ht[hash_val] = DelNode::getNode();
        }
    }
    //   ~HashMapTable()
    // {
    //     delete[] ht;
    // }
};


//test insertion of dictionary key-value pairs
double tc1(HashMapTable hash)
{
    ifstream filereader("words.txt");
    // ofstream filewriter;
    // filewriter.open("tc1Hashtime.txt", std::ios_base::app);
    string word;


    // auto start = high_resolution_clock::now();
    clock_t t;
    t = clock();
    for(int i=0; i<TCSIZE; i++)
    {
        filereader>>word;
        hash.Insert(word, "testvalue");
    }
    t = clock() - t;
    double time_taken = ((double)t);
    // auto stop = high_resolution_clock::now();

    // auto duration = duration_cast<microseconds>(stop - start);
    // string exectime = to_string(duration.count());
    // filewriter<<exectime<<"\n";

    filereader.close();
    // filewriter.close();
    // return duration.count();
    return time_taken;
}

//test search of words, 50% found, 50% not found
double tc2(HashMapTable hash)
{
    ifstream filereader("words.txt");
    // ofstream filewriter;
    // filewriter.open("tc2Hashtime.txt", std::ios_base::app);
    string word;

    vector<string> words;

    //store words in a vector
    for(int i=0; i<TCSIZE*2; i++)
    {
        filereader>>word;
        words.push_back(word);
    }
    // cout<<words.size()<<endl;
    //insert words
    for(int i=0; i<TCSIZE; i++)
    {
        hash.Insert(words[i], "testvalue");
    }

    //search available words
    // auto start = high_resolution_clock::now();
    clock_t t;
    t = clock();
    for(int i=0; i<TCSIZE/2; i++)
    {
        hash.SearchKey(words[i]);
    }
    //search unavailable words
    for(int i=TCSIZE; i<TCSIZE+250; i++)
    {
        hash.SearchKey(words[i]);
    }
    t = clock() - t;
    double time_taken = ((double)t);
    // auto stop = high_resolution_clock::now();

    // auto duration = duration_cast<microseconds>(stop - start);
    // string exectime = to_string(duration.count());
    // filewriter<<exectime<<"\n";

    // filewriter.close();
    filereader.close();
    // return duration.count();
    return time_taken;
}

//test deletion of entire dictionary
double tc3(HashMapTable hash)
{
    ifstream filereader("words.txt");
    // ofstream filewriter;
    // filewriter.open("tc3Hashtime.txt", std::ios_base::app);
    string word;

    vector<string> words;

    //store words in a vector
    for(int i=0; i<TCSIZE+10; i++)
    {
        filereader>>word;
        words.push_back(word);
    }

    //insert words
    for(int i=0; i<TCSIZE; i++)
    {
        hash.Insert(words[i], "testvalue");
    }

    //delete all the stored words
    // auto start = high_resolution_clock::now();
    clock_t t;
    t = clock();
    for(int i=0; i<TCSIZE; i++)
    {
        hash.Remove(words[i]);
    }
    t = clock() - t;
    double time_taken = ((double)t);
    // auto stop = high_resolution_clock::now();

    // auto duration = duration_cast<microseconds>(stop - start);
    // string exectime = to_string(duration.count());
    // filewriter<<exectime<<"\n";

    filereader.close();
    // filewriter.close();
    // return duration.count();
    return time_taken;
}


int main()
{
    HashMapTable hash;
    ofstream filewriter;
    filewriter.open("tc1Hashtime.txt", std::ios_base::app);

    //iterate over 10 different dictionary sizes
    for(int i = 0; i<10; i++)
    {
        double sum = 0.0;
        //iterate over the testcase values multiple times and calculate their averages
        for(int j=0; j<100; j++)
        {
            sum += tc1(hash);
        }
        filewriter<<"Average time for "<<TCSIZE<<" inputs is: "<<double(sum/100.0)<<endl;
        TCSIZE += 500;
    }

    return 0;
}