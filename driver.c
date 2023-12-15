#include "stdio.h"
#include "stdlib.h"
#include "driver.h"
#include "string.h"
#define MAX_STRING_LENGTH 20

// Used in main to choose whether more data entries should be made, or the program should end. Returns 'y' for a yes and 'n' for a no.
char scan_selection() {
    char selection = ' ';
    printf("\n\nWould you like to make a data entry?\nFor yes, type 'y':\nFor no, type 'n':\n");
    scanf(" %c", &selection);
    return selection;
}

/*  This function prompts and scans for the three measured values of temperature, salinity and Secchi depth.
 *  It first asks the user for temperature and salinity parameters. It will only ask for Secchi depth input if set parameters
 *  fulfill minimum requirements (check_input function).
 */
void input_parameters(double *temperature, double *salinity, double *secchi_depth, char location[]) {
    char temp[MAX_STRING_LENGTH];
    char sal[MAX_STRING_LENGTH];

    printf("\nMeasure the temperature in degrees Celsius, then input the value without unit and press enter: ");
    scanf(" %s", temp); // Insert input in a string in order to check if it is a number

    printf("\nMeasure the salinity in ppt, then input the value without unit and press enter: ");
    scanf(" %s", sal);

    // 'atoi' uses ASCII codes to check for char and int in a string. It returns 0 if their is a char and a number other than 0 if there are only int
    if (atoi(temp) == 0 || atoi(sal) == 0) {    // Check if input is a number using 'atoi'
        printf("Invalid input");
        input_parameters(temperature, salinity, secchi_depth, location);
    }
    else {
        *temperature = atoi(temp);                  // 'atoi' converts string to int
        *salinity = atoi(sal);
        check_parameter_input(*temperature, *salinity, secchi_depth, location);
        input_location(location);
    }
}

/*  This function prompts the user to enter a location. If the input is invalid, the user will be prompted to re-enter a location
 *  by calling itself again as a recursive function.
 */
void input_location(char location[]){
    printf("\nEnter the location from which the parameters are derived. Please do not enter invalid danish letters.\n");
    if (scanf(" %s", location)) {
        int check = check_location_input(location); //Checks if the user has input a valid location without using invalid letters such as æ/Æ, ø/Ø, å/Å.
        if (check == 1){
            input_location(location); //Recursive function
        }
    }
    else {
        input_location(location); //Recursive function
    }
}

/*  This function checks if the user input is valid. The limits are based on data for highest and lowest measurements of
 *  temperature and salinity in Danish waters. It will only prompt for Secchi depth input if set parameters
 *  fulfill minimum requirements.
 */
void check_parameter_input(double temperature, double salinity, double *secchi_depth, char location[]) {
    int invalid = 0;

    if (temperature <= -10 || temperature >= 30) {  // Checks if temperature is more or less than the common temperature of Danish waters
        printf("Your temperature input is invalid.\n");
        invalid = 1;  // If temperature is out of range, do not ask for Secchi depth
    }

    if (salinity < 0 || salinity > 35) {    // Checks if salinity is more or less than the common salinity of Danish waters
        printf("Your salinity input is invalid.\n");
        invalid = 1;  // If salinity is out of range, do not ask for Secchi depth
    }

    // If temperature and salinity are correct and show positive conditions for seagrass (see calc_t_bracket & calc_s_bracket), ask for Secchi depth
    if ((invalid != 1) && (temperature >= 5 || temperature < 25 || salinity >= 5 ||salinity < 30)) {
        char secchi[MAX_STRING_LENGTH];

        printf("\nMeasure the secchi depth in centimeter, then input the value without unit and press enter:");

        int check = scanf(" %s", secchi);
        *secchi_depth = atoi(secchi);
        if (check != 1 || *secchi_depth < 0 || atoi(secchi) == 0 || *secchi_depth > 1000) { // If 'scanf' is not equal to 1, it means that it failed to read a valid number. Check also if input is a number
            printf("Your Secchi depth input is invalid.\n");
            check_parameter_input(temperature, salinity, secchi_depth, location);
        }
    }
    else {   // If inputs are invalid, the program will prompt the user to enter parameters again.
        input_parameters(&temperature, &salinity, secchi_depth, location);
    }

}

/*  This function checks if there are any invalid letters (æ/Æ, ø/Ø, å/Å) in the location input using 'strstr' function.
 *  NOTE: Reads only the first æ/ø/å in the input, and not the rest
 */
int check_location_input(char location[]){

    if (strstr(location, "æ") || strstr(location, "Æ")) {   // 'strstr' searches for the (little) substring "æ"/"Æ" in the (big) main string.
        printf("Invalid input. Please use ae or AE.\n");
        return 1;
    }
    if (strstr(location, "ø") || strstr(location, "Ø")) {   // 'strstr' searches for the (little) substring "ø"/"Ø" in the (big) main string.
        printf("Invalid input. Please use oe or OE.\n");
        return 1;
    }
    if (strstr(location, "å") || strstr(location, "Å")) {   // 'strstr' searches for the (little) substring "å"/"Å" in the (big) main string.
        printf("Invalid input. Please use aa or AA.\n");
        return 1;
    }
    else{
        return 0;
    }
}

// This function saves an entry of the three values into the opened file, f.
void save_entry(FILE* f, double temperature, double salinity, double secchi_depth, char location[]) {
    fprintf(f, "%.1lf degrees Celsius | %.1lf ppt salinity | %.1lf centimeters | Location: %s\n", temperature, salinity, secchi_depth, location);
}

