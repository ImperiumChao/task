#include "info.h"
#include "ui_info.h"
#include <QDesktopWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QDebug>
#include <QSettings>
#include "windows.h"


Info::Info(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Info)
{
    ui->setupUi(this);
    labelPlay = ui->labelPlay;
    labelPause = ui->labelPause;

    setWindowFlags(Qt::WindowStaysOnTopHint);
    setWindowFlags(Qt::ToolTip);
    setWindowOpacity(0.8);

    if (!settings.contains("ratio"))
    {
        settings.setValue("ratio", 1);
        ratio = 1;
    }
    else ratio = settings.value("ratio").toInt();


    ui->labelPlay->setFixedSize(H*ratio-18, H*ratio-18);
//    ui->labelPlay->setBaseSize(h*ratio-18, h*ratio-18);
    ui->labelPlay->setPixmap(QPixmap(":/play.png"));
    ui->labelPlay->setVisible(false);

    ui->labelPause->setFixedSize(H*ratio-18, H*ratio-18);
//    ui->labelPause->setBaseSize(h*ratio-18, h*ratio-18);
    ui->labelPause->setPixmap(QPixmap(":/pause.png"));
    ui->labelPause->setVisible(false);

    connect(ui->labelPlay, &ButtonImage::clicked , this, &Info::pauseTask);
    connect(ui->labelPause, &ButtonImage::clicked , this, &Info::pauseTask);

    posX = -1;
    posY = -1;

    menu = new QMenu(this);
    QAction * actionNewTask = new QAction("Новая задача Alt+Z", this);
    QAction * actionPauseTask = new QAction("Пауза Alt+X", this);
    QAction * actionStat = new QAction("Статистика Alt+V", this);
    QAction * actionPlan = new QAction("Планирование Alt+A", this);

    connect(actionNewTask, &QAction::triggered, this, &Info::newTask);
    connect(actionPauseTask, &QAction::triggered, this, &Info::pauseTask);
    connect(actionStat, &QAction::triggered, this, &Info::showStatisticForm);
    connect(actionPlan, &QAction::triggered, this, &Info::showPlanForm);

    menu->addAction(actionNewTask);
    menu->addAction(actionPauseTask);
    menu->addAction(actionStat);
    menu->addAction(actionPlan);

    QRect rect = desktop.availableGeometry(desktop.primaryScreen()); // прямоугольник с размерами экрана

    int x_ = rect.width() - W*ratio;
    int y_ = rect.height() - H*ratio;

    if (settings.contains("info_x"))
    {
        x_ = settings.value("info_x").toInt();
        y_ = settings.value("info_y").toInt();
    }

    try
    {
        setGeometry(x_, y_, W*ratio, H*ratio);
    }  catch (const std::exception)
    {
        setGeometry(rect.width() - W*ratio, rect.height() - H*ratio, W*ratio, H*ratio);
    }

//    QFont font("MS Shell Dlg 2", 6.0*ratio, QFont::Bold);
//    ui->label->setFont(font);
//    ui->label->setFixedSize(width()-18,height()-18);


    QFont font("MS Shell Dlg 2", 6.0*ratio, QFont::Bold);
    ui->label->setFont(font);

    ui->labelPlay->setFixedSize(H*ratio-18, H*ratio-18);
    ui->labelPause->setFixedSize(H*ratio-18, H*ratio-18);
    ui->label->setFixedSize(W*ratio-H*ratio-36,H*ratio-18);
}

Info::~Info()
{
    delete ui;
}

void Info::setText(QString text)
{
    ui->label->setText(text);
}

void Info::showInfo(QString text)
{
    qDebug() << "showInfo";
    show();
    ui->label->setText(text);
    timer->start();
//    ui->labelPlayPause->setPixmap(QPixmap("://play.png"));

}

void Info::resetPositionWindow()
{
    QRect rect = desktop.availableGeometry(desktop.primaryScreen()); // прямоугольник с размерами экрана

    setGeometry(rect.width() - W, rect.height() - H, W, H);

    ratio = 1;

    QFont font("MS Shell Dlg 2", 6.0*ratio, QFont::Bold);
    ui->label->setFont(font);

    ui->labelPlay->setFixedSize(H*ratio-18, H*ratio-18);
    ui->labelPause->setFixedSize(H*ratio-18, H*ratio-18);
    ui->label->setFixedSize(W*ratio-H*ratio-36,H*ratio-18);

}

void Info::setOnTop()
{
    SetForegroundWindow((HWND)Info::winId());
}
void Info::hideWin()
{
    qreal op = windowOpacity();
    if (op == 0)
    {
        hide();
        setWindowOpacity(1);
        timer->stop();
        return;
    }
    setWindowOpacity(op-0.05);
}

void Info::killSelf()
{
    destroy = true;
    close();
}

void Info::mouseMoveEvent(QMouseEvent *event)
{
    if (posX == -1)
    {
        posX = event->globalX();
        posY = event->globalY();
        return;
    }

    move(x() + event->globalX() - posX, y() + event->globalY() - posY);
    posX = event->globalX();
    posY = event->globalY();

    settings.setValue("info_x", x());
    settings.setValue("info_y", y());
}

void Info::mouseDoubleClickEvent(QMouseEvent *event)
{
    emit showMainForm();
}

void Info::wheelEvent(QWheelEvent *event)
{
    if (event->delta()>0) ratio+=0.05;
    else if (ratio>=1.0) ratio-=0.05;

    settings.setValue("ratio", ratio);
    settings.setValue("info_x", x());
    settings.setValue("info_y", y());
    setGeometry(x(), y(), W*ratio, H*ratio);


    QFont font("MS Shell Dlg 2", 6.0*ratio, QFont::Bold);
    ui->label->setFont(font);

    ui->labelPlay->setFixedSize(H*ratio-18, H*ratio-18);
    ui->labelPause->setFixedSize(H*ratio-18, H*ratio-18);
    ui->label->setFixedSize(W*ratio-H*ratio-36,H*ratio-18);

}

void Info::mousePressEvent(QMouseEvent *event)
{
    if (event->button()==Qt::RightButton)
    {
        menu->move(event->globalX(), event->globalY());
        menu->show();
    }
    else if (event->button()==Qt::MiddleButton) emit showStatisticForm();
//    qDebug() <<  event->button();
}


void Info::mouseReleaseEvent(QMouseEvent *event)
{
    posX = -1;
    posY = -1;

}
