#include <check.h>

#include "../s21_helpers.h"

START_TEST(parser) {
  counts v_and_f = {0};
  char *filename = "./obj/cube_test.obj";
  FILE *f;
  f = fopen(filename, "r");
  s21_counting(f, &v_and_f);
  fseek(f, 0, SEEK_SET);
  double *vert_arr = calloc(v_and_f.v_count * 3, sizeof(double));
  unsigned int *poly = calloc(2, sizeof(unsigned int));
  int j = 0;
  poly = s21_parsing_obj(f, vert_arr, poly, &j);
  fclose(f);
  s21_reduce(poly, j);
  ck_assert_float_eq_tol(vert_arr[0], -1, 1e-6);
  ck_assert_float_eq_tol(vert_arr[1], -1, 1e-6);
  ck_assert_float_eq_tol(vert_arr[2], -1, 1e-6);
  ck_assert_float_eq_tol(vert_arr[3], -1, 1e-6);
  ck_assert_float_eq_tol(vert_arr[4], -1, 1e-6);
  ck_assert_float_eq_tol(vert_arr[5], 1, 1e-6);
  ck_assert_float_eq_tol(vert_arr[6], -1, 1e-6);
  ck_assert_float_eq_tol(vert_arr[7], 1, 1e-6);
  ck_assert_float_eq_tol(vert_arr[8], -1, 1e-6);
  ck_assert_float_eq_tol(vert_arr[9], -1, 1e-6);
  ck_assert_float_eq_tol(vert_arr[10], 1, 1e-6);
  ck_assert_float_eq_tol(vert_arr[11], 1, 1e-6);
  ck_assert_float_eq_tol(vert_arr[12], 1, 1e-6);
  ck_assert_float_eq_tol(vert_arr[13], -1, 1e-6);
  ck_assert_float_eq_tol(vert_arr[14], -1, 1e-6);
  ck_assert_float_eq_tol(vert_arr[15], 1, 1e-6);
  ck_assert_float_eq_tol(vert_arr[16], -1, 1e-6);
  ck_assert_float_eq_tol(vert_arr[17], 1, 1e-6);
  ck_assert_float_eq_tol(vert_arr[18], 1, 1e-6);
  ck_assert_float_eq_tol(vert_arr[19], 1, 1e-6);
  ck_assert_float_eq_tol(vert_arr[20], -1, 1e-6);
  ck_assert_float_eq_tol(vert_arr[21], 1, 1e-6);
  ck_assert_float_eq_tol(vert_arr[22], 1, 1e-6);
  ck_assert_float_eq_tol(vert_arr[23], 1, 1e-6);
  free(vert_arr);
  free(poly);
}
END_TEST

START_TEST(scale) {
  counts v_and_f = {0};
  char *filename = "./obj/cube_test.obj";
  FILE *f;
  f = fopen(filename, "r");
  s21_counting(f, &v_and_f);
  fseek(f, 0, SEEK_SET);
  double *vert_arr = calloc(v_and_f.v_count * 3, sizeof(double));
  unsigned int *poly = calloc(2, sizeof(unsigned int));
  int j = 0;
  poly = s21_parsing_obj(f, vert_arr, poly, &j);
  fclose(f);
  double scale = 1.3;
  s21_scale(&v_and_f, vert_arr, scale);
  ck_assert_float_eq_tol(vert_arr[0], -1.3, 1e-6);
  ck_assert_float_eq_tol(vert_arr[1], -1.3, 1e-6);
  ck_assert_float_eq_tol(vert_arr[2], -1.3, 1e-6);
  ck_assert_float_eq_tol(vert_arr[3], -1.3, 1e-6);
  ck_assert_float_eq_tol(vert_arr[4], -1.3, 1e-6);
  ck_assert_float_eq_tol(vert_arr[5], 1.3, 1e-6);
  ck_assert_float_eq_tol(vert_arr[6], -1.3, 1e-6);
  ck_assert_float_eq_tol(vert_arr[7], 1.3, 1e-6);
  ck_assert_float_eq_tol(vert_arr[8], -1.3, 1e-6);
  ck_assert_float_eq_tol(vert_arr[9], -1.3, 1e-6);
  ck_assert_float_eq_tol(vert_arr[10], 1.3, 1e-6);
  ck_assert_float_eq_tol(vert_arr[11], 1.3, 1e-6);
  ck_assert_float_eq_tol(vert_arr[12], 1.3, 1e-6);
  ck_assert_float_eq_tol(vert_arr[13], -1.3, 1e-6);
  ck_assert_float_eq_tol(vert_arr[14], -1.3, 1e-6);
  ck_assert_float_eq_tol(vert_arr[15], 1.3, 1e-6);
  ck_assert_float_eq_tol(vert_arr[16], -1.3, 1e-6);
  ck_assert_float_eq_tol(vert_arr[17], 1.3, 1e-6);
  ck_assert_float_eq_tol(vert_arr[18], 1.3, 1e-6);
  ck_assert_float_eq_tol(vert_arr[19], 1.3, 1e-6);
  ck_assert_float_eq_tol(vert_arr[20], -1.3, 1e-6);
  ck_assert_float_eq_tol(vert_arr[21], 1.3, 1e-6);
  ck_assert_float_eq_tol(vert_arr[22], 1.3, 1e-6);
  ck_assert_float_eq_tol(vert_arr[23], 1.3, 1e-6);
  free(vert_arr);
  free(poly);
}

