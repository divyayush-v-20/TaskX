#include <stdbool.h>
#include "data_structure/bst.h"
#include "library.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>

typedef struct userData userData;
TreeNode* root = NULL;

struct userData{
    char* username;
    char* password;
};

bool isValidUsername(char* input){
    for(int i = 0; i < strlen(input); i++){
        if(input[i] == ' ') return false;
    }
    return true;
}

void remove_newline(char* str) {
    char* newline_pos = strchr(str, '\n');
    if (newline_pos) {
        *newline_pos = '\0';
    }
}


bool exists_user(char* username){
    if(search(root, username)) return true;
    return false;
}

bool validate_password(char* password){
    bool noUpperCase = true;
    bool noLowerCase = true;
    bool noSplChar = true;
    bool noNum = true;
    int len = 0;
    for(int i = 0; password[i] != '\0'; i++){
        len ++;
    }
    if(len > 20 || len < 8) return false;
    for(int i = 0; i < len; i++){
        if(password[i] >= 'a' && password[i] <= 'z') noLowerCase = 0;
        if(password[i] >= 'A' && password[i] <= 'Z') noUpperCase = 0;
        if(password[i] >= '0' && password[i] <= '9') noNum = 0;
        if(password[i] >= 33 && password[i] <= 126) noSplChar = 0;
    }
    return !(noUpperCase || noLowerCase || noNum || noSplChar);
}

void login_user(){
    printf("Enter your Username and Password to Login\n\n");
    char username[50];
    char password[20];
    printf("Username : ");
    scanf("%s", username);
    getchar();
    userData* data = get_node_data(root, username);
    if(data == NULL){
        printf("The username you entered is not valid, try again\n");
        // printf("Enter 't' to try again, or 'r' if you wish to register\n");
        login_user();
    }
    else{
        char password[20];
        printf("Password : ");
        scanf("%s", password);
        while(strcmp(password, data -> password) != 0){
            printf("Incorrect Password\n");
            printf("Re-Enter Password\n");
            printf("Password : ");
            scanf("%s", password);
        }
        init_user_session(username);
    }
}

void register_user(){
    char username[50];
    char password[20];

    printf("\nEnter your username and password to register.\n\n");
    printf("[Note : username can contain Alphanumeric characters, numbers, special characters]\n");
    printf("[NO SPACES ALLOWED IN USERNAME]\n");
    printf("Password must contain an Uppercase, Lowercase, Numeric value and special chracters\n");
    printf("[Password should have atleast 8 characters]\n[Password should not exceed 20 characters]\n");
    printf("\nUsername : ");
    scanf("%[^\n]", username);
    getchar();
    // printf("%s", username);

    while(!isValidUsername(username)){
        printf("Username cannot contain spaces, please re-enter your username.\n");
        printf("Username : ");
        scanf("%[^\n]", username);
        getchar();
    }

    while(exists_user(username)){
        printf("Sorry, this username is already taken, please try another combination\n");
        printf("Enter 'CTLR + C' if you wish to exit\n");
        printf("\nUsername : ");
        scanf("%s", username);
    }
    
    printf("Password : ");
    scanf("%[^\n]", password);
    getchar();
    while(!isValidUsername(password)){
        printf("Password cannot contain spaces, please re-enter your password.\n");
        printf("Password : ");
        scanf("%[^\n]", password);
        getchar();
    }
    while(!validate_password(password)){
        printf("The password you entered does not match the security requirements\nEnter a new password with all the given constraints\n");
        printf("Password : ");
        scanf("%s", password);
    }
    FILE* cred = fopen("credentials.txt", "a");
    fprintf(cred, "%s,%s\n", username, password);
    userData* data = set_data(username, password);
    root = insert_data(root, data);
    fclose(cred);
}


void init_program(){

    char line[71];
    char username[50];
    char password[20];
    FILE* cred = fopen("credentials.txt", "r");
    while(fgets(line, sizeof(line), cred)){
        sscanf(line, "%[^,],%s", username, password);
        userData* data = set_data(username, password);
        root = insert_data(root, data);
    }

    // getInorder(root);
    // printf("\n");


    printf("Welcome to your Personalized Progress Tracker, how do you want to proceed\n");
    printf("Enter 's' to sign-in\n");
    printf("Enter 'r' to sign-up\n");
    printf("Enter 'e' to exit\n");
    char op;
    printf("Write Here : ");
    scanf("%c", &op);
    getchar();
    if(op == 'e' || op == 'E') return;
    else if(op == 'r' || op == 'R'){
        register_user();
    }
    else if(op == 's' || op == 'S'){
        login_user();
    }
}

void init_user_session(char* username){
    printf("Welcome %s", username);
}

void load_data(){
    
}