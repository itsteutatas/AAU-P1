#include "stdio.h"
#include "stdlib.h"
#include "main.h"

void input_parameters(double* temperature, double* salinity, double* secchi_depth){
    printf("Measure the temperature in degrees Celsius, input the value without unit and press enter\n");
    scanf("%lf", temperature);

    printf("Measure the secchi depth in centimeter, input the value without unit and press enter\n");
    scanf("%lf", secchi_depth);

    printf("Measure the salinity in ppt, input the value without unit and press enter\n");
    scanf("%lf", salinity);
}

void save_entry(FILE* f, double temperature, double salinity, double secchi_depth){
    fprintf(f, "%.1lf degrees Celsius | %.1lf ppt salinity | %.1lf centimeters\n", temperature, salinity, secchi_depth);
}

//Check which bracket temperature input falls into. Returns: Int corresponding with bracket
int temperature_bracket(int c) {
    if (c < 5) {
        return 1;
    } else if (c < 10) {
        return 2;
    } else if (c < 21) {
        return 3;
    } else if (c < 24) {
        return 4;
    } else if (c < 30){
        return 5;
    } else {
        return 6;
    }
}

//Check the maximum depth limit based on Secchi depth. Returns: Int max depth limit in centimeters, rounded up
int max_depth_limit(int sd) {
    return sd * 0.95;
}

void print_temperature_result(int t) {
    switch (t) {
        case 1:
            printf("The current temperature conditions are poor, as the water temperature is too low."
                   "Seagrass planted here is likely to survive, but its growth will be stunted.");
            break;
        case 2:
            printf("The current temperature conditions are fine, albeit slightly low."
                   "Seagrass planted here will survive, but not thrive.");
            break;
        case 3:
            printf("The current temperature conditions are optimal."
                   "Seagrass planted here will thrive.");
            break;
        case 4:
            printf("The current temperature conditions are fine, albeit slightly high."
                   "Seagrass planted here will survive, but not thrive.");
            break;
        case 5:
            printf("The current temperature conditions are poor, as the water temperature is too high."
                   "Seagrass planted here will not be able to reproduce.");
            break;
        case 6:
            printf("The current temperature conditions are severe, as the temperature is much too high."
                   "Seagrass planted here will likely not survive.");
    }
}

void print_secchi_result(int mdl) {
    printf("The water clarity in this area allows seagrass to be planted at a max depth of %d centimeters to survive.", mdl);
}
//Check which bracket salinity input falls into. Returns: Returns: Int corresponding with bracket

//Print statement for each parameter as a result
void print_result(int temperature, int secchi_depth) {
    int t = temperature_bracket(temperature);
    int mdl = max_depth_limit(secchi_depth);
    print_temperature_result(t);
    print_secchi_result(mdl);
}

int main(){
    double temperature, salinity, secchi_depth;
    printf("This program needs an input of temperature, secchi depth and nitrogen levels\n"
           "With this input it calculates whether the area is suitable for seagrass growth\n\n");

    input_parameters(&temperature, &salinity, &secchi_depth);

    print_result(temperature, secchi_depth);

    FILE *f = fopen("fil1.txt", "w");
    if (f == NULL)
    {
        printf("The file could not be opened.");
        exit(EXIT_FAILURE);
    }

    save_entry(f, temperature, salinity, secchi_depth);

}