#include "task.h"
#include "ui_widget.h"
#include <QDebug>
#include <QShortcut>
#include <QCloseEvent>
#include <QListWidgetItem>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDate>
#include <QTime>
#include <windows.h>
#include <winuser.h>
#include <QMenu>
#include <QKeyEvent>
#include "notificationpause.h"
#include <QMimeData>
#include <QProcess>
#include <QSettings>
#include <QDir>
#include <QTimer>
#include "addtask.h"
#include "info.h"
#include "addtask.h"





Task::Task(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QCoreApplication::setOrganizationName("Imperium Chao");
    QCoreApplication::setApplicationName("task");


    connect(ui->taskList, &QListWidget::itemActivated, ui->taskList, &QListWidget::itemDoubleClicked);
    connect(ui->taskList, &QListWidget::currentItemChanged, this, &Task::changeSelectedTask);

    setWindowFlags(Qt::WindowStaysOnTopHint);

    RegisterHotKey((HWND)Task::winId(), 100, MOD_ALT, 'Z'); //newTask()
    RegisterHotKey((HWND)Task::winId(), 101, MOD_ALT, 'X'); //pauseTask();
    RegisterHotKey((HWND)Task::winId(), 102, MOD_ALT, 'C'); //openFillForm()
    RegisterHotKey((HWND)Task::winId(), 103, MOD_ALT, 'V'); //statistic()
    RegisterHotKey((HWND)Task::winId(), 104, MOD_ALT, 'A'); //planning()
    RegisterHotKey((HWND)Task::winId(), 106, MOD_ALT, 'D');
    RegisterHotKey((HWND)Task::winId(), 105, MOD_ALT, 'Q'); //exit()

    QShortcut* shortcutMinimize = new QShortcut(this);
    shortcutMinimize->setKey(Qt::Key_Escape);
    connect(shortcutMinimize, &QShortcut::activated, this, &QWidget::hide);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon("icon.png"));
    trayIcon->setToolTip("task" "\n"
                         "Программа для подсчета времени на выполнение задач");

    QMenu * menu = new QMenu(this);
    QAction * actionNewtask = new QAction("Новая задача Alt+Z", this);
    QAction * actionPause = new QAction("Пауза Alt+X", this);
    QAction * actionTasks = new QAction("Задачи Alt+C", this);
    QAction * actionStat = new QAction("Статистика Alt+V", this);
    QAction * actionPlan = new QAction("Планирование Alt+A", this);
    QAction * actionResetWindowsSettings = new QAction("Сбросить настройки окон", this);
//    QAction * actionAutoRun = new QAction("Автозагрузка Windows", this);
    QAction * actionExit = new QAction("Выход Alt+Q", this);
    QAction * actionTimeCategorys = new QAction("Категории трудоемкости", this);


    connect(actionNewtask, &QAction::triggered, this, &Task::newTask);
    connect(actionPause, &QAction::triggered, this, &Task::pauseTask);
    connect(actionTasks, &QAction::triggered, this, &QWidget::show);
    connect(actionStat, &QAction::triggered, this, &Task::showStatisticForm);
    connect(actionResetWindowsSettings, &QAction::triggered, this, &Task::resetWindowsSettings);
    connect(actionExit, &QAction::triggered, this, [ ](){QApplication::exit();});
    connect(actionPlan, &QAction::triggered, this, [=](){planForm->show();});
    connect(actionTimeCategorys, &QAction::triggered, this, [=](){timeCategorysForm->show();});
//    connect(actionAutoRun, &QAction::triggered, this, &Widget::autorun);


//    actionAutoRun->setIcon(QIcon(":/galka.png"));
    QMenu * menuAdvanced = new QMenu(this);
    menuAdvanced->setTitle("Дополнительно");
    menuAdvanced->addAction(actionTimeCategorys);

    menu->addAction(actionNewtask);
    menu->addAction(actionPause);
    menu->addAction(actionTasks);
    menu->addAction(actionStat);
    menu->addAction(actionPlan);
    menu->addMenu(menuAdvanced);
    menu->addAction(actionResetWindowsSettings);
