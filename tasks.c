#include "tasks.h"
#include "library.h"
#include <stdio.h>

void welcome_user(char* username){
    getchar();

    FILE* user_file;
    char path[256];
    snprintf(path, sizeof(path), "user_files/%s.txt", username);
    user_file = fopen(path, "a");

    printf("\n\nHey %s, Welcome!\n", username);
    printf("Select how do you want to proceed : \n");
    printf("Enter 'a' to add a task\n");
    printf("Enter 'v' to view all tasks\n");
    printf("Enter 'm' to mark a task as complete\n");
    printf("Enter 'r' to remove/delete a task\n");

    char op;
    scanf("%c", &op);

    switch(op){
        case 'a':
        add_task(username, user_file);
        break;

        case 'v':
        view_tasks(username, user_file);
        break;

        case 'm':
        mark_as_completed(username, user_file);
        break;

        case 'r':
        remove_task(username, user_file);
    }
}

void add_task(char* username, FILE* user_file){

}

void view_tasks(char* username, FILE* user_file){

}

void mark_as_completed(char* username, FILE* user_file){

}

void remove_task(char* username, FILE* user_file){

}

//sheldon@taskX95