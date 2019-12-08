#include "math.h"
#include <string>
   
#include "Operations.cpp"
#include "Dictionary.cpp"


using namespace std;

class Node  
{  
    public:
    string key;
    string value;
    Node *left;
    Node *right;
    int height;

    Node(string k, string v)
    {
        key = k;
        value = v;
        left = NULL;
        right = NULL;
        height = 1;
    }
};

int height(Node *N)  
{  
    if (N == NULL)  
        return 0;  
    return N->height;  
} 

Node *rightRotate(Node *y)  
{  
    Node *x = y->left;  
    Node *T2 = x->right;  
  
    // Perform rotation  
    x->right = y;  
    y->left = T2;  
  
    // Update heights  
    y->height = max(height(y->left), 
                    height(y->right)) + 1;  
    x->height = max(height(x->left), 
                    height(x->right)) + 1;  
  
    // Return new root  
    return x;  
}  
  
Node *leftRotate(Node *x)  
{  
    Node *y = x->right;  
    Node *T2 = y->left;  
  
    // Perform rotation  
    y->left = x;  
    x->right = T2;  
  
    // Update heights  
    x->height = max(height(x->left),     
                    height(x->right)) + 1;  
    y->height = max(height(y->left),  
                    height(y->right)) + 1;  
  
    // Return new root  
    return y;  
}  
  
// Get Balance factor of node N  
int getBalance(Node *N)  
{  
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

Node * minValueNode(Node* node)  
{  
    Node* current = node;  
  
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)  
        current = current->left;  
  
    return current;  
}

Node* insertAVL(Node* node, string key, string value)  
{  
    /* 1. Perform the normal BST insertion */
    if (node == NULL)  
        return(new Node(key, value));  
  
    if (key < node->key)  
        node->left = insertAVL(node->left, key, value);  
    else if (key > node->key)
        node->right = insertAVL(node->right, key, value);  
    else // Equal keys are not allowed in BST  
        return node;  
  
    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left), height(node->right));
  
    /* 3. Get the balance factor of this ancestor  
        node to check whether this node became  
        unbalanced */
    int balance = getBalance(node);  
  
    // If this node becomes unbalanced, then  
    // there are 4 cases  
  
    // Left Left Case  
    if (balance > 1 && key < node->left->key)  
        return rightRotate(node);  
  
    // Right Right Case  
    if (balance < -1 && key > node->right->key)  
        return leftRotate(node);  
  
    // Left Right Case  
    if (balance > 1 && key > node->left->key)  
    {  
        node->left = leftRotate(node->left);  
        return rightRotate(node);  
    }  
  
    // Right Left Case  
    if (balance < -1 && key < node->right->key)  
    {  
        node->right = rightRotate(node->right);  
        return leftRotate(node);  
    }  
  
    /* return the (unchanged) node pointer */
    return node;  
}

Node* deleteNodeAVL(Node* root, string key)
{  
    if (root == NULL)  
        return root;  
   
    if ( key < root->key )  
        root->left = deleteNodeAVL(root->left, key);  
  
    else if( key > root->key )  
        root->right = deleteNodeAVL(root->right, key);  
  
    else
    {
        if( (root->left == NULL) || 
            (root->right == NULL) )  
        {  
            Node *temp = root->left ?  
                         root->left :  
                         root->right;  
  
            // No child case  
            if (temp == NULL)  
            {  
                temp = root;  
                root = NULL;  
            }  
            else // One child case  
            *root = *temp; // Copy the contents of  
                           // the non-empty child  
            free(temp);  
        }  
        else
        {  
            Node* temp = minValueNode(root->right);  
            root->key = temp->key;  
            root->right = deleteNodeAVL(root->right, temp->key);  
        }  
    }  

    if (root == NULL)  
    return root;  
  
    root->height = 1 + max(height(root->left),  
                           height(root->right));  

    int balance = getBalance(root);  

    if (balance > 1 &&  
        getBalance(root->left) >= 0)  
        return rightRotate(root);  

    if (balance > 1 &&  
        getBalance(root->left) < 0)  
    {  
        root->left = leftRotate(root->left);  
        return rightRotate(root);  
    }  

    if (balance < -1 &&  
        getBalance(root->right) <= 0)  
        return leftRotate(root);  
 
    if (balance < -1 &&  
        getBalance(root->right) > 0)  
    {  
        root->right = rightRotate(root->right);  
        return leftRotate(root);  
    }  
  
    return root;  
}  

string getAVL(Node* node, string key)
{
    if(node==NULL) return NULL;

    if(node->key == key) return node->value;

    if(key < node->key) return getAVL(node->left, key);
    else return getAVL(node->right, key);
}

void destroyAVL(Node *node)
{
    if(!node) return;

    destroyAVL(node->left);
    destroyAVL(node->right);
    delete node;
}

class AVL: public DataStructs
{
    private:
        Node *root;
    //implements the dictionary operations using AVL Balanced tree
    public:
        AVL(){
            root = NULL;
        }

        bool isEmpty()
        {
            if(!root) return true;
            return false;
        }

        void insert(string key, string value)
        {
            insertAVL(root, key, value);
        }

        string get(string key)
        {
            return getAVL(root, key);
        }

        void remove(string key)
        {
            deleteNodeAVL(root, key);
        }

        void destroy()
        {
            destroyAVL(root);
        }

};
