#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "windows.h"
#include <QSystemTrayIcon>
#include <QSqlDatabase>
#include <QListWidgetItem>
#include "statistic.h"
#include "planning.h"
#include <QTimer>
#include "info.h"
#include "notificationpause.h"
#include <QClipboard>
#include "addtask.h"
#include "timecategorys.h"


namespace Ui {
class Widget;
}

class Task : public QWidget
{
    Q_OBJECT

public:
    explicit Task(QWidget *parent = nullptr);
    ~Task();

private:
    Ui::Widget *ui;
    void updateDataMainForm();
    QSystemTrayIcon *trayIcon;
    PauseForm *pauseForm;
    QSqlDatabase db;
    QList<QStringList> taskList;
    QString currentTask;
    QString currentPeriod;
    QClipboard *buffer;

    bool pause;
    Statistic *statisticForm;
    Info *infoForm;
    Planning *planForm;
    AddTask *addTaskForm;
    TimeCategorys *timeCategorysForm;
    QTimer *timerPeriod, *timerInfo, *timerPause, *timerExchange, *singleShot;
    void updateInfoForm();
    bool settingsrestored;

private slots:
    void on_taskText_textChanged();
    void on_taskList_itemDoubleClicked(QListWidgetItem *);
    void updatePeriod();
    void newTask();
    void pauseTask();
    void showStatisticForm();
    void changeSelectedTask();
    void showNotificationPause();
    void exchange1C();
    void activatedTrayIcon(QSystemTrayIcon::ActivationReason reason);
    void autorun();
    void connectDataBase();
    void resetWindowsSettings();

protected:
    void hideEvent(QHideEvent *);
    void showEvent(QShowEvent *);
    void closeEvent(QCloseEvent *);
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
};

#endif // WIDGET_H
