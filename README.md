# User Management System
A CLI based User-Management-System coded in C Language including User Management, Authorization
and the core logic of a To-Do-List.

## Functionality
On compiling the program, we get 3 options, to :
1. Login
2. Register
3. Exit

When users login to the platform, they get the following options : 
1. Add task
2. View Tasks
3. Remove a task

New Users can register on the Platform by providing a unique username and a password.

## Redundancy Check
When a new users creates an account, the program ensures that he selects a unique 
username which is not taken by anyone else.

## Password Strength Checker
Programs informs registering users if their password is weak, or does not
follow proper guidelines.

## How to Run this in your system ? 
Clone this repository in your device using the following commands :  <br><br>
```
git clone https://github.com/divyayush-v-20/User-Management-System
cd User-Management-System
```
<br><br>
Run the following commands in the terminal: <br> <br>
```
1. gcc main.c -o ex -L. library.a
2. ./ex
```
<br><br>
And you are ready to go!
