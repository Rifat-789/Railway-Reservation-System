#include "functions.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

void loadTrains(Train trains[], int *countTrain){
    FILE *pfile = fopen("train.dat", "rb");             // Opens train.dat file

    if(pfile == NULL){
        *countTrain = 0;
        return;
    }

    fread(countTrain, sizeof(int), 1, pfile);               // Reads number of trains from file
    fread(trains, sizeof(Train), *countTrain, pfile);           // Reads trains details

    fclose(pfile);
}

void loadUsers(User users[], int *countUser){
    FILE *pfile = fopen("user.dat", "rb");

    if(pfile == NULL){
        *countUser = 0;
        return;
    }

    fread(countUser, sizeof(int), 1, pfile);
    fread(users, sizeof(User), *countUser, pfile);

    fclose(pfile);
}

void loadAdmins(Admin admins[], int *countAdmin){
    FILE *pfile = fopen("admin.dat", "rb");

    if(pfile == NULL){
        *countAdmin = 0;
        return;
    }

    fread(countAdmin, sizeof(int), 1, pfile);
    fread(admins, sizeof(Admin), *countAdmin, pfile);

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
    srand(time(NULL));                      // generates random seed per second

    int randPart = rand() % 9000 + 1000;                // generates random 4 digit number for random part of ticker   

    int temp = countUser + 1;                       //  used for the first part of the ticket

    users[countUser].ticketId = (temp * 10000) + randPart;              // add both part and make a uniqe ticket id
}

void bookTicket(User users[], int *countUser, Train trains[], int countTrain){
    int tempChoice = 0;

    printf("\n======= AVAILABLE TRAINS =======\n\n");

    printf("%-4s| %-28s| %-15s| %-7s| %-14s| %-14s|\n","No. ", "Destination", "Available Seats", "Price", "Departure Date", "Departure Time");
    for (int i = 0; i < 96; i++){               // number of charecters defined
        printf("-");
    }

    printf("\n");

    for(int i = 0; i < countTrain; i++){
        char numstr[5];
        sprintf(numstr, "%d.", i + 1);

        printf("%-4s| %-28s| %-15d| %-7d| %-14s| %-14s|\n", numstr, trains[i].destination, trains[i].availableSeats, trains[i].price,
                trains[i].departureDate, trains[i].departureTime);
    }

    printf("\n");
    printf("Select Train: ");
    if (scanf("%d", &tempChoice) != 1){
        printf("Invalid input! Input must be a number\n");
        while (getchar() != '\n');
        return;
    }

    getchar();     // for input buffer

    #ifdef _WIN32                   //  Refresh page
        system("cls");
    #else
        system("clear");
    #endif
        

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

    printf("\n");

    printf("Enter your name: ");
    fgets(users[*countUser].name, sizeof(users[*countUser].name), stdin);                   // For strings with space
    users[*countUser].name[strcspn(users[*countUser].name, "\n")] = '\0';

    printf("\nHow many tickets: ");
    if (scanf("%d", &users[*countUser].ticketCount) != 1){
        printf("Invalid input! Input must be a number\n");
        while (getchar() != '\n');
        return;
    }

    getchar();

    if(users[*countUser].ticketCount < 1 || users[*countUser].ticketCount > 10){                // Max 10 tickets
        printf("Maximum 10 tickets allowed!\n");
        return;
    }

    if (users[*countUser].ticketCount > trains[index].availableSeats){                          // Available seats check upon ticket count
        printf("Not enough seats! Only %d seats availavble.\n", trains[index].availableSeats);
        return;
    }

    users[*countUser].trainId = trains[index].trainId;                      // Stores train id in user struct

    printf("\nTrain ID: %d\n", users[*countUser].trainId);

    users[*countUser].totalBill = trains[index].price * users[*countUser].ticketCount;                  // Calculates total bill 

    ticketGen(users, *countUser);

    printf("\nTotal Bill : %d\n", users[*countUser].totalBill);

    char confirm;
    printf("\nConfirm Booking?(y/n): ");
    scanf(" %c", &confirm);

    if (confirm != 'y' && confirm != 'Y'){
        printf("\nBooking cancled!\n");

        users[*countUser].totalBill = 0;
        users[*countUser].trainId = 0;
        users[*countUser].ticketCount = 0;
        return;
    }

    getchar();

    printf("\nAssigned Seats: ");

    for(int i = 0; i < users[*countUser].ticketCount; i++){                 // Assigns seat numbers continually
        users[*countUser].seats[i] = trains[index].nextSeat;
        printf("%d, ", trains[index].nextSeat);

        trains[index].nextSeat++;
        trains[index].availableSeats--;
    }

    printf("\n\nBooking Successful!\n\n");

    (*countUser)++;
}

