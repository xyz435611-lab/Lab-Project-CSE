#include <stdio.h>
#include <menu/menu.h>
#include <errno.h>
#include <string.h>
#include "globals.h"

AppState manageResults()
{
    int choice;
    while (1)
    {

        printf("\nManage Results\n");
        printf("--------------\n");
        unsigned int roll;
        printf("Enter Student Roll to view results: ");
        scanf("%u", &roll);
        getchar();

        int status;

        status = MKDIR("data", 0777);
        if (status == -1 && errno != EEXIST)
        {
            perror("Accessing data failed");
            return STATE_MAIN_MENU;
        }

        status = MKDIR("data/results", 0777);
        if (status == -1 && errno != EEXIST)
        {
            perror("Accessing data/results failed");
            return STATE_MAIN_MENU;
        }

        char foldername[30];
        sprintf(foldername, "data/results/%u", roll);
        status = MKDIR(foldername, 0777);
        if (status == -1 && errno != EEXIST)
        {
            perror("Accessing data/results failed");
            return STATE_MAIN_MENU;
        }

        printf("Result of Roll %u\n", roll);
        printf("----------------------\n");
        printf("1. CT\n");
        printf("2. Term\n");
        printf("3. Overall\n");
        printf("4. Go Back\n");
        printf("5. Return to main menu\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        FILE *fp;
        switch (choice)
        {
        case 1:
        {
            fp = fopen(strcat(foldername, "/ct.txt"), "a+");
            if (fp == NULL)
            {
                perror("Failed to open ct.txt");
                return STATE_MAIN_MENU;
            }
            printf("CT Results\n");
            printf("----------\n");
            break;
        }
        case 2:
        {
            fp = fopen(strcat(foldername, "/term.txt"), "a+");
            if (fp == NULL)
            {
                perror("Failed to open term.txt");
                return STATE_MAIN_MENU;
            }
            printf("Term Results\n");
            printf("------------\n");
            break;
        }
        case 3:
        {
            printf("Overall Results\n");
            printf("---------------\n");
            break;
        }
        case 4:
        {
            return STATE_RESULT_MENU;
            break;
        }
        case 5:
        {
            printf("Return to Main Menu\n");
            return STATE_MAIN_MENU;
        }
        default:
        {
            printf("Invalid choice!\n");
            break;
        }
        }

        fclose(fp);
    }
}