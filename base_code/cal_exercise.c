//
//  cal_exercise.c
//  Excercise for Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define MAX_EXERCISES 100  			// Maximum number of exercises
#define MAX_EXERCISE_NAME_LEN 50	// Maximum length of the name of exercise


// To declare the structure of the exercises
static Exercise exercise_list[MAX_EXERCISES];
int exercise_list_size = 0;


/*
    description : read the information in "excercises.txt"
*/

void loadExercises(const char* EXERCISEFILEPATH) {
    FILE *file = fopen(EXERCISEFILEPATH, "r");
    if (file == NULL) {
        printf("There is no file for exercises! \n");
        return;
    }

    // ToCode: to read a list of the exercises from the given file
    char line[100]; // To store each line from the file
    
    while (fgets(line, sizeof(line), file) != NULL) {
    	
        // Parse the line: "<exercise_name> - <calories> kcal"
        char name[MAX_EXERCISE_NAME_LEN];
        int calories;
        
		// Extract the name and calories using sscanf
        if (sscanf(line, "%s - %d kcal", name, &calories) == 2) {
        	// Store the parsed data in the exercise_list
            strncpy(exercise_list[exercise_list_size].name, name, MAX_EXERCISE_NAME_LEN);
            exercise_list[exercise_list_size].calories_burned_per_minute = calories;
            exercise_list_size++;

            // Stop if the list exceeds the maximum allowed size
            if (exercise_list_size >= MAX_EXERCISES) {
                printf("Exercise list is full. Maximum %d exercises are supported.\n", MAX_EXERCISES);
                break;
            }    
        } 
		else {
            printf("Error parsing line: %s", line); // Handle incorrect format
        }
    }
}


/*
    description : to enter the selected exercise and the total calories burned in the health data
    input parameters : health_data - data object to which the selected exercise and its calories are added 
    return value : No
    
    operation : 1. provide the options for the exercises to be selected
    			2. enter the duration of the exercise
    			3. enter the selected exercise and the total calories burned in the health data
*/

void inputExercise(HealthData* health_data) {
    int choice, duration, i;
    
    // Exercise list
    // Check if exercises are available
    if (exercise_list_size == 0) {
        printf("No exercises available. Please load the data first.\n");
        return;
    }
    
    // ToCode: to provide the options for the exercises to be selected
    // Display exercise list
    printf("[Exercises]\n");
    for (int i = 0; i < exercise_list_size; i++) {
        printf("%d. %s - %d kcal\n", i + 1, exercise_list[i].name, exercise_list[i].calories_burned_per_minute);
    }
    printf("0. Exit\n\n");
    
    // ToCode: to enter the exercise to be chosen with exit option
	// Loop until a valid exercise is selected
    while (1) {
    	
    	// Possibly falling into an infinite loop when the user enters incorrect data
		// Therefore, verification is required to confirm that the input is a number.
        printf("Enter the exercise number: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a valid number.\n");
            while (getchar() != '\n'); // Clear the input buffer
            continue;
        }

		// Choose 0. Exit
        if (choice == 0) {
            printf("Exercise selection canceled.\n");
            return;
        }

		// The selected number is greater than or equal to 1 and corresponds to the number in the exercise list
        if (choice >= 1 && choice <= exercise_list_size) {
            choice--; // Adjust index to match the array
            // Read and output the selected exercise in the field storing the name and calories of the exercise selected by the user.
            printf("Selected exercise: '%s' (%d kcal/min)\n", exercise_list[choice].name, exercise_list[choice].calories_burned_per_minute);

            // Input and validate duration
            printf("Enter the duration of the exercise (in min.): ");
            
			while (1) {
				
				// Add verification logic to prevent negative or zero exercise times.	
                if (scanf("%d", &duration) != 1 || duration <= 0) {
                    printf("Invalid duration. Please enter a positive number.\n");
                    while (getchar() != '\n'); // Clear the input buffer
                } else {
                    break;
                }
            }

            // Calculate the calories from the selected exercise and the time entered to store the total calories burned in the variable
            int calories_burned = duration * exercise_list[choice].calories_burned_per_minute;
            
            //Use the pointer to modify the calories_burned value of the HealthData structure.
            health_data->calories_burned += calories_burned;

            printf("Calories burned: %d kcal\n", calories_burned);
            return;
        } 
		else {
            printf("Invalid choice. Please select a valid exercise number.\n");
        }
    }
}
