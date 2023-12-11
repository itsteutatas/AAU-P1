// Created by Hella Arman, november 2023
#include "main.h"
#include "driver.c"
#include "driver.h"

int main(void){
    /*char selection = ' ';
    double temperature, salinity, secchi_depth;

    //Open file "file1.txt" in writing mode
    FILE *f = fopen("file1.txt", "w");
    if (f == NULL) {
        printf("The file could not be accessed.");
        exit(EXIT_FAILURE);
    }

    //Initial prompt
    printf("This program needs an input of temperature, Secchi depth and salinity.\n"
           "With this input, it calculates whether the area is suitable for planting seagrass.\n\n");

    //Program loop, uses scan_selection() to determine whether program should run or exit
    while(selection != 'n') {
        selection = scan_selection();
        if(selection == 'y') {
            //Takes user input, prints the result, and saves the entry in the textfile
            input_parameters(&temperature, &salinity, &secchi_depth);
            print_full_result(temperature, salinity, secchi_depth);
            save_entry(f, temperature, salinity, secchi_depth);
        } else {
            //Closes file and exits program
            fclose(f);
            exit(EXIT_SUCCESS);
        }
    }*/
    return 0;
}