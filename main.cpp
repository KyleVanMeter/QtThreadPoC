#include "appmain.h"
#include <QApplication>
#include <QMainWindow>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QApplication::setApplicationDisplayName("Thread test");

  QMainWindow w;
  AppMain client(&w);
  w.setCentralWidget(&client);
  w.show();

  return a.exec();
}
