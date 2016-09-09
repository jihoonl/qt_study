#include<QApplication>
#include<QDesktopWidget>

#include "rgbd_viewer/window.h"

int main(int argc, char* argv[])
{
  QApplication app(argc, argv);
  Window window;
  window.resize(window.sizeHint());

  int desktop_area = QApplication::desktop()->width() * QApplication::desktop()->height();
  int widget_area = window.width() * window.height();

  if(((float)widget_area / (float)desktop_area) < 0.75f)
    window.show();
  else
    window.showMaximized();
  return app.exec();
}
