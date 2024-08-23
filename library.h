#include <stdbool.h>

typedef struct userData userData;

void init_program();

void register_user(const char* fileName, const char* username, const char* password);

bool verify_login(const char* username, const char* password);

void init_user_session();