void printTicket(User users[], Train trains[], int countTrain, int countUser){
    printf("\n======= TICKET ======\n");
    printf("Ticket ID: %d\n", users[countUser].ticketId);
    printf("Passenger: %s\n", users[countUser].name);
    printf("Train ID: %d\n", users[countUser].trainId);

    int trainIndex = -1;
    for (int i = 0; i < countTrain; i++){
        if (trains[i].trainId == users[countUser].trainId){
            trainIndex = i;
            break;
        }
    }

    if (trainIndex != -1){
        printf("Destination: %s\n", trains[trainIndex].destination);
        printf("Departure: %s at %s\n", trains[trainIndex].departureDate, trains[trainIndex].departureTime);
    }

    else{
        printf("Destionation: Unknown\n");
    }

    printf("Tickets       : %d\n", users[countUser].ticketCount);
    printf("Seats         : ");
    for (int i = 0; i < users[countUser].ticketCount; i++){
        printf("%d, ", users[countUser].seats[i]);
    }

    printf("\nTotal Bill  : %d\n", users[countUser].totalBill);
    printf("========================\n");
}

void checkStatus(User users[], Train trains[], int countUser, int countTrain){
    int choice;
    printf("\n======= CHECK TICKET STATUS =======\n");
    printf("1. Search by Ticket ID\n");
    printf("2. Search by Passenger Name\n");

    if (scanf("%d", &choice) != 1){
        printf("Invalid input! Input must be an integer\n");
        while (getchar() != '\n');
        return;
    }
    getchar();

    if (choice == 1){
        int tempId;
        printf("Enter Ticket ID: ");
        if (scanf("%d", &tempId) != 1){
            printf("Invalid input! Input must be an integer\n");
            while (getchar() != '\n');
            return;
        }

        int found = 0;
        for (int i = 0; i < countUser; i++){
            if (users[i].ticketId == tempId){
                printTicket(users, trains, countTrain, i);
                found = 1;
                break;
            }
        }

        if (!found){
            printf("No ticket found!\n");
        }

    }

    else if (choice == 2){
        char tempName[50];
        printf("Enter Passenger Name: ");
        fgets(tempName, sizeof(tempName), stdin);
        tempName[strcspn(tempName, "\n")] = '\0';

        int found = 0;
        for (int i = 0; i < countUser; i++){
            if (_stricmp(users[i].name, tempName) == 0){
                printTicket(users, trains, countTrain, i);
                found++;
            }
        }

        if (!found){
            printf("No tickets found!\n");
        }
        else{
            printf("\n%d booking(s) found.\n", found);
        }
    }

    else{
        printf("Invalid option!\n");
    }
}

