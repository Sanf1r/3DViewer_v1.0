#ifndef GLVIEW_H
#define GLVIEW_H

#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>

#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QSettings>
#include <QTimer>
#include <QWidget>
#include <algorithm>
#include <iostream>

extern "C" {
#include "s21_helpers.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class glView;
}
QT_END_NAMESPACE

class glView : public QOpenGLWidget {
  Q_OBJECT
 private:
  void drawCube();
  void parse();
  void rotate();
  void scale();
  void move();
  void saveSettings();
  void loadSettings();
  //    void mousePressEvent(QMouseEvent*) override;
  //    void mouseMoveEvent(QMouseEvent*) override;
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  Ui::glView *ui;
  QSettings *settings;

 public:
  glView(QWidget *parent = nullptr);
  ~glView();
  counts v_and_f = {0};
  FILE *f;
  int j = 0;
  //    float xRot = 0, yRot= 0;
  //    float x_pos = 0, y_pos = 0;
  //    QPoint mPos;
  unsigned int *poly = nullptr;
  double *vert_arr = nullptr;
  double *new_vert_arr = nullptr;
  char *filename = nullptr;
  float vert_r, back_r, lines_r;
  float vert_g, back_g, lines_g;
  float vert_b, back_b, lines_b;
  unsigned int edges_count = 0;
  double scale_value = 1;
  double min_x = 0, max_x = 0, min_y = 0, max_y = 0, min_z = 0, max_z = 0;
  double camera_o;

 private slots:
  void OpenFile();
  void back_color_slider(int value);
  void vert_color_slider(int value);
  void lines_color_slider(int value);
  void reset();
  void save_image();
  void start_draw();
  void init();
};
#endif  // GLVIEW_H
