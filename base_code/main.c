//
//  main.c
//  Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define EXERCISEFILEPATH "exercises.txt"
#define DIETFILEPATH "diets.txt"
#define HEALTHFILEPATH "health_data.txt"

static int choice;

int main() {
	// To initialize the health data object
    HealthData health_data = {0};
    
    // Tocode: to read the list of the exercises and diets
    loadExercises(EXERCISEFILEPATH); // Load exercises from file
    loadDiets(DIETFILEPATH);         // Load diets from file

    // ToCode: to run the "Healthcare Management Systems" until all calories are used up or the user wants to exit the system
    do {
    	if (health_data.total_calories_intake >= DAILY_CALORIE_GOAL){
            printf("You have consumed all your calories for today! \n");
		} 
		else{
			printf("\n=======================================================================\n");
        	printf("[Healthcare Management Systems] \n");
        	printf("1. Exercise \n");
        	printf("2. Diet \n");
        	printf("3. Show logged information \n");
        	printf("4. Exit \n");
        	printf("Select the desired number: ");
        	scanf("%d", &choice);
        	printf("=======================================================================\n");
        }
        
		// ToCode: to run the sysmtem based on the user's choice
        switch (choice) {
            case 1:
            	inputExercise(&health_data); // Call function to input exercise data
                break;
                
            case 2:
            	inputDiet(&health_data);     // Call function to input diet data
                break;
                
            case 3:
            	printHealthData(&health_data); // Display logged exercise and diet information
                break;
                
            case 4:
            	
    			printf("Exit the system.\n"); // Exit message
    			printf("=======================================================================\n");
                break;
                
            default:
                printf("[Error] Invalid option. \n"); // Error message for invalid option
                printf("Please try again! \n");
        }
    } while (health_data.total_calories_intake < DAILY_CALORIE_GOAL && choice != 4); 
	// Continue until calories are consumed or user exits

    return 0;
}

