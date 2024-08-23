#include <stdbool.h>

typedef struct userData userData;

typedef struct TreeNode TreeNode;

void init_node(TreeNode* node);

TreeNode* insert_data(TreeNode* root, userData* data);

void insertion(userData* data);

void freeTree(TreeNode* root);

userData* set_data(char* username, char* password);

char* getUsername(userData* data);

char* getPassword(userData* data);

void getInorder();

bool search(char* username);