//    menu->addAction(actionAutoRun);
    menu->addAction(actionExit);

    trayIcon->setContextMenu(menu);
    trayIcon->show();
    connect(trayIcon, &QSystemTrayIcon::activated, this, &Task::activatedTrayIcon);

    connectDataBase();

    currentTask = "";
    currentPeriod = "";
    pause = false;

    timerPeriod = new QTimer;
    timerPeriod->setInterval(30000);//30 сек
    timerPeriod->start();
    connect(timerPeriod, &QTimer::timeout,this, &Task::updatePeriod);

    timerPause = new QTimer;
    timerPause->setInterval(300000);//5 минут
    timerPause->start();
    connect(timerPause, &QTimer::timeout, this, &Task::showNotificationPause);

    timerExchange = new QTimer;
    timerExchange->setInterval(500);//пол секунды
    timerExchange->start();
    connect(timerExchange, &QTimer::timeout, this, &Task::exchange1C);


    statisticForm = new Statistic;
    planForm = new Planning;
    pauseForm = new PauseForm;
    timeCategorysForm = new TimeCategorys;

    addTaskForm = new AddTask;
    connect(addTaskForm, &AddTask::taskAdded, planForm, &Planning::fillTasks);

    infoForm = new Info;
    infoForm->setText("Нет задач");
    infoForm->show();

    connect(infoForm, &Info::showMainForm, this, &Task::show);
    connect(infoForm, &Info::newTask, this, &Task::newTask);
    connect(infoForm, &Info::pauseTask, this, &Task::pauseTask);
    connect(infoForm, &Info::showStatisticForm, this, &Task::showStatisticForm);
    connect(infoForm, &Info::showPlanForm, this, [=](){planForm->show();});

    buffer = QApplication::clipboard();

    settingsrestored = false;
}



Task::~Task()
{
    delete ui;
}

void Task::updateDataMainForm()
{
    QSqlQuery query;
    query.prepare("SELECT Tasks.id_task, "
                  "Tasks.description "
                  "FROM Periods JOIN Tasks "
                  "ON Periods.id_task=Tasks.id_task "
                  "GROUP BY Tasks.id_task, Tasks.description "
                  "ORDER BY Periods.id_period DESC "
                  "LIMIT 50");
    if(!query.exec()) return;

    ui->taskList->clear();
    taskList.clear();

    QFont fontForCurrentTask("Times", 10, QFont::Bold);

    bool first = true;
    while (query.next())
    {
        QString id_task = query.value("id_task").toString();
        QString description = query.value("description").toString();

        if (description=="") description="Незаполенная задача";

        QListWidgetItem *item = new QListWidgetItem;
        item->setText(description.split("\n")[0]);
        if (currentTask==id_task) item->setFont(fontForCurrentTask);
        ui->taskList->addItem(item);

        taskList.append(QStringList() << id_task << description);

        if (first)
        {
            if (description=="Незаполенная задача") description = "";
            ui->taskList->setCurrentRow(0);
            ui->taskText->setText(description);
            first = false;

        }
    }

}


bool Task::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType)
    Q_UNUSED(result)

    MSG* msg = reinterpret_cast<MSG*>(message);

    if(msg->message == WM_HOTKEY){

        if(msg->wParam == 100) //alt Z
        {
            newTask();
            return true;
        }
        else if(msg->wParam == 101) //alt X
        {
            pauseTask();
            return true;
        }
        else if(msg->wParam == 102) //alt C
        {
            if (this->isVisible()) hide();
            else show();
            return true;
        }
        else if(msg->wParam == 103) //alt V
        {
            if (statisticForm->isVisible()) statisticForm->hide();
            else showStatisticForm();
            return true;
        }
        else if(msg->wParam == 104) //alt A
        {
           if (planForm->isVisible()) planForm->hide();
           else planForm->show();
           return true;
        }
        else if(msg->wParam == 105) //alt Q
        {
            QApplication::quit();
            return true;
        }
        else if(msg->wParam == 106) //alt D
        {
            addTaskForm->show();
            return true;
        }
    }
    return false;
}

void Task::closeEvent(QCloseEvent *event)
{
    event->ignore();
    hide();

}

