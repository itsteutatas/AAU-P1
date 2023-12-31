//
// Created by Kevin on 07-12-2023.
//

#ifndef AAU_P1_DRIVER_H
#define AAU_P1_DRIVER_H

#endif //AAU_P1_DRIVER_H

char scan_selection();
void check_parameter_input(double temperature, double salinity, double *secchi_depth, char location[]);
int check_location_input(char location[]);
void input_location(char location[]);
void input_parameters(double *temperature, double *salinity, double *secchi_depth, char location[]);
void save_entry(FILE* f, double temperature, double salinity, double secchi_depth, char location[]);
int calc_t_bracket(double c);
int calc_s_bracket(double s);
int calc_mdl(double sd);
void print_temperature_result(int t);
void print_salinity_result(int salinity_bracket);
void print_secchi_result(int mdl);
void print_full_result(double temperature, double salinity, double secchi_depth);