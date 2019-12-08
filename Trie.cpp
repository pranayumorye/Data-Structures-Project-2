#include<bits/stdc++.h>
#include "Operations.cpp"
#include "Dictionary.cpp"
#include "DataStructs.cpp"
#include<string>

using namespace std;


class TrieNode{
    public:
    string meaning;
    unordered_map<char,TrieNode*> child_map;
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
        for(auto it = node->child_map.begin(); it!= node->child_map.end();it++){
            deleteNode(it->second);;
        }
        delete(node);
        node = NULL;
}

class Trie : public DataStructs{

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
