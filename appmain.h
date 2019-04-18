#ifndef APPMAIN_H
#define APPMAIN_H

#include <QDialog>
#include <QObject>
#include <QGraphicsView>

#include "controller.h"

class AppMain : public QDialog
{
  Q_OBJECT
public:
  explicit AppMain(QWidget *parent = nullptr);

private slots:
  void onHandleStart();
  void onHandleStop();
  void onDataGet(const QColor &newColor);

private:
  QPushButton *_start_btn = nullptr;
  QPushButton *_stop_btn = nullptr;
  QGraphicsView *_view = nullptr;
  QGraphicsScene *_scene = nullptr;
  Controller _controller;
};

#endif // APPMAIN_H