START_TEST(move) {
  counts v_and_f = {0};
  char *filename = "./obj/cube_test.obj";
  FILE *f;
  f = fopen(filename, "r");
  s21_counting(f, &v_and_f);
  fseek(f, 0, SEEK_SET);
  double *vert_arr = calloc(v_and_f.v_count * 3, sizeof(double));
  unsigned int *poly = calloc(2, sizeof(unsigned int));
  int j = 0;
  poly = s21_parsing_obj(f, vert_arr, poly, &j);
  fclose(f);
  int move = 5;
  s21_move_x(&v_and_f, vert_arr, move);
  s21_move_y(&v_and_f, vert_arr, move);
  s21_move_z(&v_and_f, vert_arr, move);
  ck_assert_float_eq_tol(vert_arr[0], 4, 1e-6);
  ck_assert_float_eq_tol(vert_arr[1], 4, 1e-6);
  ck_assert_float_eq_tol(vert_arr[2], 4, 1e-6);
  ck_assert_float_eq_tol(vert_arr[3], 4, 1e-6);
  ck_assert_float_eq_tol(vert_arr[4], 4, 1e-6);
  ck_assert_float_eq_tol(vert_arr[5], 6, 1e-6);
  ck_assert_float_eq_tol(vert_arr[6], 4, 1e-6);
  ck_assert_float_eq_tol(vert_arr[7], 6, 1e-6);
  ck_assert_float_eq_tol(vert_arr[8], 4, 1e-6);
  ck_assert_float_eq_tol(vert_arr[9], 4, 1e-6);
  ck_assert_float_eq_tol(vert_arr[10], 6, 1e-6);
  ck_assert_float_eq_tol(vert_arr[11], 6, 1e-6);
  ck_assert_float_eq_tol(vert_arr[12], 6, 1e-6);
  ck_assert_float_eq_tol(vert_arr[13], 4, 1e-6);
  ck_assert_float_eq_tol(vert_arr[14], 4, 1e-6);
  ck_assert_float_eq_tol(vert_arr[15], 6, 1e-6);
  ck_assert_float_eq_tol(vert_arr[16], 4, 1e-6);
  ck_assert_float_eq_tol(vert_arr[17], 6, 1e-6);
  ck_assert_float_eq_tol(vert_arr[18], 6, 1e-6);
  ck_assert_float_eq_tol(vert_arr[19], 6, 1e-6);
  ck_assert_float_eq_tol(vert_arr[20], 4, 1e-6);
  ck_assert_float_eq_tol(vert_arr[21], 6, 1e-6);
  ck_assert_float_eq_tol(vert_arr[22], 6, 1e-6);
  ck_assert_float_eq_tol(vert_arr[23], 6, 1e-6);
  free(vert_arr);
  free(poly);
}

