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
    FILE *pfile = fopen("train.dat", "rb");

    if(pfile == NULL){
        *countUser = 0;
        fclose(pfile);
        return;
    }

    fread(countUser, sizeof(int), 1, pfile);
    fread(users, sizeof(Train), *countUser, pfile);

    fclose(pfile);
}

void loadAdmins(Admin admins[], int *countAdmin){
    FILE *pfile = fopen("train.dat", "rb");

    if(pfile == NULL){
        *countAdmin = 0;
        fclose(pfile);
        return;
    }

    fread(countAdmin, sizeof(int), 1, pfile);
    fread(admins, sizeof(Train), *countAdmin, pfile);

    fclose(pfile);
}

void printTitle(char title[], int padding){
    for (int i = 0; i < 40; i++){
        printf("-");
    }
    printf("\n");

    for (int i = 0; i < padding; i++){
        printf(" ");
    }
    
    printf("%s\n", title);

    for (int i = 0; i < 40; i++){
        printf("-");
    }
    printf("\n");
}

void printMenu(int choice){
    int temp = 0;

    printf("1. User\n");
    printf("2. Admin\n");
    printf("Enter your choice: ");
    scanf("%d", &temp);

    if (temp == 1){
        printf("1. Book A Ticket\n");
        printf("2. Check Status\n");
        printf("3. Cancle Ticket\n");
        printf("4. Edit Ticket\n");
        printf("5. Exit\n");
    }

    if (temp == 2){
        printf("1. Check Train Status\n");
        printf("2. Edit Train status\n");
        printf("3. Check Passangers\n");
        printf("4. Edit Passanger Status\n");
        printf("5. Exit\n");
    }
    
}

void bookTicket(User users[], int *countUser){

}

void checkStatus(User users[], Train trains[]){

}

void saveTrains(Train trains[], int countTrain){
    FILE *pFile = fopen("train.dat", "wb");

    if (pFile == NULL){
        printf("Error saving the data!");
        fclose(pFile);
        return;
    }

    fwrite(&countTrain, sizeof(int), 1, pFile);
    fwrite(trains, sizeof(Train), countTrain, pFile);

    fclose(pFile);
}

void saveUsers(User users[], int countUser){
    FILE *pFile = fopen("train.dat", "wb");

    if (pFile == NULL){
        printf("Error saving the data!");
        fclose(pFile);
        return;
    }

    fwrite(&countUser, sizeof(int), 1, pFile);
    fwrite(users, sizeof(Train), countUser, pFile);

    fclose(pFile);
}

void saveAdmins(Admin admins[], int countAdmin){
    FILE *pFile = fopen("train.dat", "wb");

    if (pFile == NULL){
        printf("Error saving the data!");
        fclose(pFile);
        return;
    }

    fwrite(&countAdmin, sizeof(int), 1, pFile);
    fwrite(admins, sizeof(Train), countAdmin, pFile);

    fclose(pFile);
}
