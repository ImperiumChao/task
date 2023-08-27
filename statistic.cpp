#include "statistic.h"
#include "ui_statistic.h"
#include <QSqlQuery>
#include <QDate>
#include <QDebug>
#include <QShortcut>
#include "windows.h"
#include <QMouseEvent>
#include <QMenu>
#include <cmath>
#include <QSettings>
//#include "winuser.h"

Statistic::Statistic(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Statistic)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint);

    ui->calendar->setSelectedDate(QDate::currentDate());

    ui->periods->horizontalHeader()->resizeSection(0,300);

    editable = false;

    QShortcut* shortcut = new QShortcut(this);
    shortcut->setKey(Qt::Key_Escape);
    connect(shortcut, &QShortcut::activated, this, &QWidget::hide);

    ui->periods->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->periods, &QWidget::customContextMenuRequested, this, &Statistic::customMenuRequested);

    ui->tasks->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tasks, &QWidget::customContextMenuRequested, this, &Statistic::customMenuRequested);

    menu = new QMenu(this);
    QAction * action = new QAction("Удалить", this);
    menu->addAction(action);
    connect(action, SIGNAL(triggered()), this, SLOT(deletePeriodOrTask()));

    QSettings settings;


    if (settings.contains("statistic_x") && settings.contains("statistic_width"))
    {
        ui->splitter->restoreState(settings.value("splitterStatisticSizes").toByteArray());
        int x_ = settings.value("statistic_x").toInt();
        int y_ = settings.value("statistic_y").toInt();
        int w_ = settings.value("statistic_width").toInt();
        int h_ = settings.value("statistic_height").toInt();
        setGeometry(x_, y_, w_, h_);
    }
    else
    {
        QList<int> sizes;
        sizes.append(9999);
        sizes.append(1);
        sizes.append(9999);
        ui->splitter->setSizes(sizes);
    }

}

Statistic::~Statistic()
{
    delete ui;
}

void Statistic::fillForm()
{
    QString date = ui->calendar->selectedDate().toString("yyyy.MM.dd");

    editable = false;
    QSqlQuery query, query1;
    query.prepare("SELECT z.description, per.begin, per.end, per.id_task, per.id_period  FROM Periods per LEFT OUTER JOIN Tasks z ON per.id_task=z.id_task WHERE per.date = :date ORDER BY per.id_period DESC");
    query.bindValue(":date", date);
    query.exec();
    ui->periods->clear();
    ui->periods->setHorizontalHeaderLabels(QStringList() << "Задача" << "Начало" << "Конец");
    periods.clear();

    int row=0;

    int rowCount=0;
    while (query.next()) rowCount++;
    ui->periods->setRowCount(rowCount);
    query.seek(-1);

    while (query.next())
    {

        QTableWidgetItem * itm = new QTableWidgetItem;
        if (query.value("description").toString() == "")
        {
            itm->setText("Незаполненная задача");
        }
        else
        {
            itm->setText(query.value("description").toString().split("\n")[0]);
        }
        ui->periods->setItem(row,0,itm);

        itm = new QTableWidgetItem;
        itm->setText(query.value("begin").toString());
        ui->periods->setItem(row,1,itm);

        itm = new QTableWidgetItem;
        itm->setText(query.value("end").toString());
        ui->periods->setItem(row,2,itm);
        periods.append(QStringList() << query.value("description").toString() << query.value("begin").toString()
        <<query.value("end").toString() <<query.value("id_task").toString() <<query.value("id_period").toString());
        row++;
    }
    ui->periods->horizontalHeader()->resizeSection(0,300);

    int hh=0, mm=0;
    query.clear();
    ui->tasks->clear();
    ui->tasks->setHorizontalHeaderLabels(QStringList() << "Задача" << "Время" << "Всего");

    query.prepare("SELECT t.id_task, t.description FROM Periods p LEFT OUTER JOIN Tasks t ON t.id_task=p.id_task where p.date = :date GROUP BY t.id_task, t.description ORDER BY p.begin");
    query.bindValue(":date", date);
    query.exec();

    rowCount=0;
    while (query.next()) rowCount++;
    ui->tasks->setRowCount(rowCount+1);
    query.seek(-1);

    tasks.clear();
    row =0;
    while (query.next())
    {
//        qDebug() << query.value("id_task").toString() + " " + query.value("description").toString();
        int hour=0, min=0, hour_gen=0, min_gen=0;
        query1.prepare("SELECT date, begin, end FROM Periods WHERE id_task=:id_task");
        query1.bindValue(":id_task", query.value("id_task").toInt());
        if (!query1.exec()) qDebug() << "Не удалось заполнить задачи";
        while (query1.next())
        {
            int h = query1.value("end").toString().left(2).toInt() - query1.value("begin").toString().left(2).toInt();
            int m = query1.value("end").toString().right(2).toInt() - query1.value("begin").toString().right(2).toInt();
            if (m<0)
            {
                m+=60;
                h--;
            }
            if (query1.value("date").toString()==date)
            {
                hour+= h;
                min+= m;
                hh+=h;
                mm+=m;
            }
            hour_gen+= h;
            min_gen+= m;

        }
        hour+= min/60;
        min = min%60;
        hour_gen+= min_gen/60;
        min_gen = min_gen%60;

        QTableWidgetItem * itm = new QTableWidgetItem;
        if (query.value("description").toString() == "")
        {
            itm->setText("Незаполненная задача");
        }
        else
        {
            itm->setText(query.value("description").toString().split("\n")[0]);
        }
        ui->tasks->setItem(row,0,itm);

        itm = new QTableWidgetItem;
        itm->setText(hmToTime(hour,min));
        ui->tasks->setItem(row,1,itm);

        itm = new QTableWidgetItem;
        itm->setText(hmToTime(hour_gen, min_gen));
        ui->tasks->setItem(row,2,itm);
        tasks.append(QStringList() << query.value("description").toString() << query.value("id_task").toString());
        row++;
    }
    hh+= mm/60;
    mm = mm%60;

    QFont f("Times", 10, QFont::Bold);

    QTableWidgetItem * itm = new QTableWidgetItem;
    itm->setFont(f);
    itm->setText("ОБЩЕЕ ВРЕМЯ");
    ui->tasks->setItem(row,0,itm);

    itm = new QTableWidgetItem;
    itm->setFont(f);
    itm->setText(hmToTime(hh,mm));
    ui->tasks->setItem(row,1,itm);
    ui->tasks->horizontalHeader()->resizeSection(0,300);
    editable = true;

    fillMetrics();

}

