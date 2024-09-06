#include "tasks.h"
#include "../user_management/user.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define MAX_LINE_LENGTH 256

void welcome_user(char* username){
    // getchar();

    FILE* user_file;
    char path[256];
    snprintf(path, sizeof(path), "user_files/%s.txt", username);
    user_file = fopen(path, "a");

    printf("\nSelect how do you want to proceed : \n");
    printf("Enter 'a' to add a task\n");
    printf("Enter 'v' to view all tasks\n");
    printf("Enter 'r' to remove/delete a task\n");

    char op;
    char* str = (char *)malloc(50);
    while(true){
        printf("\nEnter here : ");

        scanf("%[^\n]", str);
        getchar();
        op = first_char(str);

        if((op == 'a' || op == 'v' || op == 'r') && char_count(str) == 1) break;

        printf("\nInvalid selection, enter again\n");
    }
    // scanf("%c", &op);
    // getchar();

    // if(!(op == 'a' || op == 'v' || op == 'r')){
    //     printf("\nInvalid input, program terminating...\n\n");
    //     return;
    // }
    switch(op){
        case 'a':
        add_task(username, user_file);
        break;

        case 'v':
        view_tasks(username);
        break;

        case 'r':
        remove_task(username);
    }
}

bool isFileEmpty(char* username){
    char* path = (char *)malloc(256);
    snprintf(path, 256, "user_files/%s.txt", username);
    FILE* file = fopen(path, "r");
    free(path);

    char* buffer = (char *)malloc(256);
    while(fgets(buffer, 256, file)){
        if(buffer[1] == ',') continue;
        else if(buffer[0] != ' ' && buffer[0] != '\0') return false;
    }
    free(buffer);
    fclose(file);
    return true;
}

void continue_flow(char* username){
    printf("Do you wish to continue ?\n");
    char* str = (char *)malloc(50);
    char op;
    while(true){
        printf("Enter[y/n] : ");
        scanf("%[^\n]", str);
        getchar();
        op = first_char(str);

        if((op == 'y' || op == 'n') && char_count(str) == 1) break;
        else{
            printf("\nInvalid selection, try again\n");
        }
    }
    free(str);

    if(op == 'y') welcome_user(username);
    else{
        printf("\nTerminating Program...\n");
        return;
    }
}

//function for adding tasks

void add_task(char* username, FILE* user_file){
    printf("Enter task here : ");
    char* task = (char*)malloc(256);
    scanf("%[^\n]", task);
    getchar();

    fprintf(user_file, "%s\n", task);
    free(task);

    printf("\nTask added successfully!\n");
    fclose(user_file);
    continue_flow(username);
}

//function for viewing tasks 


void view_tasks(char* username){
    if(isFileEmpty(username)){
        printf("\nNo tasks added\n\n");
    }
    else{
        FILE* user_file;
        char path[256];
        snprintf(path, sizeof(path), "user_files/%s.txt", username);
        user_file = fopen(path, "r");

            // printf("entered view function\n");

        char task[256];
        int counter = 0;
        while(fgets(task, sizeof(task), user_file) != NULL){
            if((task[0] == 'r' && task[1] == ',') || task[0] == ' ' || task[0] == '\0') continue;
            else {
                counter++;
                if(counter == 1) printf("\nYour tasks are as follows:\n\n");
                printf("%d. %s\n",counter, task);
            }
        }
    }
    continue_flow(username);
}

//function for viewing tasks 

void view_tasks_func(char* username){
    if(isFileEmpty(username)){
        printf("\nNo tasks added\n\n");
    }
    else{
        FILE* user_file;
        char path[256];
        snprintf(path, sizeof(path), "user_files/%s.txt", username);
        user_file = fopen(path, "r");

        char task[256];
        int counter = 1;
        while(fgets(task, sizeof(task), user_file) != NULL){
            if((task[0] == 'r' && task[1] == ',') || task[0] == ' ' || task[0] == '\0') continue;
            else {
                if(counter == 1) printf("\nYour tasks are as follows:\n\n");
                printf("%d. %s\n",counter, task);
                counter++;
            }
        }
    }
}

//function for removing a task

void remove_task(char* username) {
    char user_file[MAX_LINE_LENGTH];
    snprintf(user_file, sizeof(user_file), "user_files/%s.txt", username);

    FILE *file = fopen(user_file, "r+");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    view_tasks_func(username);
    int line_no;
    printf("Enter the task no. that you wish to remove\n");
    printf("Enter Here : ");
    scanf("%d", &line_no);
    getchar();

    char buffer[MAX_LINE_LENGTH];
    char modified_line[MAX_LINE_LENGTH + 2]; 
    int current_line = 0;
    long line_start_position = -1;

    FILE *temp_file = tmpfile();
    if (temp_file == NULL) {
        perror("Error creating temporary file");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    while (fgets(buffer, sizeof(buffer), file)) {
        if(buffer[1] != ',') current_line++;
        if (current_line == line_no) {
            size_t len = strlen(buffer);
            if (len > 0 && buffer[len - 1] == '\n') {
                buffer[len - 1] = '\0';
            }

            snprintf(modified_line, sizeof(modified_line), "r,%s\n", buffer);
            fputs(modified_line, temp_file);
        } else {
            fputs(buffer, temp_file);
        }

    }

    fclose(file);
    file = fopen(user_file, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    rewind(temp_file);
    while (fgets(buffer, sizeof(buffer), temp_file)) {
        fputs(buffer, file);
    }

    fclose(temp_file);
    fclose(file);

    continue_flow(username);
}
