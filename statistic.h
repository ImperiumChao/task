#ifndef STATISTIC_H
#define STATISTIC_H

#include <QWidget>
#include <QCloseEvent>
#include <QDate>
#include <QMenu>
//#include "windows.h"
//#include "winuser.h"

namespace Ui {
class Statistic;
}

class Statistic : public QWidget
{
    Q_OBJECT

public:
    explicit Statistic(QWidget *parent = nullptr);
    ~Statistic();
    void fillForm();

private:
    Ui::Statistic *ui;
    QList<QStringList> periods, tasks;
    QString hmToTime(int h, int m);
    bool editable;
    QMenu *menu;
    void deletePeriod(int row);
    void deleteTask(int row);
    void fillMetrics();

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event);
    void hideEvent(QHideEvent *);
    void showEvent(QShowEvent *);

private slots:
    void on_calendar_clicked(const QDate &selectedDate);
    void on_forward_clicked();
    void on_back_clicked();
    void on_periods_cellChanged(int row, int column);
    void on_calendar_activated(const QDate &selectedDate);
    void customMenuRequested(QPoint point);
    void deletePeriodOrTask();
    void on_tasks_cellChanged(int row, int column);

};

#endif // STATISTIC_H