void Task::connectDataBase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("task.db");
    db.open();

    QStringList tables = db.tables();
    if (!tables.contains("Tasks"))
    {
        QSqlQuery query("CREATE TABLE Tasks ( "
                        "id_task INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, "
                        "description TEXT )");
        query.exec();
    }
    if (!tables.contains("Periods"))
    {
        QSqlQuery query("CREATE TABLE Periods ( "
                        "id_period INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, "
                        "id_task INTEGER, "
                        "date TEXT, "
                        "begin TEXT, "
                        "end TEXT, "
                        "FOREIGN KEY(id_task) REFERENCES Tasks(id_task) )");
        query.exec();
    }
    if (!tables.contains("Projects"))
    {
        QSqlQuery query("CREATE TABLE Projects ( "
                        "id_project INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, "
                        "sequence_number INTEGER, "
                        "name TEXT )");
        query.exec();
    }
    if (!tables.contains("Scheduled_tasks"))
    {
        QSqlQuery query("CREATE TABLE Scheduled_tasks ( "
                        "id_task INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, "
                        "id_project INTEGER, "
                        "text_tasks TEXT, "
                        "sequence_number INTEGER, "
                        "begin TEXT, "
                        "end TEXT, "
                        "FOREIGN KEY(id_project) REFERENCES Projects(id_project))");
        query.exec();
    }

    QSqlQuery query("CREATE INDEX IF NOT EXISTS day_index ON Periods (date)");
    query.exec();

    query.prepare("CREATE INDEX IF NOT EXISTS task_index ON Periods (id_task)");
    query.exec();

    query.prepare("CREATE INDEX IF NOT EXISTS scheduled_tasks_id_project_index ON Scheduled_tasks (id_project)");
    query.exec();

    query.prepare("CREATE INDEX IF NOT EXISTS scheduled_tasks_begin_index ON Scheduled_tasks (begin)");
    query.exec();

    //НОВОЕ
    if (!tables.contains("Time_categorys"))
    {
        query.prepare("CREATE TABLE IF NOT EXISTS Time_categorys ("
                      "id_category INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, "
                      "name TEXT UNIQUE, "
                      "min_from REAL, "
                      "min_to REAL, "
                      "defaultValue INTEGER DEFAULT 0)");
        query.exec();

        query.prepare("INSERT INTO Time_categorys(name, min_from, min_to, defaultValue) VALUES(\"БЫСТРО\", 10, 60, 1)");
        query.exec();

        query.prepare("ALTER TABLE Scheduled_tasks "
                      "ADD COLUMN id_category INTEGER REFERENCES Time_categorys(id_category)");
        query.exec();

    }

    query.prepare("UPDATE Scheduled_tasks SET id_category=(SELECT id_category FROM Time_categorys WHERE defaultValue = 1) WHERE id_category IS NULL");
    query.exec();

}

void Task::resetWindowsSettings()
{
    QSettings settings;
    settings.clear();
    statisticForm->move(10,10);
    planForm->move(10,10);
    move(10,10);
    infoForm->resetPositionWindow();
}

void Task::updateInfoForm()
{
    if (currentTask.isEmpty())
    {
        infoForm->setText("Нет задач");
        infoForm->labelPause->setVisible(false);
        infoForm->labelPlay->setVisible(false);
        return;
    }
    QString description="";

    QSqlQuery query;
    query.prepare("SELECT description FROM Tasks WHERE id_task=:id_task");
    query.bindValue(":id_task", currentTask);
    query.exec();
    if (query.next())
    {
        description = query.value("description").toString();
        if (description=="") description="Незаполненная задача";
    }

    description = description.split("\n")[0];

    int hh_gen=0, mm_gen=0;

    query.prepare("SELECT begin, end FROM Periods WHERE id_task=:id_task");
    query.bindValue(":id_task", currentTask);
    query.exec();

    while (query.next())
    {
        int h = query.value("end").toString().left(2).toInt() - query.value("begin").toString().left(2).toInt();
        int m = query.value("end").toString().right(2).toInt() - query.value("begin").toString().right(2).toInt();
        if (m<0)
        {
            m+=60;
            h--;
        }
        hh_gen+= h;
        mm_gen+= m;

    }
    hh_gen+= mm_gen/60;
    mm_gen = mm_gen%60;

    QString str_h, str_m;
    str_h = QString::number(hh_gen);
    str_m = QString::number(mm_gen);
    if (str_h.length()==1) str_h = "0" + str_h;
    if (str_m.length()==1) str_m = "0" + str_m;

    description+= " (" + str_h + ":" + str_m + ")";

    if (pause) description = "Пауза: " + description;

    infoForm->setText(description);
    infoForm->labelPlay->setVisible(pause);
    infoForm->labelPause->setVisible(!pause);

}


