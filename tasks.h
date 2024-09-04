#include <stdio.h>

void welcome_user(char* username);

void updateCounters(int* marked, int* completed, char* username);

void readCounters(int* marked, int* completed, FILE* user_file);

void add_task(char* username, FILE* user_file);

void view_tasks(char* username);

void mark_as_completed(char* username, FILE* user_file);

void remove_task(char* username, FILE* user_file);