START_TEST(rotate_x) {
  counts v_and_f = {0};
  char *filename = "./obj/cube_test.obj";
  FILE *f;
  f = fopen(filename, "r");
  s21_counting(f, &v_and_f);
  fseek(f, 0, SEEK_SET);
  double *vert_arr = calloc(v_and_f.v_count * 3, sizeof(double));
  unsigned int *poly = calloc(2, sizeof(unsigned int));
  int j = 0;
  poly = s21_parsing_obj(f, vert_arr, poly, &j);
  fclose(f);
  double *new_vert_arr = calloc(v_and_f.v_count * 3, sizeof(double));
  double rotate = 30;
  s21_rotate_x(&v_and_f, new_vert_arr, vert_arr, rotate);
  ck_assert_float_eq_tol(vert_arr[0], -1, 1e-6);
  ck_assert_float_eq_tol(new_vert_arr[1], -0.366025, 1e-6);
  ck_assert_float_eq_tol(new_vert_arr[2], -1.366025, 1e-6);
  ck_assert_float_eq_tol(vert_arr[3], -1, 1e-6);
  ck_assert_float_eq_tol(new_vert_arr[4], -1.366025, 1e-6);
  ck_assert_float_eq_tol(new_vert_arr[5], 0.366025, 1e-6);
  ck_assert_float_eq_tol(vert_arr[6], -1, 1e-6);
  ck_assert_float_eq_tol(new_vert_arr[7], 1.366025, 1e-6);
  ck_assert_float_eq_tol(new_vert_arr[8], -0.366025, 1e-6);
  ck_assert_float_eq_tol(vert_arr[9], -1, 1e-6);
  ck_assert_float_eq_tol(new_vert_arr[10], 0.366025, 1e-6);
  ck_assert_float_eq_tol(new_vert_arr[11], 1.366025, 1e-6);
  ck_assert_float_eq_tol(vert_arr[12], 1, 1e-6);
  ck_assert_float_eq_tol(new_vert_arr[13], -0.366025, 1e-6);
  ck_assert_float_eq_tol(new_vert_arr[14], -1.366025, 1e-6);
  ck_assert_float_eq_tol(vert_arr[15], 1, 1e-6);
  ck_assert_float_eq_tol(new_vert_arr[16], -1.366025, 1e-6);
  ck_assert_float_eq_tol(new_vert_arr[17], 0.366025, 1e-6);
  ck_assert_float_eq_tol(vert_arr[18], 1, 1e-6);
  ck_assert_float_eq_tol(new_vert_arr[19], 1.366025, 1e-6);
  ck_assert_float_eq_tol(new_vert_arr[20], -0.366025, 1e-6);
  ck_assert_float_eq_tol(vert_arr[21], 1, 1e-6);
  ck_assert_float_eq_tol(new_vert_arr[22], 0.366025, 1e-6);
  ck_assert_float_eq_tol(new_vert_arr[23], 1.366025, 1e-6);
  free(vert_arr);
  free(new_vert_arr);
  free(poly);
}

START_TEST(rotate_y) {
  counts v_and_f = {0};
  char *filename = "./obj/cube_test.obj";
  FILE *f;
  f = fopen(filename, "r");
  s21_counting(f, &v_and_f);
  fseek(f, 0, SEEK_SET);
  double *vert_arr = calloc(v_and_f.v_count * 3, sizeof(double));
  unsigned int *poly = calloc(2, sizeof(unsigned int));
  int j = 0;
  poly = s21_parsing_obj(f, vert_arr, poly, &j);
  fclose(f);
  double rotate = 30;
  s21_rotate_y(&v_and_f, vert_arr, rotate);
  ck_assert_float_eq_tol(vert_arr[0], -1.366025, 1e-6);
  ck_assert_float_eq_tol(vert_arr[1], -1, 1e-6);
  ck_assert_float_eq_tol(vert_arr[2], -0.366025, 1e-6);
  ck_assert_float_eq_tol(vert_arr[3], -0.366025, 1e-6);
  ck_assert_float_eq_tol(vert_arr[4], -1, 1e-6);
  ck_assert_float_eq_tol(vert_arr[5], 1.366025, 1e-6);
  ck_assert_float_eq_tol(vert_arr[6], -1.366025, 1e-6);
  ck_assert_float_eq_tol(vert_arr[7], 1, 1e-6);
  ck_assert_float_eq_tol(vert_arr[8], -0.366025, 1e-6);
  ck_assert_float_eq_tol(vert_arr[9], -0.366025, 1e-6);
  ck_assert_float_eq_tol(vert_arr[10], 1, 1e-6);
  ck_assert_float_eq_tol(vert_arr[11], 1.366025, 1e-6);
  ck_assert_float_eq_tol(vert_arr[12], 0.366025, 1e-6);
  ck_assert_float_eq_tol(vert_arr[13], -1, 1e-6);
  ck_assert_float_eq_tol(vert_arr[14], -1.366025, 1e-6);

  ck_assert_float_eq_tol(vert_arr[15], 1.366025, 1e-6);
  ck_assert_float_eq_tol(vert_arr[16], -1, 1e-6);
  ck_assert_float_eq_tol(vert_arr[17], 0.366025, 1e-6);

  ck_assert_float_eq_tol(vert_arr[18], 0.366025, 1e-6);
  ck_assert_float_eq_tol(vert_arr[19], 1, 1e-6);
  ck_assert_float_eq_tol(vert_arr[20], -1.366025, 1e-6);

  ck_assert_float_eq_tol(vert_arr[21], 1.366025, 1e-6);
  ck_assert_float_eq_tol(vert_arr[22], 1, 1e-6);
  ck_assert_float_eq_tol(vert_arr[23], 0.366025, 1e-6);
  free(vert_arr);
  free(poly);
}