// This function checks which bracket the temperature input falls into. It returns an integer corresponding to the bracket
int calc_t_bracket(double c) {
    if (c < 5) {
        return 1; //Returns 1 for a bad result with stunted growth
    } else if (c < 10) {
        return 2; //Returns 2 for a fine result
    } else if (c < 15){
        return 3; //Returns 3 for a good result
    } else if (c < 21) {
        return 4; //Returns 4 for an optimal result
    } else if (c < 25) {
        return 5; //Returns 5 for a fine result
    } else if (c < 30){
        return 6; //Returns 6 for a bad result with stunted reproduction
    } else {
        return 7; //Returns 7 for a bad result with high mortality
    }
}

void print_temperature_result(int t) {
    switch (t) {
        case 1:
            printf("he current temperature conditions are poor, as the water temperature is too low");
            break;
        case 2:
            printf("he current temperature conditions are fine, albeit slightly low");
            break;
        case 3:
            printf("he current temperature conditions are good");
            break;
        case 4:
            printf("he current temperature conditions are optimal");
            break;
        case 5:
            printf("he current temperature conditions are fine, albeit slightly high");
            break;
        case 6:
            printf("he current temperature conditions are poor, as the water temperature is too high");
            break;
        case 7:
            printf("he current temperature conditions are severe, as the temperature is much too high");
    }
}

void print_secchi_result(int mdl) {
    printf("The water clarity in this area allows seagrass to be planted at a max depth of %d centimetres to survive.", mdl);
}

// Check which bracket salinity input falls into. Returns: Returns: Int corresponding with bracket
int calc_s_bracket(double s) {
    if(s < 5){
        return 1; // Returns 1 for a bad result with high mortality
    }
    else if(s < 9) {
        return 2; // Returns 2 for a OK Result
    }
    else if(s < 26) {
        return 3; // Returns 3 for a optimal result
    }
    else if( s < 30) {
        return 4; // Returns 4 for a OK result
    }
    else {
        return 5; // Returns 5 for a not good result
    }
}

// This function checks the maximum depth limit based on Secchi depth. The max depth limit determines how deep seagrass
// can be planted.
// It returns an integer of the max depth limit in centimeters, rounded down.
int calc_mdl(double sd) {   // mdl = max depth limit
    return sd * 0.95;
}

// Takes a parameter of salinity bracket and prints a string that represents the salinity bracket.
void print_salinity_result(int salinity_bracket){
    switch (salinity_bracket) {
        case 1:
            printf("he current salinity level is too low");
            break;
        case 2:
            printf("he current salinity level is OK");
            break;
        case 3:
            printf("he current salinity level is optimal");
            break;
        case 4:
            printf("he current salinity level is OK");
            break;
        case 5:
            printf("he current salinity level is too high");
            break;
    }
}

// Encapsulates the previous functions; finds brackets for temperature and salinity, finds the max depth limit, and
// prints a combined result.
void print_full_result(double temperature, double salinity, double secchi_depth) {
    int t_bracket = calc_t_bracket(temperature);
    int s_bracket = calc_s_bracket(salinity);
    int mdl = calc_mdl(secchi_depth);

    // Four options:
    if(t_bracket == 1 || t_bracket > 5) { // 1) Temperature is too extreme, print temperature first and salinity after
        printf("It is not recommended to plant seagrass in this area.\nT");
        print_salinity_result(s_bracket);
        printf(", and t");
        print_temperature_result(t_bracket);
        printf(". Seagrass planted here will not survive.\n");
    }
    else if (s_bracket == 1 || s_bracket == 5) { // 2) Salinity is too extreme, print salinity first and temperature after
        printf("It is not recommended to plant seagrass in this area.\nT");
        print_salinity_result(s_bracket);
        printf(", and t");
        print_temperature_result(t_bracket);
        printf(". Seagrass planted here will not thrive.\n");
    }
    else if (t_bracket == 2 || t_bracket == 5 || s_bracket == 2 || s_bracket == 4) { // 3) None of the parameters are too extreme
        printf("The conditions for planting seagrass are good enough, but could be better.\nT");
        print_temperature_result(t_bracket);
        printf(", and t");
        print_salinity_result(s_bracket);
        printf(". Seagrass planted here will survive, but not thrive.\n");
        print_secchi_result(mdl);
    }
    else { // 4) Optimal conditions for both temperature and salinity
        printf("This area is recommended for planting seagrass.\nT");
        print_temperature_result(t_bracket);
        printf(", and t");
        print_salinity_result(s_bracket);
        printf(". Seagrass planted here will thrive.\n");
        print_secchi_result(mdl);
    }
}

int main(){
    char selection;
    char location[MAX_STRING_LENGTH];
    double temperature = 0, salinity = 0, secchi_depth = 0;

    // Initial prompt
    printf("\nThis program needs an input of temperature, Secchi depth and salinity."
           " With this input, it calculates and determines whether the area is suitable for planting seagrass.");

    // Program loop, uses scan_selection() to determine whether program should run or exit
    while(1) {
        selection = scan_selection();
        if (selection == 'y' || selection == 'Y') {
            // Open file "file1.txt" in writing mode
            FILE *f = fopen("file1.txt", "a"); // "a" appends to a file. Writing operations, append data at the end of the file. The file is created if it does not exist.
            if (f == NULL) {
                printf("The file could not be accessed.");
                exit(EXIT_FAILURE);
            }

            // Takes user input, prints the result, and saves the entry in the textfile
            input_parameters(&temperature, &salinity, &secchi_depth, location);
            print_full_result(temperature, salinity, secchi_depth);
            save_entry(f, temperature, salinity, secchi_depth, location);
            fclose(f);
        }
        else if (selection == 'n' || selection == 'N') {
            // Closes file and exits program
            exit(EXIT_SUCCESS);
        }
        else {
            printf("Input not valid. Please write y or n\n");
        }
    }
}