QString Statistic::hmToTime(int h, int m)
{
    QString str_h, str_m;
    str_h = QString::number(h);
    str_m = QString::number(m);
    if (str_h.length()==1) str_h = "0" + str_h;
    if (str_m.length()==1) str_m = "0" + str_m;
    return str_h + ":" + str_m;

}

void Statistic::deletePeriod(int row)
{
    if (periods.isEmpty()) return;

    QStringList lst = periods[row];
    QString id_period = lst[4];
    QString id_task = lst[3];

    QSqlQuery query;
    query.prepare("DELETE FROM Periods WHERE id_period=:id_period");
    query.bindValue(":id_period", id_period);
    query.exec();

    query.prepare("SELECT begin FROM Periods WHERE id_task=:id_task");
    query.bindValue(":id_task", id_task);
    query.exec();
    if (!query.next())
    {
        query.prepare("DELETE FROM Tasks WHERE id_task=:id_task");
        query.bindValue(":id_task", id_task);
        query.exec();
    }
    fillForm();
}

void Statistic::deleteTask(int row)
{
    if (tasks.isEmpty()) return;

    QStringList lst = tasks[row];

    QSqlQuery query;
    query.prepare("DELETE FROM Periods WHERE id_task=:id_task");
    query.bindValue(":id_task", lst[1]);
    query.exec();

    query.prepare("DELETE FROM Tasks WHERE id_task=:id_task");
    query.bindValue(":id_task", lst[1]);
    query.exec();

    fillForm();
}

void Statistic::fillMetrics()
{
    QString date = ui->calendar->selectedDate().toString("yyyy.MM.dd");

    auto curve = [=] (int mm) -> int
    {
        if (mm==0) return 0;
        return std::min(int(std::log2(mm)*3.5), mm);
    };

    auto acurve = [=] (int mm) -> int
    {
        if (mm==0) return 0;
        return std::max(int(std::pow(2, mm/3.5)), mm);
    };

    QSqlQuery query;
    query.prepare("SELECT "
                  "z.description, "
                  "per.begin, "
                  "per.end, "
                  "per.id_task, "
                  "per.id_period  "
                  "FROM Periods per "
                  "LEFT OUTER JOIN "
                  "Tasks z ON per.id_task=z.id_task "
                  "WHERE per.date = :date "
                  "ORDER BY per.id_period");
    query.bindValue(":date", date);
    query.exec();

    QList<int> _minutes;
    QStringList _tasks;
    QString _currentTask;
    QMap<QString,int> timeSwitching;
    int mmAll=0;

    while (query.next())
    {
        QString begin_hh, begin_mm, end_hh, end_mm;
        QString task = query.value("id_task").toString();

        begin_hh = query.value("begin").toString().left(2);
        begin_mm = query.value("begin").toString().right(2);

        end_hh = query.value("end").toString().left(2);
        end_mm = query.value("end").toString().right(2);

        int begin = begin_hh.toInt()*60 + begin_mm.toInt();
        int end = end_hh.toInt()*60 + end_mm.toInt();

        int delta = end-begin;
        mmAll+=delta;

        if(_currentTask!=task)
        {
            _currentTask=task;
            _tasks.append(task);
            _minutes.append(delta);
        }
        else
        {
            QList<int>::Iterator pastEl = --_minutes.end();
            *pastEl+= delta;
        }
        timeSwitching.insert(task,0);

    }

    int sumTimeSwitching=0;
    QList<int>::Iterator it_m = _minutes.begin();

    for (QStringList::Iterator it_t = _tasks.begin(); it_t!=_tasks.end(); it_t++)
    {
        QString task = *it_t;
        int mm = *it_m;
        qDebug() << "task" << task << mm;

        for (QString &key :timeSwitching.keys())
        {
            int _valueSwitching = timeSwitching[key];
            if (key==task)
            {
                timeSwitching[key] = curve(acurve(_valueSwitching)+mm);
                sumTimeSwitching+= timeSwitching[key]-_valueSwitching;
                qDebug() << "timeSwitching[key]" << task << timeSwitching[key];
            }
            else
            {
                timeSwitching[key]= std::max(0, _valueSwitching-curve(mm));
            }
        }
        it_m++;
    }
    qDebug() << "sumTimeSwitching"<< sumTimeSwitching;
    qDebug() << "mmAll"<< mmAll;

    float switching;
    if (mmAll==0) switching =0;
    else switching = int(float(sumTimeSwitching)/float(mmAll)*100);

    switching = switching/100;


    int minutesWorkDay;
    if (ui->calendar->selectedDate()==QDate::currentDate())
    {
        QTime time = QTime::currentTime();
        if (time.hour()>17 || time.hour()<9) minutesWorkDay = 480;
        else minutesWorkDay = (time.hour()-9)*60+ time.minute();
    }
    else minutesWorkDay = 480;

    float production;
    if (mmAll==0) production =0;
    else production = int(float(mmAll)/float(minutesWorkDay)*100);
    production = production/100;

    ui->metrics->setText("ВЫРАБОТКА: " + QString::number(production) + "\n" +
                "Индекс переключаемости: " + QString::number(switching));



}

