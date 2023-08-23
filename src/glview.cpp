#include "glview.h"

#include "./ui_glview.h"

glView::glView(QWidget *parent) : QOpenGLWidget(parent), ui(new Ui::glView) {
  setFixedSize(1200, 1200);
  ui->setupUi(this);
  connect(ui->OpenFile, SIGNAL(clicked()), this, SLOT(OpenFile()));
  connect(ui->ResetButton, SIGNAL(clicked()), this, SLOT(reset()));
  connect(ui->save_image, SIGNAL(clicked()), this, SLOT(save_image()));
  connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this,
          SLOT(back_color_slider(int)));
  connect(ui->horizontalSlider_2, SIGNAL(valueChanged(int)), this,
          SLOT(back_color_slider(int)));
  connect(ui->horizontalSlider_3, SIGNAL(valueChanged(int)), this,
          SLOT(back_color_slider(int)));
  connect(ui->horizontalSlider_4, SIGNAL(valueChanged(int)), this,
          SLOT(vert_color_slider(int)));
  connect(ui->horizontalSlider_5, SIGNAL(valueChanged(int)), this,
          SLOT(vert_color_slider(int)));
  connect(ui->horizontalSlider_6, SIGNAL(valueChanged(int)), this,
          SLOT(vert_color_slider(int)));
  connect(ui->horizontalSlider_7, SIGNAL(valueChanged(int)), this,
          SLOT(lines_color_slider(int)));
  connect(ui->horizontalSlider_8, SIGNAL(valueChanged(int)), this,
          SLOT(lines_color_slider(int)));
  connect(ui->horizontalSlider_9, SIGNAL(valueChanged(int)), this,
          SLOT(lines_color_slider(int)));
  connect(ui->horizontalSlider_10, SIGNAL(valueChanged(int)), this,
          SLOT(start_draw()));
  connect(ui->horizontalSlider_11, SIGNAL(valueChanged(int)), this,
          SLOT(start_draw()));
  connect(ui->horizontalSlider_12, SIGNAL(valueChanged(int)), this,
          SLOT(start_draw()));
  connect(ui->horizontalSlider_13, SIGNAL(valueChanged(int)), this,
          SLOT(start_draw()));
  connect(ui->horizontalSlider_14, SIGNAL(valueChanged(int)), this,
          SLOT(start_draw()));
  connect(ui->horizontalSlider_15, SIGNAL(valueChanged(int)), this,
          SLOT(start_draw()));
  connect(ui->spinBox_6, SIGNAL(valueChanged(int)), this, SLOT(start_draw()));
  connect(ui->lines_style, SIGNAL(currentIndexChanged(int)), this,
          SLOT(start_draw()));
  connect(ui->vert_style, SIGNAL(currentIndexChanged(int)), this,
          SLOT(start_draw()));
  connect(ui->proj_type, SIGNAL(currentIndexChanged(int)), this,
          SLOT(start_draw()));
  connect(ui->spinBox_4, SIGNAL(valueChanged(int)), this, SLOT(start_draw()));
  connect(ui->spinBox_5, SIGNAL(valueChanged(int)), this, SLOT(start_draw()));
  settings = new QSettings("./settings.ini", QSettings::IniFormat, this);
  loadSettings();
  init();
}

glView::~glView() {
  saveSettings();
  delete[] vert_arr;
  delete[] new_vert_arr;
  delete[] poly;
  delete settings;
  delete ui;
}

void glView::initializeGL() { glEnable(GL_DEPTH_TEST); }

void glView::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
}

