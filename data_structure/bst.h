#include <stdbool.h>

typedef struct userData userData;

typedef struct TreeNode TreeNode;

TreeNode* insert_data(TreeNode* root, userData* data);

void freeTree(TreeNode* root);

userData* set_data(char* username, char* password);

char* getUsername(userData* data);

char* getPassword(userData* data);

void getInorder(TreeNode* root);

bool search(TreeNode* root, char* username);

userData* get_node_data(TreeNode* root, char* username);