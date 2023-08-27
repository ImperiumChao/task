#include "qmytablewidgetitem.h"
#include <QDebug>

QMyTableWidgetItem::QMyTableWidgetItem()
{

}

void QMyTableWidgetItem::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "бля заработало";
}
