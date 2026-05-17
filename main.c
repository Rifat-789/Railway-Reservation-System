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
    
    printTitle(title, padding);

    printf("1. User\n");
    printf("2. Admin\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);


    // For Users
    if (choice == 1){
        int tempChoice = 0;
        printf("1. Book a ticket\n");
        printf("2. Check Status\n");
        printf("3. Cancle Ticket\n");
        printf("4. Exit\n");
        printf("Entet your choice: ");
        scanf("%d", &tempChoice);


        switch (tempChoice){
            case 1:
                #ifdef _WIN32
                    system("clear");
                #else
                    system("cls");
                #endif

                bookTicket(users, &countUser, trains, countTrain);
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

                checkStatus(users, trains, countUser, countTrain);
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

                cancelTicket(users, &countUser, trains, countTrain);
                printf("Press enter to continue!");
                getchar();
                getchar();
                break;

            case 4:
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
    }


    // For Admin
        else if (choice == 2){
            int tempChoice = 0;

            printf("1. Update Status\n");
            printf("2. Exit\n");
            scanf("%d", &tempChoice);

            if (tempChoice == 1){
                int temp2 = 0;

                printf("1. Add Train\n");
                printf("2. Delete Train\n");
                printf("3. Exit\n");
                scanf("%d", &temp2);

                switch (temp2)
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
            }
            


            
            
        }

        



    return 0;
}