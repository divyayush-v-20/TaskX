#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include <string.h>
typedef struct TreeNode TreeNode;
typedef struct userData userData;
int main(){
    TreeNode* root = init_node();
    
    for(int i = 0; i < 3; i++){
        char* username;
        char* password;
        gets(username);
        gets(password);
        userData* data = set_data(username, password);
        root = insert_data(root, data);
    }

    getInorder(root);

    return 0;
}