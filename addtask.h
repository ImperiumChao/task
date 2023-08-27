#ifndef ADDTASK_H
#define ADDTASK_H

#include <QWidget>

namespace Ui {
class AddTask;
}

class AddTask : public QWidget
{
    Q_OBJECT

public:
    explicit AddTask();
    ~AddTask();

private:
    Ui::AddTask *ui;
    QStringList projects;
signals:
    void taskAdded();
private slots:
    void on_buttonBox_accepted();

    // QWidget interface
    void on_buttonBox_rejected();

protected:
    void showEvent(QShowEvent *);

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *);

    // QWidget interface
protected:
    void hideEvent(QHideEvent *);
};

#endif // ADDTASK_H
