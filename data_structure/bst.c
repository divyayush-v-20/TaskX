#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "bst.h"

struct userData{
    char* username;
    char* password;
};

typedef struct userData userData;

userData* set_data(char* username, char* password){
    userData* data = (userData *)malloc(sizeof(userData));
    data -> username = strdup(username);
    data -> password = strdup(password);
    return data;
}

char* getUsername(userData* data){
    return data -> username;
}

char* getPassword(userData* data){
    return data -> password;
}

struct TreeNode{
    userData* val;
    struct TreeNode* left;
    struct TreeNode* right;
};

typedef struct TreeNode TreeNode;

TreeNode* root = NULL;

void init_node(TreeNode* node){
    node = (TreeNode *)malloc(sizeof(TreeNode));
    node -> val = NULL;
    node -> left = NULL;
    node -> right = NULL;
}

TreeNode* insert_data(TreeNode* root, userData* data){
    if(!root){
        TreeNode* newNode;
        init_node(newNode);
        newNode -> val = data;
        return newNode;
    }
    if(strcmp(root -> val -> username, data -> username) > 0){
        root -> left = insert_data(root -> left, data);
    }
    else{
        root -> right = insert_data(root -> right, data);
    }
    return root;
}

void insertion(userData* data){
    root = insert_data(root, data);
}

void freeTree(TreeNode* root){
    if (root) {
        freeTree(root -> left);
        freeTree(root -> right);
        free(root -> val -> username);
        free(root -> val -> password);
        free(root -> val);
        free(root);
    }
    return;
}

void getInorder(){
    if(!root) return;
    getInorder(root -> left);
    printf("%s ", root -> val -> username);
    getInorder(root -> right);
}

bool search(char* username){
    while(root){
        if(strcmp(root -> val -> username, username) == 0) return true;
        else if(strcmp(root -> val -> username, username) > 0) root = root -> left;
        else root = root -> right;
    }
    return false;
}