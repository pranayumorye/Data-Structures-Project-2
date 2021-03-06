#include<bits/stdc++.h>
#include <time.h>

int TCSIZE = 500;

using namespace std;
// using namespace std::chrono;

class TrieNode{
    public:
    string meaning;
    map<char,TrieNode*> child_map;
    bool endOfWord;

    TrieNode(){
        endOfWord = false;
    }
};

TrieNode* removeNode(TrieNode* root,string k,int depth){

    if(root == NULL){
        return NULL;
    }

    //Found the leaf and
    if(depth == k.size()){

         // This node is no more end of word after 
        // removal of given key 
        if(root->endOfWord){
            root->endOfWord = false;
        }

        // If not prefix of any other word 
        if(root->child_map.empty()){
            delete(root);
        }
        return root;

    }

    //Recur for intermediate roots
    if(!removeNode(root->child_map[k[depth]],k,depth+1)){
        root->child_map.erase(k[depth]);
    }

    if(root->child_map.empty() && root->endOfWord == false){
        delete(root);
        root = NULL;
    }
    return root;
}

void deleteNode(TrieNode* node){

        if(node == NULL) return;
        for(map<char, TrieNode*>::iterator it = node->child_map.begin(); it!= node->child_map.end();it++){
            deleteNode(it->second);;
        }
        delete(node);
        node = NULL;
}

class Trie{

private:
TrieNode* root;

public:
    Trie(){
        root =  NULL;
    }

    bool isEmpty(){

    }

    void insert(string key, string value){
        if(root == NULL) 
          root = new TrieNode();
        
        TrieNode* ptr = root;
        for(int i=0;i<key.length();i++){
            char val = key[i];
            if(ptr->child_map.find(val) == ptr->child_map.end()){
                ptr->child_map[val] = new TrieNode();
            }
            ptr = ptr->child_map[val];
        }

        ptr->endOfWord = true;
        ptr->meaning = value;

    }

    string get(string key){

        if(root == NULL){
            return NULL;
        }

        TrieNode* temp = root;
        for(int i=0;i<key.length();i++){
            char val = key[i];
            temp = temp->child_map[val];
            if(temp == NULL){
                return "Does Not Exist";
            }
        }
        if(temp->endOfWord){
            return temp->meaning;
        }
        return "Does Not exist";
    } 

    void remove(string k){
        removeNode(root,k,0);
    }

    void destroy(){
        deleteNode(root);
    }

};


//test insertion of dictionary key-value pairs
double tc1(Trie *trieds)
{
    ifstream filereader("words.txt");
    // ofstream filewriter;
    // filewriter.open("tc1Trietime.txt", std::ios_base::app);
    string word;


    //auto start = high_resolution_clock::now();
    clock_t t;
    t = clock();
    for(int i=0; i<TCSIZE; i++)
    {
        filereader>>word;
        trieds->insert(word, "testvalue");
    }
    t = clock() - t;
    double time_taken = ((double)t);
    //auto stop = high_resolution_clock::now();

    //auto duration = duration_cast<microseconds>(stop - start);
    //string exectime = to_string(duration.count());
    // filewriter<<exectime<<"\n";

    filereader.close();
    // filewriter.close();
    //return duration.count();
    return time_taken;
}

//test search of words, 50% found, 50% not found
double tc2(Trie *trieds)
{
    ifstream filereader("words.txt");
    // ofstream filewriter;
    // filewriter.open("tc2Trietime.txt", std::ios_base::app);
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
        trieds->insert(words[i], "testvalue");
    }

    //search available words
    // auto start = high_resolution_clock::now();
    clock_t t;
    t = clock();
    for(int i=0; i<TCSIZE/2; i++)
    {
        trieds->get(words[i]);
    }
    //search unavailable words
    for(int i=TCSIZE; i<TCSIZE+250; i++)
    {
        trieds->get(words[i]);
    }
    // auto stop = high_resolution_clock::now();
    t = clock() - t;
    double time_taken = ((double)t);

    // auto duration = duration_cast<microseconds>(stop - start);
    // string exectime = to_string(duration.count());
    // filewriter<<exectime<<"\n";

    // filewriter.close();
    filereader.close();
    // return duration.count();
    return time_taken;
}

//test deletion of entire dictionary
double tc3(Trie *trieds)
{
    ifstream filereader("words.txt");
    // ofstream filewriter;
    // filewriter.open("tc3Trietime.txt", std::ios_base::app);
    string word;

    vector<string> words;

    //store words in a vector
    for(int i=0; i<TCSIZE*2; i++)
    {
        filereader>>word;
        words.push_back(word);
    }

    //insert words
    for(int i=0; i<TCSIZE; i++)
    {
        trieds->insert(words[i], "testvalue");
    }

    //delete all the stored words
    // auto start = high_resolution_clock::now();
    clock_t t;
    t = clock();
    for(int i=0; i<TCSIZE/2; i++)
    {
        trieds->remove(words[i]);
    }
    // auto stop = high_resolution_clock::now();
    t = clock() - t;
    double time_taken = ((double)t);

    // auto duration = duration_cast<microseconds>(stop - start);
    // string exectime = to_string(duration.count());
    // filewriter<<exectime<<"\n";

    filereader.close();
    // filewriter.close();
    // return duration.count();
    return time_taken;
}


int main(){

Trie *trieds = new Trie();
ofstream filewriter;
filewriter.open("tc1Trietime.txt", std::ios_base::app);

//iterate over 10 different dictionary sizes
for(int i = 0; i<10; i++)
{
    double sum = 0.0;
    //iterate over the testcase values multiple times and calculate their averages
    for(int j=0; j<100; j++)
    {
        sum += tc1(trieds);
    }

    filewriter<<"Average time for "<<TCSIZE<<" inputs is: "<<double(sum/100.0)<<endl;
    TCSIZE += 500;
    
}  

filewriter.close();

return 0;
}


