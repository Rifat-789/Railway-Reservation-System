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
        printf("Availabel Seats: %d\n", trains[i].availableSeats);
    }

    printf("Select Train: ");
    scanf("%d", &tempChoice);

    // validation check
    if(tempChoice < 1 || tempChoice > countTrain){
        printf("Invalid Train Choice!\n");
        return;
    }

    int index = tempChoice - 1;

    if (trains[index].availableSeats == 0){                 // Availability check
        printf("Sorry, this train is fully booked!");
        return;
    }

    printf("How many tickets: ");
    scanf("%d", &users[*countUser].ticketCount);

    if(users[*countUser].ticketCount < 1 || users[*countUser].ticketCount > 10){                // Max 10 tickets
        printf("Maximum 10 tickets allowed!\n");
        return;
    }

    if (users[*countUser].ticketCount > trains[index].availableSeats){                          // Available seats check upon ticket count
        printf("Not enough seats! Only %d seats availavble.\n", trains[index].availableSeats);
        return;
    }

    users[*countUser].trainId = trains[index].trainId;                      // Stores train id in user struct

    printf("\nAssigned Seats: ");

    for(int i = 0; i < users[*countUser].ticketCount; i++){                 // Assigns seat numbers continually
        users[*countUser].seats[i] = trains[index].nextSeat;
        printf("%d ", trains[index].nextSeat);

        trains[index].nextSeat++;
        trains[index].availableSeats--;
    }

    printf("\n");

    users[*countUser].totalBill = trains[index].price * users[*countUser].ticketCount;                  // Calculates total bill 

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

void cancelTicket(User users[], int *countUser, Train trains[], int countTrain){
    int tempId;
    int index = -1;
    char confirm;

    printf("\n====== CANCLE TICKET ======\n");
    printf("Enter Ticket ID to Cancle: ");
    if(scanf("%d", &tempId) != 1){
        printf("Invalid Id! Id must be a number.");
        while(getchar() != '\n');
        return;
    }

    for (int i = 0; i < *countUser; i++){
        if (tempId == users[i].ticketId){
            index = i;
            break;
        }
    }

    if (index == -1){
        printf("\nTicket Not Found!\n");
        return;
    }

    printf("Canceling the following booking: \n");
    checkStatus(users, trains, countUser, countTrain);

    printf("Are you sure you want to cancle? (y/n): ");
    scanf("% c", &confirm);

    if (confirm != 'y' && confirm != 'Y'){
        printf("Cancellation aborted.\n");
        return;
    }

    for (int i = 0; i < countTrain; i++){                           // Restore trains availave seats
        if (trains[i].trainId == users[index].trainId){
            trains[i].availableSeats += users[index].ticketCount;
            break;
        }
    }

    for (int i = index; i < *countUser - 1; i++){
        users[i] = users[i + 1];
    }

    (*countUser)--;

    printf("Ticket canceled successfully.\n");

}

void addTrain(Train trains[], int *countTrain){

    printf("Enter Train Destination: ");
    scanf("%s", &trains[*countTrain].destination);

    printf("\nEnter Train ID: ");
    scanf("%d", &trains[*countTrain].trainId);

    printf("\nEnter Ticket price: ");
    scanf("%d", &trains[*countTrain].price);

    printf("\nEnter Total Seats: ");
    scanf("%d", &trains[*countTrain].totalSeats);

    trains[*countTrain].availableSeats = trains[*countTrain].totalSeats;
    trains[*countTrain].nextSeat = 1;

    (*countTrain)++;

    printf("\nTrain Added Successfully.\n");
}

void deleteTrain(Train trains[], int *countTrain){
    int tempId;
    int index = -1;
    char confirm;

    printf("\n====== DELETE TRAIN ======\n");
    printf("Enter Train ID to Cancle: ");
    if(scanf("%d", &tempId) != 1){
        printf("Invalid Id! Id must be a number.");
        while(getchar() != '\n');
        return;
    }

    for (int i = 0; i < *countTrain; i++){
        if (tempId == trains[i].trainId){
            index = i;
            break;
        }
    }

    if (index == -1){
        printf("\nTrain Not Found!\n");
        return;
    }

    printf("Train ID: %d\n", trains[index].trainId);
    printf("Destination: %s\n", trains[index].destination);
    printf("Available seats: %d\n", trains[index].availableSeats);
    printf("Ticket Price: %d\n", trains[index].price);

    printf("Are you sure you want to Delete? (y/n): ");
    scanf("% c", &confirm);

    if (confirm != 'y' && confirm != 'Y'){
        printf("\nDeletion aborted.\n");
        return;
    }

    for (int i = index; i < *countTrain - 1; i++){
        trains[i] = trains[i + 1];
    }

    (*countTrain)--;

    printf("Train Deleted Successfully.\n");
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