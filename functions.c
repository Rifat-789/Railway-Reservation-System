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

    users[countUser].ticketId = (temp * 10000) + randPart;
}

void bookTicket(User users[], int *countUser, Train trains[], int countTrain){
    int tempChoice = 0;

    printf("\n======= AVAILABLE TRAINS =======\n");

    for(int i = 0; i < countTrain; i++){

        printf("%d. %s\n", i + 1, trains[i].destination);

        printf("Train ID : %d\n", trains[i].trainId);

        printf("Price    : %d\n\n", trains[i].price);
    }

    printf("Select Train: ");
    scanf("%d", &tempChoice);

    // validation check
    if(tempChoice < 1 || tempChoice > countTrain){
        printf("Invalid Train Choice!\n");
        return;
    }

    int index = tempChoice - 1;

    printf("How many tickets: ");
    scanf("%d", &users[*countUser].ticketCount);

    if(users[*countUser].ticketCount < 1 || users[*countUser].ticketCount > 10){

        printf("Maximum 10 tickets allowed!\n");
        return;
    }

    users[*countUser].trainId = trains[index].trainId;

    printf("\nAssigned Seats: ");

    for(int i = 0; i < users[*countUser].ticketCount; i++){
        users[*countUser].seats[i] = (*countUser * 10) + i + 1;

        printf("%d ", users[*countUser].seats[i]);
    }

    users[*countUser].totalBill = trains[index].price * users[*countUser].ticketCount;

    ticketGen(users, *countUser);

    printf("Seats       : ");

    for(int i = 0; i < users[*countUser].ticketCount; i++){

        printf("%d ", users[*countUser].seats[i]);
    }

    printf("\nTotal Bill : %d\n", users[*countUser].totalBill);

    printf("\nBooking Successful!\n");

    (*countUser)++;
}

void checkStatus(User users[], Train trains[], int countUser, int countTrain){
    if (countUser == 0){
        printf("No bookings found!\n");
        return;
    }

    int trainIndex = -1;

    for (int i = 0; i < countTrain; i++){
        if (trains[i].trainId == users[countUser - 1].trainId){
            trainIndex = i;
            break;
        }
    }

    printf("\n\n======= TICKET =======\n");

    printf("Ticket ID   : %d\n", users[countUser - 1].ticketId);

    printf("Train ID    : %d\n", users[countUser - 1].trainId);

    if (trainIndex != -1){
        printf("Destination : %s\n", trains[trainIndex].destination);

        printf("Tickets     : %d\n", users[countUser - 1].ticketCount);

        printf("Seats       : ");

        for(int i = 0; i < users[countUser - 1].ticketCount; i++){

            printf("%d ", users[countUser - 1].seats[i]);
        }
        
        printf("\nTotal Bill: %d\n", users[countUser - 1].totalBill);
    }
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