void Statistic::closeEvent(QCloseEvent *event)
{
    QSettings settings;
    settings.setValue("splitterStatisticSizes", ui->splitter->saveState());
    settings.setValue("statistic_x", x());
    settings.setValue("statistic_y", y());

    hide();
    event->ignore();
}

void Statistic::on_calendar_clicked(const QDate &selectedDate)
{
    fillForm();
}

void Statistic::on_forward_clicked()
{
    ui->calendar->setSelectedDate(ui->calendar->selectedDate().addDays(1));
    fillForm();
}

void Statistic::on_back_clicked()
{
    ui->calendar->setSelectedDate(ui->calendar->selectedDate().addDays(-1));
    fillForm();
}

void Statistic::on_periods_cellChanged(int row, int column)
{
    if (!editable) return;

    QStringList lst = periods[row];
    QString begin = ui->periods->item(row,1)->text();
    QString end = ui->periods->item(row,2)->text();

    if (begin.count()!=5 || end.count()!=5) fillForm();

    bool hhok_b, mmok_b, hhok_e, mmok_e;
    int hh_b, mm_b, hh_e, mm_e;

    hh_b = begin.left(2).toInt(&hhok_b);
    mm_b = begin.right(2).toInt(&mmok_b);
    hh_e = end.left(2).toInt(&hhok_e);
    mm_e = end.right(2).toInt(&mmok_e);
    bool b = (begin[2]==QChar(':'));
    bool e = (end[2]==QChar(':'));

    if (
    !(hhok_b && mmok_b) ||
    !(hhok_e && mmok_e) ||
     (hh_b>23 || mm_b>59)||
     (hh_e>23 || mm_e>59)||
     (hh_b<0  || mm_b<0) ||
     (hh_e<0  || mm_e<0) ||
     !(b && e) ||
     ((hh_b*60+mm_b) > (hh_e*60+mm_e))
            )
    {
        fillForm();
        return;
    }

    QSqlQuery query;
    query.prepare("UPDATE Periods SET begin = :begin, end = :end WHERE id_period=:id_period");
    query.bindValue(":id_period", lst[4]);
    query.bindValue(":begin", begin);
    query.bindValue(":end", end);
    query.exec();
    periods[row][1] = begin;
    periods[row][2] = end;
    fillForm();

}

void Statistic::on_calendar_activated(const QDate &selectedDate)
{
    fillForm();
}

void Statistic::customMenuRequested(QPoint point)
{
    if (ui->tasks->hasFocus() && ui->tasks->currentRow()==ui->tasks->rowCount()-1) return; //ОБЩЕЕ ВРЕМЯ
    menu->move(QCursor::pos());
    menu->show();

}

void Statistic::deletePeriodOrTask()
{
    if(ui->periods->hasFocus()) deletePeriod(ui->periods->currentRow());
    else if (ui->tasks->hasFocus()) deleteTask(ui->tasks->currentRow());
}



void Statistic::on_tasks_cellChanged(int row, int column)
{
    if(!editable) return;
    fillForm();
}

void Statistic::hideEvent(QHideEvent *)
{
    QSettings settings;
    settings.setValue("splitterStatisticSizes", ui->splitter->saveState());
    settings.setValue("statistic_x", x());
    settings.setValue("statistic_y", y());
    settings.setValue("statistic_width", width());
    settings.setValue("statistic_height", height());
}

void Statistic::showEvent(QShowEvent *)
{
    SetForegroundWindow((HWND)Statistic::winId());
}
