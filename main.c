// Created by Hella Arman, november 2023
#include "main.h"

#define MAX_TEMP 20
#define MAX_N 30
#define MAX_DEPTH 40

#define MIN_TEMP 10
#define MIN_N 20
#define MIn_DEPTH 30

int main(void){

    return 0;
}

int if_value_higher(int actual_value, int limit_value) {
   if(actual_value < limit_value){
       return 0;
   }
   else{
       return 1; //hvis den er højere, så returnerer den 1
   }
}

int if_value_below(int actual_value, int limit_value){
    if(actual_value > limit_value)
        return 0;
    }
    else {
        return 1; //hvis temperaturen er laverer, så returnerer den 1
}

int comparator(int temp, int N, int depth){
       //Temperatur
        if(if_value_higher(temp,MAX_TEMP) == 1){
            return 0; //hvis temperaturen er højere, så returnerer den 0
        }
        else (if_value_below(temp,MIN_TEMP) == 0){
            return 1;
        }
    }