START_TEST(rotate_z) {
  counts v_and_f = {0};
  char *filename = "./obj/cube_test.obj";
  FILE *f;
  f = fopen(filename, "r");
  s21_counting(f, &v_and_f);
  fseek(f, 0, SEEK_SET);
  double *vert_arr = calloc(v_and_f.v_count * 3, sizeof(double));
  unsigned int *poly = calloc(2, sizeof(unsigned int));
  int j = 0;
  poly = s21_parsing_obj(f, vert_arr, poly, &j);
  fclose(f);
  double rotate = 30;
  s21_rotate_z(&v_and_f, vert_arr, rotate);
  ck_assert_float_eq_tol(vert_arr[0], -1.366025, 1e-6);
  ck_assert_float_eq_tol(vert_arr[1], -0.366025, 1e-6);
  ck_assert_float_eq_tol(vert_arr[2], -1, 1e-6);
  ck_assert_float_eq_tol(vert_arr[3], -1.366025, 1e-6);
  ck_assert_float_eq_tol(vert_arr[4], -0.366025, 1e-6);
  ck_assert_float_eq_tol(vert_arr[5], 1, 1e-6);
  ck_assert_float_eq_tol(vert_arr[6], -0.366025, 1e-6);
  ck_assert_float_eq_tol(vert_arr[7], 1.366025, 1e-6);
  ck_assert_float_eq_tol(vert_arr[8], -1, 1e-6);
  ck_assert_float_eq_tol(vert_arr[9], -0.366025, 1e-6);
  ck_assert_float_eq_tol(vert_arr[10], 1.366025, 1e-6);
  ck_assert_float_eq_tol(vert_arr[11], 1, 1e-6);
  ck_assert_float_eq_tol(vert_arr[12], 0.366025, 1e-6);
  ck_assert_float_eq_tol(vert_arr[13], -1.366025, 1e-6);
  ck_assert_float_eq_tol(vert_arr[14], -1, 1e-6);
  ck_assert_float_eq_tol(vert_arr[15], 0.366025, 1e-6);
  ck_assert_float_eq_tol(vert_arr[16], -1.366025, 1e-6);
  ck_assert_float_eq_tol(vert_arr[17], 1, 1e-6);
  ck_assert_float_eq_tol(vert_arr[18], 1.366025, 1e-6);
  ck_assert_float_eq_tol(vert_arr[19], 0.366025, 1e-6);
  ck_assert_float_eq_tol(vert_arr[20], -1, 1e-6);
  ck_assert_float_eq_tol(vert_arr[21], 1.366025, 1e-6);
  ck_assert_float_eq_tol(vert_arr[22], 0.366025, 1e-6);
  ck_assert_float_eq_tol(vert_arr[23], 1, 1e-6);
  free(vert_arr);
  free(poly);
}

START_TEST(normal) {
  counts v_and_f = {0};
  char *filename = "./obj/cube_test.obj";
  FILE *f;
  f = fopen(filename, "r");
  s21_counting(f, &v_and_f);
  fseek(f, 0, SEEK_SET);
  double *vert_arr = calloc(v_and_f.v_count * 3, sizeof(double));
  unsigned int *poly = calloc(2, sizeof(unsigned int));
  int j = 0;
  poly = s21_parsing_obj(f, vert_arr, poly, &j);
  fclose(f);
  double min_x, max_x, min_y, max_y, min_z, max_z, camera_o;
  s21_normal(&v_and_f, vert_arr, &min_x, &max_x, &min_y, &max_y, &min_z, &max_z,
             &camera_o);
  min_x = -1;
  max_x = 1;
  min_y = -1;
  max_y = 1;
  min_z = -1;
  max_z = 1;
  camera_o = 1;
  free(vert_arr);
  free(poly);
}

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, parser);
  tcase_add_test(tc1_1, scale);
  tcase_add_test(tc1_1, move);
  tcase_add_test(tc1_1, rotate_x);
  tcase_add_test(tc1_1, rotate_y);
  tcase_add_test(tc1_1, rotate_z);
  tcase_add_test(tc1_1, normal);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_VERBOSE);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
