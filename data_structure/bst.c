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


TreeNode* insert_data(TreeNode* root, userData* data){
    if(!root){
        TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
        newNode -> left = NULL;
        newNode -> right = NULL;
        newNode -> val = data;
        return newNode;
    }
    int cmp = strcmp(root -> val -> username, data -> username);
    if(cmp > 0){
        root -> left = insert_data(root -> left, data);
    }
    else if(cmp < 0){
        root -> right = insert_data(root -> right, data);
    }
    else{
        printf("Duplicate username found: %s\n", data -> username);
        free(data -> username);
        free(data -> password);
        free(data);
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

bool search(TreeNode* root, char* username){
    while(root){
        if(strcmp(root -> val -> username, username) == 0) return true;
        else if(strcmp(root -> val -> username, username) > 0) root = root -> left;
        else root = root -> right;
    }
    return false;
}

userData* get_node_data(TreeNode* root, char* username){
    while(root){
        if(strcmp(root -> val -> username, username) == 0) return root -> val;
        else if(strcmp(root -> val -> username, username) > 0) root = root -> left;
        else root = root -> right;
    }
    return NULL;
}