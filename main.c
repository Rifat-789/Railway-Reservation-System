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
    
    while (1){
        #ifdef _WIN32               // Reset the terminal screen
            system("cls");
        #else
            system("clear");
        #endif

        printTitle(title, padding);
        printf("1. User\n");
        printf("2. Admin\n");
        printf("3. Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        // For User
        if (choice == 1){
            int tempChoice = 0;

            while (tempChoice != 4){
                #ifdef _WIN32
                    system("cls");
                #else
                    system("clear");
                #endif

                printf("1. Book a ticket\n");
                printf("2. Check Status\n");
                printf("3. Cancle Ticket\n");
                printf("4. Return to Main Menu\n\n");
                printf("Entet your choice: ");
                scanf("%d", &tempChoice);
                getchar();

                switch (tempChoice){
                    case 1:
                        #ifdef _WIN32
                            system("cls");
                        #else
                            system("clear");
                        #endif

                        bookTicket(users, &countUser, trains, countTrain);
                        saveAll(trains, users, admins, countTrain, countUser, countAdmin);
                        printf("\nPress enter to continue...");
                        getchar();
                        break;

                    case 2:
                        #ifdef _WIN32
                            system("cls");
                        #else
                            system("clear");
                        #endif

                        checkStatus(users, trains, countUser, countTrain);
                        printf("\nPress enter to continue...");
                        getchar();
                        break;

                    case 3:
                        #ifdef _WIN32
                            system("cls");
                        #else
                            system("clear");
                        #endif

                        cancelTicket(users, &countUser, trains, countTrain);
                        saveAll(trains, users, admins, countTrain, countUser, countAdmin);
                        printf("\nPress enter to continue...");
                        getchar();
                        break;

                    case 4:
                        break;                      // Returns to main menu
                    
                        default:
                            printf("Invalid choice!\n");
                            getchar();
                        break;
                }
            }
        }

        // For Admin
        else if (choice == 2){
            #ifdef _WIN32
                system("cls");
            #else
                system("clear");
            #endif

            int tempChoice = 0;

            adminLogin(admins, &countAdmin);

            while (tempChoice != 2){

                #ifdef _WIN32
                    system("cls");
                #else
                    system("clear");
                #endif

                printf("======= ADMIN PANNEL =======\n");
                printf("1. Update Status\n");
                printf("2. Return to Main Menu\n\n");
                printf("Enter your choice: ");
                scanf("%d", &tempChoice);
                getchar();

                if (tempChoice == 1){
                    int temp2 = 0;

                    while (temp2 != 3){
                        #ifdef _WIN32
                            system("cls");
                        #else
                            system("clear");
                        #endif

                        printf("1. Add Train\n");
                        printf("2. Delete Train\n");
                        printf("3. Return to Admin Menu\n\n");
                        printf("Enter your choice: ");
                        scanf("%d", &temp2);
                        getchar();

                        switch (temp2){
                            case 1:
                                #ifdef _WIN32
                                    system("cls");
                                #else
                                    system("clear");
                                #endif

                                addTrain(trains, &countTrain);
                                saveAll(trains, users, admins, countTrain, countUser, countAdmin);
                                printf("\nPress enter to continue...");
                                getchar();
                                
                                break;

                            case 2:
                                #ifdef _WIN32
                                    system("cls");
                                #else
                                    system("clear");
                                #endif

                                deleteTrain(trains, &countTrain);
                                saveAll(trains, users, admins, countTrain, countUser, countAdmin);
                                printf("\nPress enter to continue...");
                                getchar();
                                
                                break;

                            case 3:
                                break;                  // Returns to admin menu
                            
                            default:
                                printf("Invalid choice!\n");
                                getchar();
                                break;
                        }
                    }
                }  

                else if (tempChoice == 2){
                    break;
                }
            }
        }

        else if (choice == 3){
            printf("Goodbye!\n");
            exit(0);
        }
    }

    return 0;
}