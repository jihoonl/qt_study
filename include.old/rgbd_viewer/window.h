
#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <QWidget>

#include "rgbd_viewer/gl_widget.h"

QT_BEGIN_NAMESPACE
class QSlider;
QT_END_NAMESPACE

class GLWidget;

class Window : public QWidget
{
  Q_OBJECT
  public:
    Window();
  protected:
    void keyPressEvent(QKeyEvent * event);

  private:
    QSlider *createSlider();

    GLWidget *glWidget;
    QSlider *x_slider;
    QSlider *y_slider;
    QSlider *z_slider;
};

#endif
