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

void ticketGen(User users[], int countUser){
    srand(time(NULL));

    int randPart = rand() % 9000 + 1000;

    int temp = countUser + 1;

    users[countUser].tickerId = (temp * 10000) + randPart;
}

void bookTicket(User users[], int *countUser, Train trains[], int countTrain){
    int tempChoice = 0;

    printf("--- AVAILABLE DESTINATIONS ---");
    
    for (int i = 0; i < countTrain; i++){
        printf("%d. %s", i + 1, trains[i].destination);
    }

    printf("Enter your choice: ");
    scanf("%d", &tempChoice);

    if (tempChoice < 1 || tempChoice > countTrain){
        printf("Invalid choice!");
        return;
    }

    int index = tempChoice - 1;

    printf("\nDestination: %s\n", trains[index].destination);
    printf("Ticket price: %d\n", trains[index].price);

    int tempChoice2 = 0;
    printf("1. Pay\n");
    printf("2. Cancle\n");
    printf("Enter your choice: ");
    scanf("%d", &tempChoice2);

    if (tempChoice2 == 1){
        users[*countUser].bill = trains[index].price;
        users[*countUser].seatCount = *countUser + 1;

        ticketGen(users, *countUser);
        printf("\nBooking successfull!\n");

        printf("Seat Number: %d\n", users[*countUser].seatCount);
        printf("Ticket ID: %d\n", users[*countUser].tickerId);
        printf("Bill: %d\n", users[*countUser].bill);

        (*countUser)++;
    }

    else {
        printf("Booking cancled!\n");
        return;
    }
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

void saveAll(Train trains[], User users[], Admin admins[], int countTrain, int countUser, int countAdmin){
    saveTrains(trains, countTrain);
    saveUsers(users, countUser);
    saveAdmins(admins, countAdmin);
}