void Task::newTask()
{
    pause = false;
    pauseForm->hide();

    QSqlQuery query;
    query.prepare("INSERT INTO Tasks(description) VALUES(:description)");
    query.bindValue(":description", "");
    query.exec();

    query.prepare("SELECT last_insert_rowid()");
    query.exec();
    query.next();
    currentTask = query.value(0).toString();

    query.prepare("INSERT INTO Periods(id_task, date, begin, end) VALUES(:id_task, :date, :time, :time)");
    query.bindValue(":id_task", currentTask);
    query.bindValue(":date", QDate::currentDate().toString("yyyy.MM.dd"));
    query.bindValue(":time", QTime::currentTime().toString("hh:mm"));
    query.exec();

    query.prepare("SELECT last_insert_rowid()");
    query.exec();
    query.next();
    currentPeriod = query.value(0).toString();

    if (statisticForm->isVisible()) statisticForm->fillForm();
    updateDataMainForm();
    updateInfoForm();
    timerPause->stop();
}

void Task::pauseTask()
{
    if (currentTask.isEmpty()) return;

    QSqlQuery query;

    if (pause)
    {
        query.prepare("INSERT INTO Periods(id_task, date, begin, end) VALUES(:id_task, :date, :time, :time)");
        query.bindValue(":id_task", currentTask);
        query.bindValue(":date", QDate::currentDate().toString("yyyy.MM.dd"));
        query.bindValue(":time", QTime::currentTime().toString("hh:mm"));
        query.exec();

        query.prepare("SELECT last_insert_rowid()");
        query.exec();
        query.next();
        currentPeriod = query.value(0).toString();
        pause = false;
        pauseForm->hide();
        timerPause->stop();
    }
    else
    {
        pause = true;
        timerPause->start();
    }

    if (statisticForm->isVisible()) statisticForm->fillForm();
    updateInfoForm();
}

void Task::showStatisticForm()
{
    statisticForm->fillForm();
    statisticForm->show();
}


void Task::changeSelectedTask()
{
    if (taskList.isEmpty() || ui->taskList->currentRow()==-1) return;

    QString description = taskList[ui->taskList->currentRow()].at(1);
    if (description=="Незаполненная задача") description="";

    ui->taskText->setText(description);
    updateInfoForm();
}

void Task::showNotificationPause()
{
    pauseForm->show();
}

void Task::exchange1C()
{
    const QMimeData *mimeData = buffer->mimeData();
    if (!mimeData->hasText()) return;
    QString text = mimeData->text();

    if(text.left(13)!="///Данные за ") return;


    QString date = text.mid(13,10);
    QSqlQuery query;
//    query.prepare("SELECT per.id_task, per.id_period, z.description, per.begin, per.end FROM Periods per LEFT OUTER JOIN Tasks z ON per.id_task=z.id_task WHERE per.date = :date ORDER BY per.id_period DESC");
    query.prepare("SELECT "
                  "per.id_task, "
                  "per.id_period, "
                  "z.description, "
                  "per.begin, "
                  "per.end, "
                  "per.date "
                  "FROM Periods per "
                  "LEFT OUTER JOIN "
                  "Tasks z ON per.id_task=z.id_task "
                  "WHERE per.date = :date OR :date=\"всё время \""
                  "ORDER BY per.id_period DESC");
    query.bindValue(":date", date);
    query.exec();

    QString res = "///Задачи за " + date + "///\n";
    while (query.next())
    {
        QString description = query.value("description").toString();
        description = description.replace("\n", "@#$$");
        description = description.replace(";", "@#;;");

        res+=query.value("id_task").toString() + ";";
        res+=query.value("id_period").toString() + ";";
        res+=description + ";";
        res+=query.value("begin").toString() + ";";
        res+=query.value("end").toString() + ";";
        res+=query.value("date").toString() + ";\n";

    }
    res+="///КОНЕЦ///";
    buffer->setText(res);
}

