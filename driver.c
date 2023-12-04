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

//Check the maximum depth limit based on Secchi depth. Returns: Int max depth limit in centimeters, rounded up

//Check which bracket salinity input falls into. Returns: Returns: Int corresponding with bracket
int salinity_bracket(int s){
    if(s < 5){
        return 1; // Returns 1 for a bad result with high mortality
    }
    else if(s < 9){
        return 2; // Returns 2 for a OK Result
    }
    else if(s < 26){
        return 3; // Returns 3 for a optimal result
    }
    else if( s < 36){
        return 4; // Returns 4 for a fine result
    }
    else{
        return 5; // Returns 5 for a not good result
    }
}

//Print result for salinity
void print__salinity_result(int salinity_bracket){
    switch (salinity_bracket) {
        case 1:
            printf("The current salinity level is to low and\n");
            break;
        case 2:
            printf("The current salinity level is OK\n");
            break;
        case 3:
            printf("The current salinity level is optimal\n")
            break;
        case 4:
            printf("The current sainity level is fine\n")
            break;
        case 5:
            printf("The current salinity level i to high\n")
            break;
    }
}

int main(){
    double temperature, level_of_nitrogen, secchi_depth;
    printf("This program needs an input of temperature, secchi depth and nitrogen levels\n"
           "With this input it calculates whether the area is suitable for seagrass growth\n\n");

    input_parameters(&temperature, &level_of_nitrogen, &secchi_depth);

    FILE *f = fopen("fil1.txt", "w");
    if (f == NULL)
    {
        printf("The file could not be opened.");
        exit(EXIT_FAILURE);
    }

    print_txt(f, temperature, level_of_nitrogen, secchi_depth);

}