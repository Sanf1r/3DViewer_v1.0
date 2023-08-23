#ifndef S21_HELPERS_H
#define S21_HELPERS_H

#define _GNU_SOURCE
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data {
  unsigned int v_count;
  unsigned int f_count;
} counts;

void s21_lexems(char *str, char **lexems);
void s21_counting(FILE *f, counts *v_and_f);
unsigned int *s21_parsing_obj(FILE *f, double *vert_arr, unsigned int *poly,
                              int *j);
void s21_reduce(unsigned int *str, int j);
int s21_isnum(char *number);
void s21_scale(counts *v_and_f, double *new_vert_arr, double scale);
void s21_move_x(counts *v_and_f, double *new_vert_arr, int move);
void s21_move_y(counts *v_and_f, double *new_vert_arr, int move);
void s21_move_z(counts *v_and_f, double *new_vert_arr, int move);
void s21_rotate_x(counts *v_and_f, double *new_vert_arr, double *vert_arr,
                  double rotate);
void s21_rotate_y(counts *v_and_f, double *new_vert_arr, double rotate);
void s21_rotate_z(counts *v_and_f, double *new_vert_arr, double rotate);
void s21_normal(counts *v_and_f, double *new_vert_arr, double *min_x,
                double *max_x, double *min_y, double *max_y, double *min_z,
                double *max_z, double *camera_o);

#endif  // S21_HELPERS_H
