//
//  cal_diets.c
//  Diets for Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define MAX_DIETS 100      			// Maximum number of diets
#define MAX_FOOD_NAME_LEN 50		// Maximum length of the name of food


// list of diets 
static Diet diet_list[MAX_DIETS];
static int diet_list_size = 0;


/*
    description : read the information in "diets.txt"
*/

void loadDiets(const char* DIETFILEPATH) {
    FILE *file = fopen(DIETFILEPATH, "r");
    if (file == NULL) {
        printf("There is no file for diets! \n");
        return;
    }

    // ToCode: to read a list of the diets from the given file
    // Read diet data from a file.
    
    char name[MAX_FOOD_NAME_LEN]; // to store the name of the food
    int calories;
    while (fscanf(file, "%s %d", name, &calories) == 2) {
    	// Read what is saved as "(food name) - (calorie) kcal" and save it to name and calories.
		// Make sure you read the two items (name and calories) well at this time.
        
        // Copy the string from name to diet_list[diet_list_size].name using the strncpy 
        strncpy(diet_list[diet_list_size].food_name, name, MAX_FOOD_NAME_LEN - 1);
        
        // Explicitly add null characters at the end of a string so that the string can end with null characters
		diet_list[diet_list_size].food_name[MAX_FOOD_NAME_LEN - 1] = '\0';
       
	    // Save the calories stored in the calories in the 'diet_list[].calories'.
        diet_list[diet_list_size].calories_intake = calories;
        diet_list_size++; // Diet information updated
        
        // Stop when the maximum number of diets is reached.
        if (diet_list_size >= MAX_DIETS){
            break;
        }
    }
    fclose(file);
}

/*
    description : to enter the selected diet and the total calories intake in the health data
    input parameters : health_data - data object to which the selected diet and its calories are added 
    return value : No
    
    operation : 1. provide the options for the diets to be selected
    			2. enter the selected diet and the total calories intake in the health data
*/

void inputDiet(HealthData* health_data) {
    int choice, i;
    
    // Diets list
    // Check if diets are available
    if (diet_list_size == 0) {
        printf("No diets available. Please load the data first.\n");
        return;
    }
    
    // ToCode: to provide the options for the diets to be selected
    printf("The list of diets:\n");
    // Display diet list
    for (i = 0; i < diet_list_size; i++) {
        printf("%d. %s - %d kcal\n", i + 1, diet_list[i].food_name, diet_list[i].calories_intake);
    }
    printf("0. Exit\n\n");
    
    
	// ToCode: to enter the diet to be chosen with exit option
    // Loop until a valid diet is selected
    while (1) {
    	
    	// Possibly falling into an infinite loop when the user enters incorrect data
		// Therefore, verification is required to confirm that the input is a number.
        printf("Enter the diet number: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a valid number.\n");
            while (getchar() != '\n'); // Clear the input buffer
            continue;
        }
        
        // Choose 0. Exit
        if (choice == 0) {
            printf("Diet selection canceled.\n");
            return;
        }
		
		// The selected number is greater than or equal to 1 and corresponds to the number in the diet list
        if (choice >= 1 && choice <= diet_list_size) {
            choice--; // Adjust index to match the array
            printf("\nSelected diet: %s - %d kcal\n", diet_list[choice].food_name, diet_list[choice].calories_intake);
            break;
        }
		else {
            printf("Invalid choice. Please select a valid diet number.\n");
        }
	}

    // ToCode: to enter the selected diet in the health data
    // Update health data with selected diet
    // Use the pointer to modify the diet_name value of the HealthData structure
	strncpy(health_data->diet[health_data->diet_count].food_name, diet_list[choice].food_name, MAX_FOOD_NAME_LEN - 1);
	health_data->diet[health_data->diet_count].food_name[MAX_FOOD_NAME_LEN - 1] = '\0'; // Ensure null-termination
	health_data->diet_count++;
	
    // ToCode: to enter the total calories intake in the health data
    // Update total calories intake in health data
	health_data->total_calories_intake += diet_list[choice].calories_intake;
	
	printf("Total calories intake - %d kcal\n", health_data->total_calories_intake);
}