void cancelTicket(User users[], int *countUser, Train trains[], int countTrain){
    int tempId;
    int index = -1;
    char confirm;

    printf("\n====== CANCLE TICKET ======\n");
    printf("Enter Ticket ID to Cancle: ");
    if(scanf("%d", &tempId) != 1){
        printf("Invalid Id! Id must be a number.\n");
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
    printTicket(users, trains, countTrain, index);

    printf("Are you sure you want to cancle? (y/n): ");
    scanf(" %c", &confirm);

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

    printf("Ticket canceled successfully.\n\n");

}

void adminLogin(Admin admins[], int *countAdmin){
    strcpy(admins[0].userName, "Rifat");
    strcpy(admins[0].password, "12345");

    strcpy(admins[1].userName, "Sayeem");
    strcpy(admins[1].password, "00000");

    *countAdmin = 2;

    char tempU[20];
    char tempP[20];
    printf("Enter Username: ");
    scanf("%s", tempU);

    if (strcmp(tempU, admins[0].userName) == 0 || strcmp(tempU, admins[1].userName) == 0){

        printf("\n");

        printf("Enter Password: ");
        scanf("%s", tempP);

        if (strcmp(tempU, admins[0].userName) == 0){
            if (strcmp(tempP, admins[0].password) == 0){
                printf("\nWelcome Rifat\n");
            }

            else{
                printf("\nInvalid Password!\n");
                return;
            }
        }

        else if(strcmp(tempU, admins[1].userName) == 0){
            if (strcmp(tempP, admins[1].password) == 0){
                printf("\nWelcome Sayeem\n");
            }

            else{
                printf("\nInvalid Password!\n");
                return;
            }
        }
            
    }
}

void addTrain(Train trains[], int *countTrain){
    printf("Enter Train Destination: ");
    fgets(trains[*countTrain].destination, sizeof(trains[*countTrain].destination), stdin);                 // scanf doesn't work
    trains[*countTrain].destination[strcspn(trains[*countTrain].destination, "\n")] = '\0';                 // strcspn - finds the first occurance of any charecter in a string

    printf("\nEnter Train ID: ");
    if (scanf("%d", &trains[*countTrain].trainId) != 1){
        printf("Invalid input! Input must be a number\n");
        while (getchar() != '\n');
        return;
    }

    getchar();

    printf("\nEnter Ticket price: ");
    if (scanf("%d", &trains[*countTrain].price) != 1){
        printf("Invalid input! Input must be a number\n");
        while (getchar() != '\n');
        return;
    }

    getchar();

    printf("\nEnter Total Seats: ");
    if (scanf("%d", &trains[*countTrain].totalSeats) != 1){
        printf("Invalid input! Input must be a number\n");
        while (getchar() != '\n');
        return;
    }

    getchar();

    printf("\nEnter Departure Date: ");
    fgets(trains[*countTrain].departureDate, sizeof(trains[*countTrain].departureDate), stdin);
    trains[*countTrain].departureDate[strcspn(trains[*countTrain].departureDate, "\n")] = '\0';

    printf("\nEnter Departure Time: ");
    fgets(trains[*countTrain].departureTime, sizeof(trains[*countTrain].departureTime), stdin);
    trains[*countTrain].departureTime[strcspn(trains[*countTrain].departureTime, "\n")] = '\0';

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
        printf("Invalid Id! Id must be a number.\n");
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
    scanf(" %c", &confirm);

    if (confirm != 'y' && confirm != 'Y'){
        printf("\nDeletion aborted.\n");
        return;
    }

    for (int i = index; i < *countTrain - 1; i++){
        trains[i] = trains[i + 1];
    }

    (*countTrain)--;

    printf("Train Deleted Successfully.\n\n");
}

void saveTrains(Train trains[], int countTrain){
    FILE *pFile = fopen("train.dat", "wb");

    if (pFile == NULL){
        printf("Error saving the data!");
        return;
    }

    fwrite(&countTrain, sizeof(int), 1, pFile);
    fwrite(trains, sizeof(Train), countTrain, pFile);

    fclose(pFile);
}

void saveUsers(User users[], int countUser){
    FILE *pFile = fopen("user.dat", "wb");

    if (pFile == NULL){
        printf("Error saving the data!");
        return;
    }

    fwrite(&countUser, sizeof(int), 1, pFile);
    fwrite(users, sizeof(User), countUser, pFile);

    fclose(pFile);
}

void saveAdmins(Admin admins[], int countAdmin){
    FILE *pFile = fopen("admin.dat", "wb");

    if (pFile == NULL){
        printf("Error saving the data!");
        return;
    }

    fwrite(&countAdmin, sizeof(int), 1, pFile);
    fwrite(admins, sizeof(Admin), countAdmin, pFile);

    fclose(pFile);
}

void saveAll(Train trains[], User users[], Admin admins[], int countTrain, int countUser, int countAdmin){
    saveTrains(trains, countTrain);
    saveUsers(users, countUser);
    saveAdmins(admins, countAdmin);
}