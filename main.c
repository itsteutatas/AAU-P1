//
// Created by xande on 06/11/2023.
//
#include "stdio.h"
#include "stdlib.h"
#include "main.h"

void input_parameters(double* temperature, double* level_of_nitrogen, double* secchi_depth){
    printf("Measure the temperature in degrees Celsius, input the value without unit and press enter\n");
    scanf("%lf", temperature);

    printf("Measure the secchi depth in centimeter, input the value without unit and press enter\n");
    scanf("%lf", secchi_depth);

    printf("Measure the levels of nitrogen in micrograms per liter, input the value without unit and press enter\n");
    scanf("%lf", level_of_nitrogen);
}

void print_txt(FILE* f, double temperature, double level_of_nitrogen, double secchi_depth){
    fprintf(f, "%.1lf degrees Celsius | %.1lf micrograms per Liter | %.1lf centimeters\n", temperature, level_of_nitrogen, secchi_depth);
}


int main(){
    double temperature, level_of_nitrogen, secchi_depth;
    printf("This program needs an input of temperature, secchi depth and nitrogen levels\n"
           "With this input it calculates whether the area is suitable for seagrass growth\n\n");

    input_parameters(&temperature, &level_of_nitrogen, &secchi_depth);

    FILE *f = fopen("fil1.txt", "w");
    if (f == NULL)
    {
        printf("filen blev ikke åbnet");
        exit(EXIT_FAILURE);
    }

    print_txt(f, temperature, level_of_nitrogen, secchi_depth);

}