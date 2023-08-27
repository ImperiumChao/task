#ifndef INFO_H
#define INFO_H

#include <QWidget>
#include <QTimer>
#include <QMenu>
#include <QPalette>
#include <QLabel>
#include <QSettings>
#include <QDesktopWidget>

#include "buttonimage.h"

namespace Ui
{
    class Info;
}

class Info : public QWidget
{
    Q_OBJECT

public:
    explicit Info(QWidget *parent = 0);
    ~Info();
    void setText(QString text);
    void showInfo(QString text);
    void destroySelf();
    ButtonImage *labelPlay, *labelPause;
    void resetPositionWindow();
    void setOnTop();


private:
    Ui::Info *ui;
    QTimer *timer;
    int posX, posY;
    bool destroy;
    const int W=200, H=35;
    float ratio;
    QMenu *menu;
    QPixmap pixmap;
    QSettings settings;
    QDesktopWidget desktop;

private slots:
    void hideWin();

public slots:
    void killSelf();
    // QWidget interface
protected:
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
signals:
    void showMainForm();
    void newTask();
    void pauseTask();
    void showStatisticForm();
    void showPlanForm();

    // QWidget interface

};

#endif // INFO_H
