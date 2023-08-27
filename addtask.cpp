#include "addtask.h"
#include "ui_addtask.h"
#include <windows.h>
#include <QSqlQuery>
#include <QDate>
#include <QShortcut>
#include <QSettings>
#include <QDebug>

AddTask::AddTask() :
    ui(new Ui::AddTask)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    QShortcut* shortcut = new QShortcut(this);
    shortcut->setKey(Qt::Key_Escape);

    connect( shortcut, SIGNAL(activated()), SLOT(hide()));

    shortcut = new QShortcut(ui->textTask);
    shortcut->setKey(QKeySequence("Ctrl+Space"));

    connect(shortcut, &QShortcut::activated, this, &AddTask::on_buttonBox_accepted);

    QSettings settings;
    if (settings.contains("addTask_x") && settings.contains("addTask_width"))
    {
        int x_ = settings.value("addTask_x").toInt();
        int y_ = settings.value("addTask_y").toInt();
        int w_ = settings.value("addTask_width").toInt();
        int h_ = settings.value("addTask_height").toInt();
        setGeometry(x_, y_, w_, h_);
    }
}

AddTask::~AddTask()
{
    delete ui;
}

void AddTask::on_buttonBox_accepted()
{
    QString id_project = projects[ui->projects->currentIndex()];

    QSqlQuery query;

    int sequence_number = 1;
    query.prepare("SELECT max(sequence_number) AS sequence_number FROM Scheduled_tasks WHERE id_project=:id_project");
    query.bindValue(":id_project", id_project);
    query.exec();

    if (query.next())
    {
        sequence_number = query.value("sequence_number").toInt();
    }

    query.prepare("INSERT INTO Scheduled_tasks(id_project, text_tasks, sequence_number, begin) VALUES (:id_project, :text_tasks, :sequence_number, :begin)");
    query.bindValue(":id_project", id_project);
    query.bindValue(":text_tasks", ui->textTask->toPlainText());
    query.bindValue(":sequence_number", ++sequence_number);
    query.bindValue(":begin", QDate::currentDate().toString("yyyy.MM.dd"));
    query.exec();
    emit taskAdded();
    hide();
}

void AddTask::showEvent(QShowEvent *)
{
    qDebug() << "showEvent";
    SetForegroundWindow((HWND)AddTask::winId());

    ui->projects->clear();
    projects.clear();

    QSqlQuery query;
    query.prepare("SELECT id_project, name FROM Projects ORDER BY sequence_number");
    query.exec();

    while (query.next())
    {
        ui->projects->addItem(query.value("name").toString());
        projects.append(query.value("id_project").toString());
    }
    if (ui->projects->count()!=0)  ui->projects->setCurrentIndex(0);
    ui->textTask->clear();

    ui->textTask->setFocus();
}

void AddTask::closeEvent(QCloseEvent *event)
{
    event->ignore();
    hide();
}

void AddTask::hideEvent(QHideEvent *)
{
    QSettings settings;
    settings.setValue("addTask_x", x());
    settings.setValue("addTask_y", y());
    settings.setValue("addTask_width", width());
    settings.setValue("addTask_height", height());
}

void AddTask::on_buttonBox_rejected()
{
    hide();
}
