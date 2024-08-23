#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include <string.h>
typedef struct TreeNode TreeNode;
typedef struct userData userData;
int main(){
    TreeNode* root = NULL;
    
    for(int i = 0; i < 3; i++) {
        char username[100];  
        char password[100];  

        printf("Enter username: ");
        fgets(username, 100, stdin);
        username[strcspn(username, "\n")] = 0;  // Remove newline character

        printf("Enter password: ");
        fgets(password, 100, stdin);
        password[strcspn(password, "\n")] = 0;  // Remove newline character

        userData* data = set_data(username, password);
        root = insert_data(root, data);
    }

    getInorder(root);

    return 0;
}