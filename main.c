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

    do {

        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif


        printf("1. User\n");
        printf("2. Admin\n");
        printf("3. Exit\n");
        printf("\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);


        // For Users
        if (choice == 1){
            #ifdef _WIN32
                system("cls");
            #else
                system("clear");
            #endif


            int tempChoice = 0;
            printf("1. Book a ticket\n");
            printf("2. Check Status\n");
            printf("3. Cancle Ticket\n");
            printf("4. Return to Main Menu\n");
            printf("\n");
            printf("Entet your choice: ");
            scanf("%d", &tempChoice);


            switch (tempChoice){
                case 1:
                    #ifdef _WIN32
                        system("cls");
                    #else
                        system("clear");
                    #endif

                    bookTicket(users, &countUser, trains, countTrain);
                    saveAll(trains, users, admins, countTrain, countUser, countAdmin);
                    printf("Press enter to continue!");
                    getchar();
                    break;

                case 2:
                    #ifdef _WIN32
                        system("cls");
                    #else
                        system("clear");
                    #endif

                    checkStatus(users, trains, countUser, countTrain);
                    saveAll(trains, users, admins, countTrain, countUser, countAdmin);
                    printf("Press enter to continue!");
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
                    printf("Press enter to continue!");
                    getchar();
                    break;

                case 4:
                    #ifdef _WIN32
                        system("cls");
                    #else
                        system("clear");
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
                #ifdef _WIN32
                    system("cls");
                #else
                    system("clear");
                #endif


                int tempChoice = 0;

                adminLogin(admins, &countAdmin);

                #ifdef _WIN32
                    system("cls");
                #else
                    system("clear");
                #endif

                printf("\n======= ADMIN PANNEL =======\n");
                printf("1. Update Status\n");
                printf("2. Return to Main Menu\n");
                printf("\n");
                printf("Enter your choice: ");
                scanf("%d", &tempChoice);

                if (tempChoice == 1){
                    #ifdef _WIN32
                        system("cls");
                    #else
                        system("clear");
                    #endif


                    int temp2 = 0;

                    printf("1. Add Train\n");
                    printf("2. Delete Train\n");
                    printf("3. Return to Main Menu\n");
                    printf("\n");
                    printf("Enter your choice: ");
                    scanf("%d", &temp2);

                    switch (temp2)
                    {
                    case 1:
                        #ifdef _WIN32
                            system("cls");
                        #else
                            system("clear");
                        #endif

                        addTrain(trains, &countTrain);
                        saveAll(trains, users, admins, countTrain, countUser, countAdmin);
                        printf("Press enter to continue!");
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
                        printf("Press enter to continue!");
                        getchar();
                        
                        break;

                    case 3:
                        #ifdef _WIN32
                            system("cls");
                        #else
                            system("clear");
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

            else if (choice == 3){
                exit;
            }

    }    while(choice != 3);

        



    return 0;
}