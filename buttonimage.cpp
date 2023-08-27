#include "buttonimage.h"
#include <QMouseEvent>

ButtonImage::ButtonImage(QWidget *parent)
{

    setCursor(QCursor(Qt::PointingHandCursor));
    setScaledContents(true);
}

ButtonImage::~ButtonImage()
{

}

void ButtonImage::mousePressEvent(QMouseEvent *event)
{
    if (event->button()==Qt::LeftButton) emit clicked();

}
