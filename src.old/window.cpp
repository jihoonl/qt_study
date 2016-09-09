#include <QtGui>

#include "rgbd_viewer/gl_widget.h"
#include "rgbd_viewer/window.h"

Window::Window()
{
  glWidget = new GLWidget();

  x_slider = createSlider();
  y_slider = createSlider();
  z_slider = createSlider();

  connect(x_slider, SIGNAL(valudeChanged(int)),     glWidget, SLOT(setXRotation(int)));
  connect(glWidget, SIGNAL(xRotationChanged(int)),  x_slider, SLOT(setValue(int)));
  connect(y_slider, SIGNAL(valudeChanged(int)),     glWidget, SLOT(setYRotation(int)));
  connect(glWidget, SIGNAL(yRotationChanged(int)),  y_slider, SLOT(setValue(int)));
  connect(z_slider, SIGNAL(valudeChanged(int)),     glWidget, SLOT(setZRotation(int)));
  connect(glWidget, SIGNAL(zRotationChanged(int)),  z_slider, SLOT(setValue(int)));

  QHBoxLayout *mainLayout= new QHBoxLayout();
  mainLayout->addWidget(glWidget);
  mainLayout->addWidget(x_slider);
  mainLayout->addWidget(y_slider);
  mainLayout->addWidget(z_slider);
  setLayout(mainLayout);

  x_slider->setValue(15 * 16);
  y_slider->setValue(345 * 16);
  z_slider->setValue(0 * 16);
  setWindowTitle(tr("Hello GL"));
}


QSlider* Window::createSlider()
{
  QSlider *slider = new QSlider(Qt::Vertical);
  slider->setRange(0, 360 * 16);
  slider->setSingleStep(16);
  slider->setPageStep(15 * 16);
  slider->setTickInterval(15 * 16);
  slider->setTickPosition(QSlider::TicksRight);
  return slider;
}

void Window::keyPressEvent(QKeyEvent* e)
{
  if(e->key() == Qt::Key_Escape)
    close();
  else
    QWidget::keyPressEvent(e);
}
