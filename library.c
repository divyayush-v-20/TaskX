#include <stdbool.h>
#include "data_structure/bst.h"
#include "library.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "tasks.h"
#include "security/encryption.h"

void disable_echo() {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE); 
    DWORD mode;

    GetConsoleMode(hStdin, &mode);

    SetConsoleMode(hStdin, mode & ~(ENABLE_ECHO_INPUT));
}

void enable_echo() {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE); 
    DWORD mode;

    GetConsoleMode(hStdin, &mode);

    SetConsoleMode(hStdin, mode | ENABLE_ECHO_INPUT);
}


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
    // int len = strlen(input);
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
        if(password[i] == ' ') return false;
        if(password[i] >= 'a' && password[i] <= 'z') noLowerCase = 0;
        if(password[i] >= 'A' && password[i] <= 'Z') noUpperCase = 0;
        if(password[i] >= '0' && password[i] <= '9') noNum = 0;
        if(password[i] >= 33 && password[i] <= 126) noSplChar = 0;
    }
    return !(noUpperCase || noLowerCase || noNum || noSplChar);
}

void login_user(){
    printf("\nEnter your Username and Password to Login\n\n");
    char* username = (char*)malloc(20);
    char* password = (char*)malloc(20);
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
        // char password[20];
        printf("Password : ");
        disable_echo();
        scanf("%s", password);
        enable_echo();
        while(strcmp(password, data -> password) != 0){
            printf("Incorrect Password\n");
            printf("Re-Enter Password\n");
            printf("Password : ");
            disable_echo();
            scanf("%s", password);
            enable_echo();
        }
        welcome_user(username);
    }
    free(username);
    free(password);
}


void register_user(){
    char* username = (char*)malloc(50);
    char* password = (char*)malloc(50);

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
        getchar();
    }
    printf("Password : ");
    disable_echo();
    scanf("%[^\n]", password);
    getchar();
    enable_echo();
    // while(!validate_password(password)){
    //     printf("Password cannot contain spaces, please re-enter your password.\n");
    //     printf("Password : ");
    //     scanf("%[^\n]", password);
    //     getchar();
    // }
    while(!validate_password(password)){
        printf("The password you entered does not match the security requirements\nEnter a new password with all the given constraints\n");
        printf("Password : ");
        disable_echo();
        scanf("%[^\n]", password);
        getchar();
        enable_echo();
    }
    
    //adding the credentials to credentials.txt
    FILE* cred = fopen("cred_encr.txt", "a");
    fprintf(cred, "%s,%s\n", encode(username), encode(password));
    userData* data = set_data(username, password);
    root = insert_data(root, data);
    fclose(cred);

    //creating a txt file for each user
    const char* folder_name = "user_files";
    // const char* file_name = ("%s.txt", username);
    char path[256];
    snprintf(path, sizeof(path), "%s/%s.txt", folder_name, decode(username));
    FILE* user_file = fopen(path, "a");
    if(user_file == NULL){
        perror("Error creating user file\n");
        return;
    }
    fprintf(user_file, "%d,%d", 0, 0);
    printf("\nDo you wish to sign in or exit ?\n");
    printf("Enter 's' to sign in\n");
    printf("Enter 'e' to exit\n");
    char op;
    printf("Enter here : ");
    scanf("%c", &op);
    getchar();
    while(op != 's' && op != 'e'){
        printf("\nInvalid input, enter again\n");
        printf("\nEnter Here : ");
        scanf("%c", &op);
        getchar();
    }
    if(op == 's') login_user();
    if(op == 'e') return;
    else{
        return;
    }
    fclose(user_file);
    free(username);
    free(password);
}


void init_program(){

    char line[71];
    char* username = (char*)malloc(20);
    char* password = (char*)malloc(20);
    // FILE* cred = fopen("credentials.txt", "r");
    FILE* new_cred = fopen("cred_encr.txt", "r");
    userData* data = NULL;
    while(fgets(line, sizeof(line), new_cred)){
        sscanf(line, "%[^,],%s", username, password);
        data = set_data(decode(username), decode(password));
        // fprintf(new_cred, "%s,%s\n", encode(username), encode(password));
        root = insert_data(root, data);
    }
    // getInorder(root);
    free(data);

    // getInorder(root);
    // printf("\n");


    printf("\n\nWelcome to your Personalized Task Planner, how do you want to proceed\n");
    printf("Enter 's' to sign-in\n");
    printf("Enter 'r' to sign-up\n");
    printf("Enter 'e' to exit\n");
    char op;
    printf("\nEnter Here : ");
    scanf("%c", &op);
    getchar();
    while(op != 's' && op != 'r' && op != 'e'){
        printf("\nInvalid option, re-enter : ");
        scanf("%c", &op);
        getchar();
    }
    if(op == 'e' || op == 'E') {
        printf("\nProgram Terminating...");
        return;
    }
    else if(op == 'r' || op == 'R'){
        register_user();
    }
    else if(op == 's' || op == 'S'){
        login_user();
    }
    free(username);
    free(password);
}