void glView::paintGL() {
  glClearColor(back_r, back_g, back_b, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  if (ui->proj_type->currentIndex() == 0) {
    glOrtho(-camera_o * 2, camera_o * 2, -camera_o * 2, camera_o * 2,
            -camera_o * 100, camera_o * 100);
  } else {
    gluPerspective(90.0, 1.0, 0.1, 1000000);
    glTranslated(0, 0, -camera_o * 2);
  }
  //    glRotatef(xRot, 1 ,0 ,0);
  //    glRotatef(yRot, 0, 1, 0);
  rotate();
  move();
  scale();
  drawCube();
}

void glView::start_draw() { update(); }

void glView::init() {
  back_r = ui->horizontalSlider->value() / 100.0;
  back_g = ui->horizontalSlider_2->value() / 100.0;
  back_b = ui->horizontalSlider_3->value() / 100.0;
  lines_r = ui->horizontalSlider_7->value() / 100.0;
  lines_g = ui->horizontalSlider_8->value() / 100.0;
  lines_b = ui->horizontalSlider_9->value() / 100.0;
  vert_r = ui->horizontalSlider_4->value() / 100.0;
  vert_g = ui->horizontalSlider_5->value() / 100.0;
  vert_b = ui->horizontalSlider_6->value() / 100.0;
  ui->color_r->setText(QString::number(back_r));
  ui->color_g->setText(QString::number(back_g));
  ui->color_b->setText(QString::number(back_b));
  ui->color_r_3->setText(QString::number(lines_r));
  ui->color_g_3->setText(QString::number(lines_g));
  ui->color_b_3->setText(QString::number(lines_b));
  ui->color_r_2->setText(QString::number(vert_r));
  ui->color_g_2->setText(QString::number(vert_g));
  ui->color_b_2->setText(QString::number(vert_b));
}

void glView::drawCube() {
  glVertexPointer(3, GL_DOUBLE, 0, new_vert_arr);
  glEnableClientState(GL_VERTEX_ARRAY);
  glColor3d(vert_r, vert_g, vert_b);
  glPointSize(ui->spinBox_5->value());
  if (ui->vert_style->currentIndex() == 0) {
    ui->label_9->show();
    ui->spinBox_5->show();
    glDrawArrays(GL_POINTS, 0, v_and_f.v_count);
  } else if (ui->vert_style->currentIndex() == 1) {
    ui->label_9->show();
    ui->spinBox_5->show();
    glEnable(GL_POINT_SMOOTH);
    glDrawArrays(GL_POINTS, 0, v_and_f.v_count);
    glDisable(GL_POINT_SMOOTH);
  } else {
    ui->label_9->hide();
    ui->spinBox_5->hide();
  }
  glColor3d(lines_r, lines_g, lines_b);
  glLineWidth(ui->spinBox_4->value());
  if (ui->lines_style->currentIndex() == 1) {
    glLineStipple(1, 0x00FF);
    glEnable(GL_LINE_STIPPLE);
    glDrawElements(GL_LINES, j, GL_UNSIGNED_INT, poly);
    glDisable(GL_LINE_STIPPLE);
  } else {
    glDrawElements(GL_LINES, j, GL_UNSIGNED_INT, poly);
  }
  glDisableClientState(GL_VERTEX_ARRAY);
  std::copy(vert_arr, vert_arr + v_and_f.v_count * 3, new_vert_arr);
}

void glView::parse() {
  v_and_f = {0};
  delete[] vert_arr;
  delete[] poly;
  f = fopen(filename, "r");
  s21_counting(f, &v_and_f);
  vert_arr = new double[v_and_f.v_count * 3];
  poly = new unsigned int[2];
  fseek(f, 0, SEEK_SET);
  poly = s21_parsing_obj(f, vert_arr, poly, &j);
  fclose(f);
  s21_reduce(poly, j);
  edges_count = j / 2;
  new_vert_arr = new double[v_and_f.v_count * 3];
  std::copy(vert_arr, vert_arr + v_and_f.v_count * 3, new_vert_arr);
}

// mouse movement
// void glView::mousePressEvent(QMouseEvent* mo) {
//    mPos = mo->pos();
//}

// void glView::mouseMoveEvent(QMouseEvent* mo) {
//     xRot = 1 / M_PI*(mo->pos().y() - mPos.y());
//     yRot = 1 / M_PI*(mo->pos().x() - mPos.x());
//     update();
// }

void glView::OpenFile() {
  QString filter = " OBJ Files (*.obj)";
  QString file_name = QFileDialog::getOpenFileName(this, "Open OBJ file",
                                                   QDir::homePath(), filter);
  if (!file_name.isEmpty() && !file_name.isNull()) {
    QString name = file_name.mid(file_name.lastIndexOf('/') + 1);
    QByteArray array = file_name.toLocal8Bit();
    filename = array.data();
    parse();
    s21_normal(&v_and_f, new_vert_arr, &min_x, &max_x, &min_y, &max_y, &min_z,
               &max_z, &camera_o);
    ui->name->setText(name);
    ui->vertices->setText(QString::number(v_and_f.v_count));
    ui->edges->setText(QString::number(edges_count));
    ui->path->setText(file_name);
  }
}

void glView::reset() {
  ui->horizontalSlider_10->setValue(0);
  ui->horizontalSlider_11->setValue(0);
  ui->horizontalSlider_12->setValue(0);
  ui->horizontalSlider_13->setValue(0);
  ui->horizontalSlider_14->setValue(0);
  ui->horizontalSlider_15->setValue(0);
  ui->spinBox_6->setValue(100);
  ui->horizontalSlider->setValue(0);
  ui->horizontalSlider_2->setValue(0);
  ui->horizontalSlider_3->setValue(0);
  ui->lines_style->setCurrentIndex(0);
  ui->spinBox_4->setValue(1);
  ui->horizontalSlider_7->setValue(100);
  ui->horizontalSlider_8->setValue(0);
  ui->horizontalSlider_9->setValue(0);
  ui->vert_style->setCurrentIndex(0);
  ui->spinBox_5->setValue(2);
  ui->horizontalSlider_4->setValue(0);
  ui->horizontalSlider_5->setValue(0);
  ui->horizontalSlider_6->setValue(100);
  update();
}

void glView::back_color_slider(int value) {
  back_r = ui->horizontalSlider->value() / 100.0;
  back_g = ui->horizontalSlider_2->value() / 100.0;
  back_b = ui->horizontalSlider_3->value() / 100.0;
  ui->color_r->setText(QString::number(back_r));
  ui->color_g->setText(QString::number(back_g));
  ui->color_b->setText(QString::number(back_b));
  update();
}

void glView::vert_color_slider(int value) {
  vert_r = ui->horizontalSlider_4->value() / 100.0;
  vert_g = ui->horizontalSlider_5->value() / 100.0;
  vert_b = ui->horizontalSlider_6->value() / 100.0;
  ui->color_r_2->setText(QString::number(vert_r));
  ui->color_g_2->setText(QString::number(vert_g));
  ui->color_b_2->setText(QString::number(vert_b));
  update();
}

void glView::lines_color_slider(int value) {
  lines_r = ui->horizontalSlider_7->value() / 100.0;
  lines_g = ui->horizontalSlider_8->value() / 100.0;
  lines_b = ui->horizontalSlider_9->value() / 100.0;
  ui->color_r_3->setText(QString::number(lines_r));
  ui->color_g_3->setText(QString::number(lines_g));
  ui->color_b_3->setText(QString::number(lines_b));
  update();
}

void glView::scale() {
  scale_value = ui->spinBox_6->value() / 100.0;
  s21_scale(&v_and_f, new_vert_arr, scale_value);
}

void glView::move() {
  s21_move_x(&v_and_f, new_vert_arr, ui->horizontalSlider_10->value());
  s21_move_y(&v_and_f, new_vert_arr, ui->horizontalSlider_11->value());
  s21_move_z(&v_and_f, new_vert_arr, ui->horizontalSlider_12->value());
}

void glView::rotate() {
  s21_rotate_x(&v_and_f, new_vert_arr, vert_arr,
               ui->horizontalSlider_13->value());
  s21_rotate_y(&v_and_f, new_vert_arr, ui->horizontalSlider_14->value());
  s21_rotate_z(&v_and_f, new_vert_arr, ui->horizontalSlider_15->value());
}

void glView::save_image() {
  QString str = QFileDialog::getSaveFileName(this, NULL, NULL,
                                             "BMP (*.bmp) ;; JPEG (*.jpeg)");
  if (!str.isEmpty()) {
    this->grabFramebuffer().save(str);
  }
}

void glView::saveSettings() {
  settings->setValue("scale", ui->spinBox_6->value());
  settings->setValue("rotate_x", ui->horizontalSlider_13->value());
  settings->setValue("rotate_y", ui->horizontalSlider_14->value());
  settings->setValue("rotate_z", ui->horizontalSlider_15->value());
  settings->setValue("move_x", ui->horizontalSlider_10->value());
  settings->setValue("move_y", ui->horizontalSlider_11->value());
  settings->setValue("move_z", ui->horizontalSlider_12->value());
  settings->setValue("background_r", ui->horizontalSlider->value());
  settings->setValue("background_g", ui->horizontalSlider_2->value());
  settings->setValue("background_b", ui->horizontalSlider_3->value());
  settings->setValue("lines_style", ui->lines_style->currentIndex());
  settings->setValue("lines_thick", ui->spinBox_4->value());
  settings->setValue("lines_r", ui->horizontalSlider_7->value());
  settings->setValue("lines_g", ui->horizontalSlider_8->value());
  settings->setValue("lines_b", ui->horizontalSlider_9->value());
  settings->setValue("vertices_style", ui->vert_style->currentIndex());
  settings->setValue("vertices_size", ui->spinBox_5->value());
  settings->setValue("vertices_r", ui->horizontalSlider_4->value());
  settings->setValue("vertices_g", ui->horizontalSlider_5->value());
  settings->setValue("vertices_b", ui->horizontalSlider_6->value());
}

void glView::loadSettings() {
  ui->spinBox_6->setValue(settings->value("scale", "100").toInt());
  ui->horizontalSlider_13->setValue(settings->value("rotate_x", "0").toInt());
  ui->horizontalSlider_14->setValue(settings->value("rotate_y", "0").toInt());
  ui->horizontalSlider_15->setValue(settings->value("rotate_z", "0").toInt());
  ui->horizontalSlider_10->setValue(settings->value("move_x", "0").toInt());
  ui->horizontalSlider_11->setValue(settings->value("move_y", "0").toInt());
  ui->horizontalSlider_12->setValue(settings->value("move_z", "0").toInt());
  ui->horizontalSlider->setValue(settings->value("background_r", "0").toInt());
  ui->horizontalSlider_2->setValue(
      settings->value("background_g", "0").toInt());
  ui->horizontalSlider_3->setValue(
      settings->value("background_b", "0").toInt());
  ui->lines_style->setCurrentIndex(settings->value("lines_style", "0").toInt());
  ui->spinBox_4->setValue(settings->value("lines_thick", "1").toInt());
  ui->horizontalSlider_7->setValue(settings->value("lines_r", "100").toInt());
  ui->horizontalSlider_8->setValue(settings->value("lines_g", "0").toInt());
  ui->horizontalSlider_9->setValue(settings->value("lines_b", "0").toInt());
  ui->vert_style->setCurrentIndex(
      settings->value("vertices_style", "0").toInt());
  ui->spinBox_5->setValue(settings->value("vertices_size", "2").toInt());
  ui->horizontalSlider_4->setValue(settings->value("vertices_r", "0").toInt());
  ui->horizontalSlider_5->setValue(settings->value("vertices_g", "0").toInt());
  ui->horizontalSlider_6->setValue(
      settings->value("vertices_b", "100").toInt());
}
