#include "s21_helpers.h"

void s21_lexems(char *str, char **lexems) {
  int lexcount = 0;
  char *del = strtok(str, " ");
  while (del != NULL) {
    lexems[lexcount++] = del;
    del = strtok(NULL, " ");
  }
}

void s21_counting(FILE *f, counts *v_and_f) {
  char c = 'c', temp = 't';
  while (c != EOF) {
    c = fgetc(f);
    if (temp == 'v' && c == ' ') v_and_f->v_count += 1;
    if (temp == 'f' && c == ' ') v_and_f->f_count += 1;
    temp = c;
  }
}

unsigned int *s21_parsing_obj(FILE *f, double *vert_arr, unsigned int *poly,
                              int *j) {
  int count = 0;
  int mem = 2;
  char c = 'c', temp = 't';
  unsigned int r = 0;
  char *line = NULL;
  size_t len = 0;
  while (c != EOF) {
    c = fgetc(f);
    if (temp == 'v' && c == ' ') {
      fscanf(f, "%lf %lf %lf", &vert_arr[r], &vert_arr[r + 1],
             &vert_arr[r + 2]);
      r += 3;
    }
    if (temp == 'f' && c == ' ') {
      getline(&line, &len, f);
      char *orig[1024] = {0};
      s21_lexems(line, orig);
      char *res[1024] = {0};

      for (int i = 0; orig[i]; i++) {
        if (s21_isnum(orig[i])) {
          res[i] = strtok(orig[i], "/");
        } else {
          continue;
        }
      }

      for (int i = 0; res[i]; mem += 2) {
        poly = realloc(poly, (mem) * sizeof(unsigned int));
        if (poly) {
          if (!i) {
            poly[count++] = (unsigned int)atof(res[i++]);
            poly[count++] = (unsigned int)atof(res[i]);
          } else if (!res[i + 1]) {
            poly[count++] = (unsigned int)atof(res[i++]);
            poly[count++] = (unsigned int)atof(res[0]);
          } else {
            poly[count++] = (unsigned int)atof(res[i]);
            poly[count++] = (unsigned int)atof(res[++i]);
          }
        } else {
          printf("Memory Error!");
          exit(1);
        }
      }
    }
    temp = c;
  }

  *j = count;
  if (line) free(line);

  return poly;
}

void s21_reduce(unsigned int *str, int j) {
  for (int i = 0; i < j; i++) {
    str[i] -= 1;
  }
}

int s21_isnum(char *number) {
  int code = 1;
  if (*number < '0' || *number > '9') {
    code = 0;
    // break;
  }
  return code;
}

void s21_scale(counts *v_and_f, double *new_vert_arr, double scale) {
  for (unsigned i = 0; i < v_and_f->v_count * 3; i++) {
    new_vert_arr[i] *= scale;
  }
}

void s21_move_x(counts *v_and_f, double *new_vert_arr, int move) {
  for (unsigned i = 0; i < v_and_f->v_count * 3; i += 3) {
    new_vert_arr[i] += move;
  }
}

void s21_move_y(counts *v_and_f, double *new_vert_arr, int move) {
  for (unsigned i = 1; i < v_and_f->v_count * 3; i += 3) {
    new_vert_arr[i] += move;
  }
}

void s21_move_z(counts *v_and_f, double *new_vert_arr, int move) {
  for (unsigned i = 2; i < v_and_f->v_count * 3; i += 3) {
    new_vert_arr[i] += move;
  }
}

void s21_rotate_x(counts *v_and_f, double *new_vert_arr, double *vert_arr,
                  double rotate) {
  rotate = rotate * (M_PI / 180);
  double temp_y, temp_z;
  for (unsigned i = 0; i < v_and_f->v_count * 3; i += 3) {
    temp_y = vert_arr[i + 1];
    temp_z = vert_arr[i + 2];
    new_vert_arr[i + 1] = temp_y * cos(rotate) - temp_z * sin(rotate);
    new_vert_arr[i + 2] = temp_y * sin(rotate) + temp_z * cos(rotate);
  }
}

void s21_rotate_y(counts *v_and_f, double *new_vert_arr, double rotate) {
  rotate = rotate * (M_PI / 180);
  double temp_x, temp_z;
  for (unsigned i = 0; i < v_and_f->v_count * 3; i += 3) {
    temp_x = new_vert_arr[i];
    temp_z = new_vert_arr[i + 2];
    new_vert_arr[i] = temp_x * cos(rotate) + temp_z * sin(rotate);
    new_vert_arr[i + 2] = -temp_x * sin(rotate) + temp_z * cos(rotate);
  }
}

void s21_rotate_z(counts *v_and_f, double *new_vert_arr, double rotate) {
  rotate = rotate * (M_PI / 180);
  double temp_x, temp_y;
  for (unsigned i = 0; i < v_and_f->v_count * 3; i += 3) {
    temp_x = new_vert_arr[i];
    temp_y = new_vert_arr[i + 1];
    new_vert_arr[i] = temp_x * cos(rotate) + temp_y * sin(rotate);
    new_vert_arr[i + 1] = -temp_x * sin(rotate) + temp_y * cos(rotate);
  }
}

void s21_normal(counts *v_and_f, double *new_vert_arr, double *min_x,
                double *max_x, double *min_y, double *max_y, double *min_z,
                double *max_z, double *camera_o) {
  *min_x = *max_x = new_vert_arr[0];
  *min_y = *max_y = new_vert_arr[1];
  *min_z = *max_z = new_vert_arr[2];
  for (unsigned i = 0, j = 1, k = 2; i < v_and_f->v_count * 3;
       i += 3, j += 3, k += 3) {
    if (new_vert_arr[i] < *min_x) *min_x = new_vert_arr[i];
    if (new_vert_arr[i] > *max_x) *max_x = new_vert_arr[i];
    if (new_vert_arr[j] < *min_y) *min_y = new_vert_arr[j];
    if (new_vert_arr[j] > *max_y) *max_y = new_vert_arr[j];
    if (new_vert_arr[k] < *min_z) *min_z = new_vert_arr[k];
    if (new_vert_arr[k] > *max_z) *max_z = new_vert_arr[k];
  }
  double new_camera = *max_x;
  if (*max_y >= fabs(*min_y) && *max_y > new_camera) new_camera = *max_y;
  if (*max_z >= fabs(*min_z) && *max_z > new_camera) new_camera = *max_z;
  if (fabs(*min_x) > *max_x && fabs(*min_x) > new_camera)
    new_camera = fabs(*min_x);
  if (fabs(*min_y) > *max_y && fabs(*min_y) > new_camera)
    new_camera = fabs(*min_y);
  if (fabs(*min_z) > *max_z && fabs(*min_z) > new_camera)
    new_camera = fabs(*min_z);
  *camera_o = new_camera;
}
