#include "stdio.h"
#include "stdlib.h"
#include "main.h"
#include "driver.h"
#define MAX_STRING_LENGTH 20

//Used in main to choose whether more data entries should be made or the program should end. Returns 'y' for yes and 'n' for no.
char scan_selection() {
    char selection = ' ';
    printf("Would you like to make a data entry? (y/n): ");
    scanf(" %c", &selection);
    return selection;
}
//This function validates input parameters. Want to make a range - higher and lower limitis for input
//E.g. for temperature limits could be max low and high temperatures measured in Danish waters.
// Max low : -10, max high : 30
void check_input(double temperature, double salinity, double secchi_depth, char location[]){
    int count = 0;

    if(temperature <= -10|| temperature >= 30){
        printf("Your temperature input is invalid.\n");
        count = 1;
    }
    if(salinity < 0 || salinity > 50){
        printf("Your salinity input is invalid.\n");
        count = 1;
    }
    if(secchi_depth <= 0){
        printf("Your Secchi depth input is invalid.\n");
        count = 1;
    }

    if (count == 1) {
        input_parameters(temperature, salinity, secchi_depth, location);
    }
}

//This function prompts and scans for the three measured values of temperature, salinity and secchi depth.
void input_parameters(double temperature, double salinity, double secchi_depth, char location[]){

    printf("Measure the temperature in degrees Celsius, then input the value without unit and press enter: ");
    scanf("%lf", &temperature);

    printf("Measure the salinity in ppt, then input the value without unit and press enter: ");
    scanf("%lf", &salinity);

    printf("Measure the secchi depth in centimeter, then input the value without unit and press enter: ");
    scanf("%lf", &secchi_depth);

    printf("Enter the sea at which the measurements are taken: ");
    scanf("%s", location);

    check_input(temperature, salinity, secchi_depth, location);
}



//This function saves an entry of the three values into the opened file, f.
void save_entry(FILE* f, double temperature, double salinity, double secchi_depth, char location[]){
    fprintf(f, "%.1lf degrees Celsius | %.1lf ppt salinity | %.1lf centimeters | Location: %s\n", temperature, salinity, secchi_depth, location);
}

//This function checks which bracket the temperature input falls into. It returns an integer corresponding to the bracket
int calc_t_bracket(double c) {
    if (c < 5) {
        return 1; //Returns 1 for a bad result with stunted growth
    } else if (c < 10) {
        return 2; //Returns 2 for a fine result
    } else if (c < 21) {
        return 3; //Returns 3 for an optimal result
    } else if (c < 24) {
        return 4; //Returns 4 for a fine result
    } else if (c < 30){
        return 5; //Returns 5 for a bad result with stunted reproduction
    } else {
        return 6; //Returns 6 for a bad result with high mortality
    }
}

//Check which bracket salinity input falls into. Returns: Returns: Int corresponding with bracket
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
    else if( s < 36) {
        return 4; // Returns 4 for a fine result
    }
    else {
        return 5; // Returns 5 for a not good result
    }
}

//This function checks the maximum depth limit based on Secchi depth. The max depth limit determines how deep seagrass
//can be planted.
//It returns an integer of the max depth limit in centimeters, rounded down.
int calc_mdl(double sd) {
    return sd * 0.95;
}

//Takes a parameter of temperature bracket and prints a string that represents the temperature bracket.
void print_temperature_result(int t) {
    switch (t) {
        case 1:
            printf("he current water temperature is too low");
            break;
        case 2:
            printf("he current water temperature fine, albeit slightly low");
            break;
        case 3:
            printf("he current water temperature is optimal");
            break;
        case 4:
            printf("he current water temperature is fine, albeit slightly high");
            break;
        case 5:
            printf("he current water temperature is too high");
            break;
        case 6:
            printf("he current water temperature is much too high");
    }
}

