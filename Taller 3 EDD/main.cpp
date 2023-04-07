#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;


struct sInfoEntrada{
    char tipo;
    int dato;
};

class AVLNode {
public:
    int data;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(int data) {
        this->data = data;
        left = right = nullptr;
        height = 1;
    }
};

class AVLTree {
public:
    AVLNode* root;

    int height(AVLNode* node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    int balanceFactor(AVLNode* node) {
        if (node == nullptr)
            return 0;
        return height(node->left) - height(node->right);
    }

    void updateHeight(AVLNode* node) {
        if (node == nullptr)
            return;
        node->height = max(height(node->left), height(node->right)) + 1;
    }

    AVLNode* rightRotate(AVLNode* node) {
        AVLNode* leftChild = node->left;
        AVLNode* rightOfLeftChild = leftChild->right;

        leftChild->right = node;
        node->left = rightOfLeftChild;

        updateHeight(node);
        updateHeight(leftChild);

        return leftChild;
    }

    AVLNode* leftRotate(AVLNode* node) {
        AVLNode* rightChild = node->right;
        AVLNode* leftOfRightChild = rightChild->left;

        rightChild->left = node;
        node->right = leftOfRightChild;

        updateHeight(node);
        updateHeight(rightChild);

        return rightChild;
    }

    AVLNode* minValueNode(AVLNode* node) {
        AVLNode* current = node;

        while (current->left != nullptr)
            current = current->left;

        return current;
    }


    AVLNode* erase(AVLNode*node,int data){
        if(node == nullptr)
            return node;

        if(data < node->data)
            node->left = erase(node->left,data);
        else if(data > node->data)
            node->right = erase(node->right,data);
        else{
            if(node->left == nullptr || node->right == nullptr){
                AVLNode* temp = node->left ? node->left : node->right;

                if(temp == nullptr){
                    temp = node;
                    node = nullptr;
                }
                else
                    *node = *temp;
                delete temp;
            }
            else{
                AVLNode* temp = minValueNode(node->right);
                node->data = temp->data;
                node->right = erase(node->right,temp->data);
            }
        }

        if(node == nullptr)
            return node;

        updateHeight(node);

        int balance = balanceFactor(node);

        if(balance > 1 && balanceFactor(node->left) >= 0)
            return rightRotate(node);

        if(balance > 1 && balanceFactor(node->left) < 0){
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if(balance < -1 && balanceFactor(node->right) <= 0)
            return leftRotate(node);

        if(balance < -1 && balanceFactor(node->right) > 0){
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;

    }


    AVLNode* insert(AVLNode* node, int data) {
        if (node == nullptr)
            return new AVLNode(data);

        if (data < node->data)
            node->left = insert(node->left, data);
        else if (data > node->data)
            node->right = insert(node->right, data);
        else
            return node; // data already exists in the tree

        updateHeight(node);

        int balance = balanceFactor(node);

        if (balance > 1 && data < node->left->data)
            return rightRotate(node);

        if (balance < -1 && data > node->right->data)
            return leftRotate(node);

        if (balance > 1 && data > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && data < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void inorder(AVLNode* node) {
        if (node == nullptr)
            return;
        cout << '\n';
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    AVLTree() {
        root = nullptr;
    }
};




sInfoEntrada leerlinea(char *linea){
    sInfoEntrada info;
    char *token;
    token = strtok(linea, " ");
    info.tipo = token[0];
    token = strtok(NULL, " ");
    info.dato = atoi(token);
    return info;
}

vector<sInfoEntrada> infoEntradaAgregacion(string filename){
    vector<sInfoEntrada> info;
    ifstream file(filename);
    string str;
    while (getline(file, str))
    {
        sInfoEntrada infoEntrada = leerlinea((char*)str.c_str());
        if(infoEntrada.tipo == 'A'){
            info.push_back(infoEntrada);
        }
    }
    return info;
}

vector<sInfoEntrada> infoEntradaEliminacion(string filename){
    vector<sInfoEntrada> info;
    ifstream file(filename);
    string str;
    while (getline(file, str))
    {
        sInfoEntrada infoEntrada = leerlinea((char*)str.c_str());
        if(infoEntrada.tipo == 'E'){
            info.push_back(infoEntrada);
        }
    }
    return info;
}

vector<int> inorder(AVLNode* node) {
    vector<int> v;
    vector<int> v1;
        if (node == nullptr)
            return v;

        v.push_back(node->data);
        v1=inorder(node->left);
        for(int i=0; i<v1.size(); i++){
            v.push_back(v1[i]);
        }
        v1=inorder(node->right);
        for(int i=0; i<v1.size(); i++){
            v.push_back(v1[i]);
        }
    return v;
}

bool impar(int n){
    if(n%2==0){
        return false;
    }
    else{
        return true;
    }
}

int median(int size){
    if(impar(size)){
        return (size/2)+1;
    }
    else{
        return size/2;
    }
}


int main() {
    AVLTree tree;
    //Insertar 19, 20, 5, 82
    tree.root = tree.insert(tree.root, 19);
    tree.root = tree.insert(tree.root, 20);
    tree.root = tree.insert(tree.root, 5);
    tree.root = tree.insert(tree.root, 82);
    tree.inorder(tree.root);
    //Eliminar 50
    tree.root = tree.erase(tree.root, 50);
    tree.inorder(tree.root);
}
