#include <stdio.h>

void welcome_user(char* username);

void add_task(char* username, FILE* user_file);

void view_tasks(char* username, FILE* user_file);

void mark_as_completed(char* username, FILE* user_file);

void remove_task(char* username, FILE* user_file);