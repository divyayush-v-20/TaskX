#include <stdbool.h>

typedef struct userData userData;

void init_program();

void register_user();

void login_user();

void init_user_session(); 

bool exists_user(char* username);

void load_data();