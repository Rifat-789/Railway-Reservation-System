#include "functions.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

void loadTrains(Train trains[], int *countTrain){
    FILE *pfile = fopen("train.dat", "rb");

    if(pfile == NULL){
        *countTrain = 0;
        fclose(pfile);
        return;
    }

    fread(countTrain, sizeof(int), 1, pfile);
    fread(trains, sizeof(Train), *countTrain, pfile);

    fclose(pfile);

}

void loadUsers(User users[], int *countUser){

}

void loadAdmins(Admin admins[], int *countAdmin){

}

void printTitle(char title[], int padding){

}

void printMenu(int choice){

}

void bookTicket(User users[], int *countUser){

}

void checkStatus(User users[], Train trains[]){

}