void Task::activatedTrayIcon(QSystemTrayIcon::ActivationReason reason)
{
    if (reason== QSystemTrayIcon::DoubleClick) show();
    else if (reason== QSystemTrayIcon::MiddleClick) showStatisticForm();
    else if (reason== QSystemTrayIcon::Trigger) infoForm->setOnTop();
    //    showMainForm();
}

void Task::autorun()
{
    qDebug() << "autorun";
    QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
    settings.setValue("task", QDir::toNativeSeparators(QCoreApplication::applicationFilePath()));
    settings.sync();

//    QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
//    settings.remove("task");
}

void Task::showEvent(QShowEvent *)
{
    ui->taskText->setFocus();
    updateDataMainForm();
    SetForegroundWindow((HWND)Task::winId());

    if (!settingsrestored)
    {
        QSettings settings;
        ui->splitter->restoreState(settings.value("splitterMainWindowSizes").toByteArray());
        if (settings.contains("mainWindow_x") && settings.contains("mainWindow_width"))
        {

            int x_ = settings.value("mainWindow_x").toInt();
            int y_ = settings.value("mainWindow_y").toInt();
            int w_ = settings.value("mainWindow_width").toInt();
            int h_ = settings.value("mainWindow_height").toInt();
            qDebug() << "restoreMainW" << x_ << y_ << w_ << h_;
            setGeometry(x_, y_, w_, h_);
            qDebug() << "restoreMainW__" << x() << y() << width() << height();
        }
    }
    settingsrestored = true;

}

void Task::hideEvent(QHideEvent *)
{
    qDebug() << "hideEvent" << x() << y() << width() << height();
    QSettings settings;
    settings.setValue("splitterMainWindowSizes", ui->splitter->saveState());
    settings.setValue("mainWindow_x", x());
    settings.setValue("mainWindow_y", y());
    settings.setValue("mainWindow_width", width());
    settings.setValue("mainWindow_height", height());
}

void Task::on_taskText_textChanged()
{
    if(taskList.isEmpty()) return;

    QString task_id = taskList[ui->taskList->currentRow()][0];
    QString description = ui->taskText->toPlainText();

    QSqlQuery query;
    query.prepare("UPDATE Tasks SET description = :description WHERE id_task=:id_task");
    query.bindValue(":id_task", task_id);
    query.bindValue(":description", description);
    if (!query.exec()) QMessageBox::warning(0,"Ошибка", "Не удалось изменить задачу");
    QString txt = ui->taskText->toPlainText();
    if (txt=="") txt = "Незаполненная задача";
    ui->taskList->currentItem()->setText(txt.split("\n")[0]);
    taskList[ui->taskList->currentRow()][1] = txt;

    updateInfoForm();

    if (statisticForm->isVisible()) statisticForm->fillForm();

//    emit updateSpecificTask(task_id, description);

}

void Task::on_taskList_itemDoubleClicked(QListWidgetItem *)
{
    if (currentTask==taskList[ui->taskList->currentRow()][0]) return;
    currentTask = taskList[ui->taskList->currentRow()][0];

    QSqlQuery query;
    query.prepare("INSERT INTO Periods(id_task, date, begin, end) VALUES(:id_task, :date, :time, :time)");
    query.bindValue(":id_task", currentTask);
    query.bindValue(":date", QDate::currentDate().toString("yyyy.MM.dd"));
    query.bindValue(":time", QTime::currentTime().toString("hh:mm"));
    query.exec();

    query.prepare("SELECT last_insert_rowid()");
    query.exec();
    query.next();
    currentPeriod = query.value(0).toString();

    pause = false;
    timerPause->stop();
    pauseForm->hide();

    updateDataMainForm();
    updateInfoForm();

}


void Task::updatePeriod()
{
    if(pause) return;

    QString currentTime = QTime::currentTime().toString("hh:mm");
    if (currentTime=="23:59" || currentTime == "00:00")
    {
        pause = true;
        return;
    }

    QSqlQuery query;
    query.prepare("UPDATE Periods SET end = :end WHERE id_period=:id_period");
    query.bindValue(":id_period", currentPeriod);
    query.bindValue(":end", currentTime);
    if (!query.exec()) qDebug() << query.lastError();
    if (statisticForm->isVisible()) statisticForm->fillForm();

    updateInfoForm();
}