//Takes a parameter of salinity bracket and prints a string that represents the salinity bracket.
void print_salinity_result(int salinity_bracket){
    switch (salinity_bracket) {
        case 1:
            printf("he current salinity level is too low");
            break;
        case 2:
            printf("he current salinity level is fine");
            break;
        case 3:
            printf("he current salinity level is optimal");
            break;
        case 4:
            printf("he current salinity level is fine");
            break;
        case 5:
            printf("he current salinity level is too high");
            break;
    }
}

//Takes parameter of max depth limit and prints the result as a string.
void print_secchi_result(int mdl) {
    printf("The water clarity in this area allows seagrass to be planted at a max depth of %d centimeters.\n\n", mdl);
}

//Encapsulates the previous functions; finds brackets for temperature and salinity, finds the max depth limit, and
//prints a combined result.
void print_full_result(double temperature, double salinity, double secchi_depth) {
    int t_bracket = calc_t_bracket(temperature);
    int s_bracket = calc_s_bracket(salinity);
    int mdl = calc_mdl(secchi_depth);

    //Four options:
    if(t_bracket == 1 || t_bracket > 4) { //1) Temperature is too extreme, print temperature first and salinity after
        printf("It is not recommended to plant seagrass in this area.\nT");
        print_temperature_result(t_bracket);
        printf(" (%d)", t_bracket);
        printf(", and t");
        print_salinity_result(s_bracket);
        printf(" (%d)", s_bracket);
        printf(".\n");
    } else if (s_bracket == 1 || s_bracket == 5) { //2) Salinity is too extreme, print salinity first and temperature after
        printf("It is not recommended to plant seagrass in this area.\nT");
        print_salinity_result(s_bracket);
        printf(" (%d)", t_bracket);
        printf(", and t");
        print_temperature_result(t_bracket);
        printf(" (%d)", s_bracket);
        printf(".\n");
    } else if (t_bracket == 2 || t_bracket == 4 || s_bracket == 2 || s_bracket == 4) { //3) None of the parameters are too extreme
        printf("The conditions for planting seagrass are good enough, but could be better.\nT");
        print_salinity_result(s_bracket);
        printf(" (%d)", s_bracket);
        printf(", and t");
        print_temperature_result(t_bracket);
        printf(" (%d)", t_bracket);
        printf(".\n");
        print_secchi_result(mdl);
        printf(" (%d)", mdl);
    } else { //Optimal conditions for both temperature and salinity
        printf("This area is recommended for planting seagrass.\nT");
        print_temperature_result(t_bracket);
        // printf(" (%d)", t_bracket);
        printf(", and t");
        print_salinity_result(s_bracket);
        // printf(" (%d)", s_bracket);
        printf(".\n");
        print_secchi_result(mdl);
    }
}

int main(){
    char selection;
    char location[MAX_STRING_LENGTH];
    double temperature = 0, salinity = 0, secchi_depth = 0;

    //Initial prompt
    printf("This program needs an input of temperature, Secchi depth and salinity.\n"
           "With this input, it calculates whether the area is suitable for planting seagrass.\n\n");

    //Program loop, uses scan_selection() to determine whether program should run or exit
    while(1) {
        selection = scan_selection();
        if (selection == 'y' || selection == 'Y') {
            //Open file "file1.txt" in writing mode
            FILE *f = fopen("file1.txt", "a"); // "a" appends to a file. Writing operations, append data at the end of the file. The file is created if it does not exist.
            if (f == NULL) {
                printf("The file could not be accessed.");
                exit(EXIT_FAILURE);
            }

            //Takes user input, prints the result, and saves the entry in the textfile
            input_parameters(temperature, salinity, secchi_depth, location);
            print_full_result(temperature, salinity, secchi_depth);
            save_entry(f, temperature, salinity, secchi_depth, location);
            fclose(f);
        }
        else if (selection == 'n' || selection == 'N') {
            //Closes file and exits program
            exit(EXIT_SUCCESS);
        }
        else {
            printf("Input not valid. Please write y or n\n");
        }
    }
}