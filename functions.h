#ifndef FUNCTIONS_H                     // prevents the function being included more then ones.
#define FUNCTIONS_H

#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int tickerId;
    int seatCount;
    char bookedSeats[100];
    int bill;
} User;

typedef struct {
    char userName[20];
    char password[20];
} Admin;

typedef struct {
    char destination[30];
    int trainId;
    char cls[10];
} Train;

void loadTrains(Train trains[], int *countTrain);
void loadUsers(User users[], int *countUser);
void loadAdmins(Admin admins[], int *countAdmin);
void printTitle(char title[], int padding);
void printMenu(int choice);
void bookTicket(User users[], int *countUser);
void checkStatus(User users[], Train trains[]);
void saveTrains(Train trains[], int countTrain);
void saveUsers(User users[], int countUser);
void saveAdmins(Admin admins[], int countAdmin);
void saveAll(Train trains[], User users[], Admin admins[], int countTrain, int countUser, int countAdmin);



#endif