#ifndef NOTIFICATIONPAUSE_H
#define NOTIFICATIONPAUSE_H

#include <QDialog>

namespace Ui {
class PauseForm;
}

class PauseForm : public QDialog
{
    Q_OBJECT

public:
    explicit PauseForm(QWidget *parent = 0);
    ~PauseForm();

private slots:
    void on_pushButton_clicked();

private:
    Ui::PauseForm *ui;
    QWidget mainForm;

    // QDialog interface
public slots:

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event);
signals:
    void showMainForm();

    // QWidget interface
protected:
    void showEvent(QShowEvent *);
};

#endif // NOTIFICATIONPAUSE_H
