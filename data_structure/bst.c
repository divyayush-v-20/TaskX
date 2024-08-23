#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "bst.h"

struct userData{
    char* username;
    char* password;
};

typedef struct userData userData;

userData* set_data(char* username, char* password){
    userData* data = (userData *)malloc(sizeof(userData));
    data -> username = username;
    data -> password = password;
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

TreeNode* init_node(){
    TreeNode* root = (TreeNode *)malloc(sizeof(TreeNode));
    root -> left = NULL;
    root -> right = NULL;
}

TreeNode* insert_data(TreeNode* root, userData* data){
    if(!root){
        TreeNode* newNode = init_node();
        newNode -> val -> username = data -> username;
        newNode -> val -> password = data -> password;
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

void getInorder(TreeNode* root){
    if(!root) return;
    getInorder(root -> left);
    printf("%s ", root -> val -> username);
    getInorder(root -> right);
}