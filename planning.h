#ifndef PLANNING_H
#define PLANNING_H

#include <QWidget>
#include <QCloseEvent>
#include "addtask.h"
#include <QTextEdit>
#include <QMap>
#include <QCheckBox>
#include <QComboBox>
#include <QListWidgetItem>

namespace Ui {
class Planning;
}

class Planning : public QWidget
{
    Q_OBJECT

public:
    explicit Planning(QWidget *parent = nullptr);
    ~Planning();

private:
    Ui::Planning *ui;
    QWidget *getCheckWidgetTable(QString id_task, bool completed);
    QTextEdit *getTextEditTable(QString id_task, QString text, bool completed, int row);
    QComboBox *getComboBoxTimeCategory(QString id_task, QString id_category);
    QStringList projects;
    AddTask* at;
    QList<QMap<QString, QString>> timeCategorys;
    void fillMetrics();

private slots:
    void textTaskChanged();
    void checkTaskChanged();
    void timeCategoryChanged(int index);

    void addTask(QString id_project="");

    // QWidget interface
    void on_addProject_clicked();

    void on_deleteProject_clicked();

    void on_orderProjectUp_clicked();

    void on_orderProjectDown_clicked();
    void on_calendar_activated(const QDate &date);

    void on_projects_currentRowChanged(int currentRow);

    void on_calendar_clicked(const QDate &date);

    void on_showCompletedTasks_stateChanged(int arg1);

    void on_addTask_clicked();

    void on_orderTaskUp_clicked();

    void on_orderTaskDown_clicked();

    void on_deleteTask_clicked();
    void on_projects_itemDoubleClicked(QListWidgetItem *item);

public slots:
    void fillProjects();
    void fillTasks();
    void updateTimeCategorys();

signals:
    void needAddTask(QString id_project="");

protected:
    void closeEvent(QCloseEvent *event);

    // QWidget interface
protected:
    void hideEvent(QHideEvent *);

    // QWidget interface
protected:
    void showEvent(QShowEvent *);
};

#endif // PLANNING_H
