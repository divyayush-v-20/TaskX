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
    printf("\nSelect how do you want to proceed : \n");
    printf("Enter 'a' to add a task\n");
    printf("Enter 'v' to view all tasks\n");
    printf("Enter 'm' to mark a task as complete\n");
    printf("Enter 'r' to remove/delete a task\n");

    printf("\nEnter here : ");

    char op;
    scanf("%c", &op);
    getchar();

    switch(op){
        case 'a':
        add_task(username, user_file);
        break;

        case 'v':
        view_tasks(username);
        break;

        case 'm':
        mark_as_completed(username, user_file);
        break;

        case 'r':
        remove_task(username, user_file);
    }
}

void updateCounters(int* marked, int* completed, char* username){
    char* path = (char*)malloc(256);
    snprintf(path, sizeof(path), "user_files/%s.txt", username);
    FILE* user_file = fopen(path, "r+");

    fprintf(user_file, "%d,%d\n", marked, completed);
    free(path);
    fclose(user_file);
}

void readCounters(int* marked, int* completed, FILE* user_file){
    rewind(user_file);
    fscanf(user_file, "%d,%d\n", marked, completed);
}

void add_task(char* username, FILE* user_file){
    int marked, completed;
    readCounters(&marked, &completed, user_file);
    ++marked;

    printf("Enter task here : ");
    char* task = (char*)malloc(256);
    scanf("%[^\n]", task);
    getchar();

    fprintf(user_file, "\n%s,0", task);
    updateCounters(&marked, &completed, username);
    free(task);

    printf("\nTask added successfully!\n");
}

void view_tasks(char* username){
    printf("\nYour tasks and their completion status is as follows\n\n");
    FILE* user_file;
    char path[256];
    snprintf(path, sizeof(path), "user_files/%s.txt", username);
    user_file = fopen(path, "r");

    // printf("entered view function\n");

    char task[256];
    bool startPrinting = false;
    int counter = 1;
    while(fgets(task, sizeof(task), user_file) != NULL){

        char* description = (char*)malloc(256);
        int status;
        sscanf(task, "%[^,],%d", description, &status);
        if(startPrinting){
            printf("%d. %s - %s\n", counter++, description, status == 0 ? "Pending" : "Completed");
        }
        startPrinting = true;
        
    }
}

void mark_as_completed(char* username, FILE* user_file){

}

void remove_task(char* username, FILE* user_file){

}

