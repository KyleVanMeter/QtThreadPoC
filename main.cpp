#include "appmain.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QApplication::setApplicationDisplayName("Thread test");

  AppMain client;
  client.show();

  return a.exec();
}
