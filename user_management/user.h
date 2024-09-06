#include <stdbool.h>
#include <windows.h>

void disable_echo();

void enable_echo();

typedef struct userData userData;

void init_program();

void register_user();

void login_user();

void init_user_session(char* username); 

bool exists_user(char* username);

bool validate_password(char* password);

void remove_newline(char* str);

char first_char(char* str);

int char_count(char* str);

userData* search_from_file(char* username);