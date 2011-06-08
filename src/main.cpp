#include <QtGui/QApplication>
#include "home.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  Home *home = new Home();
  home->show();

  return a.exec();
}
