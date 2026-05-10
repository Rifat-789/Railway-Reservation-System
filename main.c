#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include "functions.h"

int main(){

    char title[] = "Railway Reservation System";
    int padding = (40 - strlen(title)) / 2;

    int choice = 0;
    Train trains[100];
    User users[100];
    Admin admins[100];

    int countTrain = 0, countUser = 0, countAdmin = 0;

    loadTrains(trains, &countTrain);
    loadUsers(users, &countUser);
    loadAdmins(admins, &countAdmin);

    do {
        #ifdef _WIN32
            system("clear");
        #else
            system("cls");
        #endif
        
        printTitle(title, padding);
        printfMenu(choice);
        scanf("%d", &choice);


        switch (choice)
        {
        case 1:
            #ifdef _WIN32
                system("clear");
            #else
                system("cls");
            #endif


            printf("Press enter to continue!");
            getchar();
            getchar();
            break;

        case 2:
            #ifdef _WIN32
                system("clear");
            #else
                system("cls");
            #endif

            
            printf("Press enter to continue!");
            getchar();
            getchar();
            break;

        case 3:
            #ifdef _WIN32
                system("clear");
            #else
                system("cls");
            #endif

            exit;
            printf("Press enter to continue!");
            getchar();
            getchar();
            break;
        
        default:
            break;
        }
    

    } while(choice != 3);




    return 0;
}