#ifndef QMYTABLEWIDGETITEM_H
#define QMYTABLEWIDGETITEM_H

#include <QTableWidgetItem>
#include <QObject>
#include <QWidget>

class QMyTableWidgetItem : public QTableWidgetItem
{
public:
    QMyTableWidgetItem();
protected:
    void mousePressEvent(QMouseEvent* event);
};

#endif // QMYTABLEWIDGETITEM_H
