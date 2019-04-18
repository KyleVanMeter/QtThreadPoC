#include "appmain.h"
#include <QDialogButtonBox>
#include <QPushButton>
#include <QGridLayout>
#include <QGuiApplication>
#include <QGraphicsView>
#include <QDebug>

AppMain::AppMain(QWidget *parent) {
  resize(400, 150);

  auto button_box = new QDialogButtonBox;
  _start_btn = new QPushButton(tr("Start"));
  _stop_btn = new QPushButton(tr("Stop"));
  button_box->addButton(_start_btn, QDialogButtonBox::ActionRole);
  button_box->addButton(_stop_btn, QDialogButtonBox::RejectRole);

  connect(_start_btn, &QAbstractButton::clicked, this, &AppMain::onHandleStart);
  connect(_stop_btn, &QAbstractButton::clicked, this, &AppMain::onHandleStop);

  connect(&_controller, &Controller::passData, this, &AppMain::onDataGet);
  QGridLayout *main_layout = nullptr;
  _view = new QGraphicsView();

  main_layout = new QGridLayout(this);
  main_layout->addWidget(button_box, 1, 0, 1, 2);
  main_layout->addWidget(_view, 2, 0, 50, 50);

  setWindowTitle(QGuiApplication::applicationDisplayName());
}

void AppMain::onHandleStart() {
  _controller.start();
}

void AppMain::onHandleStop() {
  _controller.stop();
}

void AppMain::onDataGet(const QColor &newColor) {
  qDebug() << newColor;
  QPixmap colors(_view->viewport()->width(),_view->viewport()->height());
  colors.fill(newColor);
  _scene = new QGraphicsScene;
  _scene->addPixmap(colors);
  _view->setScene(_scene);
  repaint();
}
