#include <stdbool.h>
#include "data_structure/bst.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct userData userData;

bool exists_user(char* username){
    return 0;
}

void login_user(){

}

void register_user(){
    char username[50];
    char password[20];

    printf("\nEnter your username and password to register.\n\n");
    printf("[Note : username can contain Alphanumeric characters, numbers, special characters]\n");
    printf("[NO SPACES ALLOWED IN USERNAME]\n");

    printf("\nUsername : ");
    scanf("%s", username);

    while(exists_user(username)){
        printf("Sorry, this username is already taken, please try another combination\n");
        printf("Enter 'e' if you wish to exit\n");
        printf("\nUsername : ");
        scanf("%s, username");
    }
    printf("Password : ");
    scanf("%s", password);
    FILE* cred = fopen("credentials.txt", "a");
    fprintf(cred, "%s,%s\n", username, password);
    fclose(cred);
}


void init_program(){

    char line[71];
    char username[50];
    char password[20];
    FILE* cred = fopen("credentials.txt", "a");
    while(fgets(line, sizeof(line), cred)){
        sscanf(line, "%[^,],%s", username, password);
        userData* data = set_data(username, password);
        insertion(data);
    }

    getInorder();

    printf("Welcome to your Personalized Progress Tracker, how do you want to proceed\n");
    printf("Enter 's' to sign-in\n");
    printf("Enter 'r' to sign-up\n");
    printf("Enter 'e' to exit\n");
    char op;
    printf("Write Here : ");
    scanf("%c", &op);
    if(op == 'e' || op == 'E') return;
    else if(op == 'r' || op == 'R'){
        register_user();
    }
    else if(op == 's' || op == 'S'){
        login_user();
    }
}

void init_user_session(){

}

