#include "notificationpause.h"
#include "ui_notificationpause.h"
#include <QCloseEvent>
#include <QDebug>
#include "windows.h"

PauseForm::PauseForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PauseForm)
{
    ui->setupUi(this);
//    mainForm = parent;
}

PauseForm::~PauseForm()
{
    delete ui;
}

void PauseForm::on_pushButton_clicked()
{
    close();
}

void PauseForm::closeEvent(QCloseEvent *event)
{
    hide();
    event->ignore();
}

void PauseForm::showEvent(QShowEvent *)
{
    SetForegroundWindow((HWND)PauseForm::winId());
}

