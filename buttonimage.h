#ifndef BUTTONIMAGE_H
#define BUTTONIMAGE_H

#include <QLabel>
#include <QObject>
#include <QWidget>

class ButtonImage : public QLabel
{
    Q_OBJECT
public:
    explicit ButtonImage(QWidget *parent = nullptr);
    ~ButtonImage();

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);
signals:
    void clicked();
};

#endif // BUTTONIMAGE_H
