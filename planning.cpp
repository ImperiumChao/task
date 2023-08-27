#include "planning.h"
#include "ui_planning.h"
#include <QCheckBox>
#include <QTableWidgetItem>
#include <QHBoxLayout>
#include <QSettings>
#include <QTextEdit>
#include <QSqlQuery>
#include <QListWidgetItem>
#include <QDebug>
#include <QInputDialog>
#include <QMessageBox>
#include <QSqlError>
#include "addtask.h"
#include <QShortcut>
#include <QMap>
#include <QComboBox>



Planning::Planning(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Planning)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    connect(this, &Planning::needAddTask, this, &Planning::addTask);

    QShortcut* shortcut = new QShortcut(this);
    shortcut->setKey(Qt::Key_Escape);
    connect(shortcut, &QShortcut::activated, this, &QWidget::hide);

    shortcut = new QShortcut(this);
    shortcut->setKey(Qt::Key_Delete);
    connect(shortcut, &QShortcut::activated, this, &Planning::on_deleteTask_clicked);

    fillProjects();


    QSettings settings;

    if (settings.contains("planning_x") && settings.contains("planning_width"))
    {
        int x_ = settings.value("planning_x").toInt();
        int y_ = settings.value("planning_y").toInt();
        int w_ = settings.value("planning_width").toInt();
        int h_ = settings.value("planning_height").toInt();
        setGeometry(x_, y_, w_, h_);
    }

    QList<int> sizes;
    sizes.append(1);
    sizes.append(99999);

    ui->splitter_2->setSizes(sizes);
    ui->splitter->setSizes(sizes);

//    ui->splitter->restoreState(settings.value("splitterPlanningSizes").toByteArray());
}

Planning::~Planning()
{
    delete ui;
}

QWidget *Planning::getCheckWidgetTable(QString id_task, bool completed)
{
    QWidget * widget = new QWidget;
    QHBoxLayout * layout = new QHBoxLayout;
    QCheckBox * checkbox = new QCheckBox(widget);

    widget->setLayout(layout);
    layout->setMargin(0);
    layout->addStretch();
    layout->addWidget(checkbox);
    layout->addStretch();
    checkbox->setChecked(completed);
    checkbox->setProperty("id_task", id_task);
    connect(checkbox, &QCheckBox::stateChanged, this, &Planning::checkTaskChanged);

    return widget;
}

QTextEdit *Planning::getTextEditTable(QString id_task, QString text, bool completed, int row)
{
    QTextEdit * te = new QTextEdit;
    te->setFixedHeight(50);
    if (completed)
    {
        te->setText("<html><s>" + text + "</s></html>");
        te->setReadOnly(true);
    }
    else te->setText(text);

    te->setStyleSheet("QTextEdit {border-width: 0px, 0px, 0px, 0px; border-style: solid}");
    te->setProperty("id_task", QVariant(id_task));
    te->setProperty("row", QVariant(row));

    int countString = (text.count("\n")+1);
    int h;
    if (countString==1) h = 32;
    else h = 27 * countString;

    te->setFixedHeight(h);
    ui->tasks->setRowHeight(row, h+1);

    connect(te, &QTextEdit::textChanged, this, &Planning::textTaskChanged);
    return te;
}

QComboBox *Planning::getComboBoxTimeCategory(QString id_task, QString id_category)
{
    QComboBox *cb = new QComboBox;
    int index=0, i=0;
    for(QMap<QString, QString> category : timeCategorys)
    {
        cb->addItem(category["name"]);
        if (category["id_category"]==id_category) index = i;
        i++;
    }
    cb->setCurrentIndex(index);
    cb->setProperty("id_task", QVariant(id_task));

    connect(cb, SIGNAL(currentIndexChanged(int)), this, SLOT(timeCategoryChanged(int)));

    return cb;
}

void Planning::fillMetrics()
{
    QString id_project = projects[ui->projects->currentRow()];

    QSqlQuery query;
    query.prepare("SELECT "
                  "Scheduled_tasks.end, "
                  "Time_categorys.min_from, "
                  "Time_categorys.min_to "
                  "FROM Scheduled_tasks LEFT JOIN Time_categorys ON Scheduled_tasks.id_category=Time_categorys.id_category "
                  "WHERE id_project=:id_project AND "
                 "(begin<=:selectedDate AND (end IS NULL OR (:showCompletedTasks  AND end=:selectedDate))) "
                  "ORDER BY sequence_number");

    query.bindValue(":id_project", id_project);
    query.bindValue(":selectedDate", ui->calendar->selectedDate().toString("yyyy.MM.dd"));
    query.bindValue(":showCompletedTasks", ui->showCompletedTasks->isChecked());

    if (!query.exec()) return;

    float min=0, max=0, mean=0;
    while (query.next())
    {
        bool comletedTask = !query.value("end").isNull();

        if (!comletedTask)
        {
            int min_from = query.value("min_from").toInt();
            int min_to = query.value("min_to").toInt();
            min+=min_from;
            max+=min_to;
            mean+=(min_to-min_from)/2;
        }
    }

    int widthTable = ui->tasks->width();
    ui->tasks->setColumnWidth(0, 100);
    ui->tasks->setColumnWidth(1, widthTable-250);

    QString minHours = QString::number(min/60, 'g', 2);
    QString maxHours = QString::number(max/60, 'g', 2);
    QString meanHours = QString::number(mean/60, 'g', 2);

    ui->workload->setText(
                QString("ЗАГРУЖЕННОСТЬ: %1 ч. (от %2 ч. до %3 ч.)")
                .arg(meanHours)
                .arg(minHours)
                .arg(maxHours));
}

void Planning::textTaskChanged()
{
    QTextEdit * te = qobject_cast<QTextEdit *>(sender());

    QString text = te->toPlainText();
    QString id_task = te->property("id_task").toString();
    int row = te->property("row").toInt();

    qDebug() << id_task;

    QSqlQuery query;
    query.prepare("UPDATE Scheduled_tasks SET text_tasks=:text WHERE id_task=:id");
    query.bindValue(":text", te->toPlainText());
    query.bindValue(":id", id_task);
    query.exec();

    int countString = (text.count("\n")+1);
    int h;
    if (countString==1) h = 32;
    else h = 27 * countString;

    te->setFixedHeight(h);
    ui->tasks->setRowHeight(row, h+1);

    connect(te, &QTextEdit::cursorPositionChanged, this, [=]() {qDebug() << "cursorPositionChanged";});
}

void Planning::checkTaskChanged()
{
    QCheckBox * ch = qobject_cast<QCheckBox *>(sender());

    QString id_task = ch->property("id_task").toString();
    bool completed = ch->isChecked();



    QSqlQuery query;
    query.prepare("UPDATE Scheduled_tasks SET end=:end WHERE id_task=:id");

    if (completed) query.bindValue(":end", ui->calendar->selectedDate().toString("yyyy.MM.dd"));
    else query.bindValue(":end", QVariant(QVariant::String));

    query.bindValue(":id", id_task);
    query.exec();

    fillTasks();
}

void Planning::timeCategoryChanged(int index)
{

    QComboBox * cb = qobject_cast<QComboBox *>(sender());
    QString id_task = cb->property("id_task").toString();

    QString id_category = timeCategorys[index]["id_category"];

    QSqlQuery query;
    query.prepare("UPDATE Scheduled_tasks SET id_category=:id_category WHERE id_task=:id_task");
    query.bindValue(":id_category", id_category);
    query.bindValue(":id_task", id_task);
    query.exec();
//    qDebug() << query.boundValues();
    fillMetrics();
}

void Planning::fillProjects()
{
    projects.clear();
    ui->projects->clear(); 

    QSqlQuery query;
    query.prepare("SELECT id_project, name FROM projects ORDER BY sequence_number");

    if (!query.exec()) return;

    while (query.next())
    {
        QString nameProject = query.value("name").toString();
        ui->projects->addItem(nameProject);
        projects.append(query.value("id_project").toString());
    }

    if (!projects.isEmpty()) ui->projects->setCurrentRow(0);

}

void Planning::fillTasks()
{
    qDebug() << "fillTasks";

    updateTimeCategorys();

    ui->tasks->clear();
    ui->tasks->setRowCount(0);
    ui->tasks->setColumnCount(3);
    ui->tasks->setHorizontalHeaderLabels(QStringList() << "" << "Задача" << "Временные затраты");
    if (projects.isEmpty()) return;

    QString id_project = projects[ui->projects->currentRow()];

    QSqlQuery query;
    query.prepare("SELECT "
                  "id_task, "
                  "text_tasks, "
                  "end, "
                  "id_category "
                  "FROM Scheduled_tasks "
                  "WHERE id_project=:id_project AND "
                 "(begin<=:selectedDate AND (end IS NULL OR (:showCompletedTasks  AND end=:selectedDate))) "
                  "ORDER BY sequence_number");

    query.bindValue(":id_project", id_project);
    query.bindValue(":selectedDate", ui->calendar->selectedDate().toString("yyyy.MM.dd"));
    query.bindValue(":showCompletedTasks", ui->showCompletedTasks->isChecked());

    if (!query.exec()) return;

    int size=0;
    while (query.next()) size++;
    query.seek(-1);

    ui->tasks->setRowCount(size);
    int row=0;
    while (query.next())
    {
        bool comletedTask = !query.value("end").isNull() ;

        QString text = query.value("text_tasks").toString();
        QString id_task = query.value("id_task").toString();
        QString id_category = query.value("id_category").toString();

        ui->tasks->setCellWidget(row, 0, getCheckWidgetTable(id_task, comletedTask));
        ui->tasks->setCellWidget(row, 1, getTextEditTable(id_task, text, comletedTask, row));
        ui->tasks->setCellWidget(row, 2, getComboBoxTimeCategory(id_task, id_category));
        row++;
    }

    int widthTable = ui->tasks->width();
    ui->tasks->setColumnWidth(0, 100);
    ui->tasks->setColumnWidth(1, widthTable-250);

    fillMetrics();

    auto header = ui->tasks->horizontalHeader();
    connect(header, &QHeaderView::sectionDoubleClicked, [=](int logicalIndex){
        QString text = ui->tasks->horizontalHeaderItem(logicalIndex)->text();
       qDebug() << logicalIndex << text;
    });

}

void Planning::updateTimeCategorys()
{
    QSqlQuery query;
    query.prepare("SELECT id_category, name FROM Time_categorys ORDER BY defaultValue DESC");
    query.exec();

    timeCategorys.clear();
    while (query.next())
    {
        QMap<QString, QString> category;
        category["id_category"] = query.value("id_category").toString();
        category["name"] = query.value("name").toString();
        timeCategorys.append(category);
    }
}

void Planning::addTask(QString id_project)
{
    at->show();
}

void Planning::closeEvent(QCloseEvent *event)
{
    event->ignore();
    hide();
}

void Planning::hideEvent(QHideEvent *)
{
    qDebug() << x() << y();
    QSettings settings;
//    settings.setValue("splitterPlanningSizes", ui->splitter->saveState());
    settings.setValue("planning_x", x());
    settings.setValue("planning_y", y());
    settings.setValue("planning_width", width());
    settings.setValue("planning_height", height());
}

void Planning::showEvent(QShowEvent *)
{
    ui->calendar->setSelectedDate(QDate::currentDate());
    fillTasks();
}

void Planning::on_addProject_clicked()
{
    QString nameProject = QInputDialog::getText(this,"Новый проект", "Название проекта");

    if (nameProject.isEmpty()) return;

    QSqlQuery query;

    int sequence_number = 1;
    query.prepare("SELECT max(sequence_number) AS sequence_number FROM Projects");
    query.exec();
    if (query.next())
    {
        sequence_number = query.value("sequence_number").toInt();
    }

    query.prepare("INSERT INTO Projects(sequence_number, name) VALUES (:sequence_number, :name)");
    query.bindValue(":sequence_number", ++sequence_number);
    query.bindValue(":name", nameProject);
    query.exec();

    fillProjects();
}

void Planning::on_deleteProject_clicked()
{
    int currentRow = ui->projects->currentRow();
    if (currentRow==-1) return;

    QMessageBox::StandardButton answer;
    answer = QMessageBox::question(this, "Удаление проекта", "Вы уверены, что хотите удалить проект? Все задачи будут удалены.");
    if (answer!=QMessageBox::Yes) return;

    QSqlQuery query;
    query.prepare("DELETE FROM Projects WHERE id_project=:id_project");
    query.bindValue(":id_project", projects[currentRow]);
    query.exec();

    query.prepare("DELETE FROM Scheduled_tasks WHERE id_project=:id_project");
    query.bindValue(":id_project", projects[currentRow]);
    query.exec();

    fillProjects();

}

void Planning::on_orderProjectUp_clicked()
{
    int currentRow = ui->projects->currentRow();
    if (currentRow==-1) return;

    QString id_project = projects[currentRow];

    QSqlQuery query;
    query.prepare("SELECT sequence_number FROM Projects WHERE id_project=:id_project");
    query.bindValue(":id_project", id_project);
    query.exec();
    query.next();
    int sequence_number = query.value("sequence_number").toInt();

    query.prepare("SELECT id_project, sequence_number FROM Projects WHERE sequence_number < :sequence_number ORDER BY sequence_number DESC LIMIT 1");
    query.bindValue(":sequence_number", sequence_number);
    query.exec();

    if (!query.next()) return;

    int sequence_number__ = query.value("sequence_number").toInt();
    QString id_project__ = query.value("id_project").toString();

    query.prepare("BEGIN TRANSACTION");
    query.exec();

    query.prepare("UPDATE Projects SET sequence_number = :sequence_number WHERE id_project=:id_project");
    query.bindValue(":sequence_number", sequence_number__);
    query.bindValue(":id_project", id_project);
    query.exec();

    query.prepare("UPDATE Projects SET sequence_number = :sequence_number WHERE id_project=:id_project");
    query.bindValue(":sequence_number", sequence_number);
    query.bindValue(":id_project", id_project__);
    query.exec();

    query.prepare("END TRANSACTION");
    query.exec();

    fillProjects();
    ui->projects->setCurrentRow(currentRow-1);
}

void Planning::on_orderProjectDown_clicked()
{
    int currentRow = ui->projects->currentRow();
    if (currentRow==-1) return;

    QString id_project = projects[currentRow];

    QSqlQuery query;
    query.prepare("SELECT sequence_number FROM Projects WHERE id_project=:id_project");
    query.bindValue(":id_project", id_project);
    query.exec();
    query.next();
    int sequence_number = query.value("sequence_number").toInt();

    query.prepare("SELECT id_project, sequence_number FROM Projects WHERE sequence_number > :sequence_number ORDER BY sequence_number LIMIT 1");
    query.bindValue(":sequence_number", sequence_number);
    query.exec();

    if (!query.next()) return;

    int sequence_number__ = query.value("sequence_number").toInt();
    QString id_project__ = query.value("id_project").toString();

    query.prepare("BEGIN TRANSACTION");
    query.exec();

    query.prepare("UPDATE Projects SET sequence_number = :sequence_number WHERE id_project=:id_project");
    query.bindValue(":sequence_number", sequence_number__);
    query.bindValue(":id_project", id_project);
    query.exec();

    query.prepare("UPDATE Projects SET sequence_number = :sequence_number WHERE id_project=:id_project");
    query.bindValue(":sequence_number", sequence_number);
    query.bindValue(":id_project", id_project__);
    query.exec();

    query.prepare("END TRANSACTION");
    query.exec();

    fillProjects();
    ui->projects->setCurrentRow(currentRow+1);
}

void Planning::on_calendar_activated(const QDate &date)
{
    fillTasks();
}

void Planning::on_projects_currentRowChanged(int currentRow)
{
    fillTasks();
}

void Planning::on_calendar_clicked(const QDate &date)
{
    fillTasks();
}

void Planning::on_showCompletedTasks_stateChanged(int arg1)
{
    fillTasks();
}

void Planning::on_addTask_clicked()
{
    if (ui->projects->currentRow()==-1) return;
    QString id_project = projects[ui->projects->currentRow()];

    QSqlQuery query;

    int sequence_number = 1;
    query.prepare("SELECT max(sequence_number) AS sequence_number FROM Scheduled_tasks WHERE id_project=:id_project");
    query.bindValue(":id_project", id_project);
    if (!query.exec()) return;

    if (query.next())
    {
        sequence_number = query.value("sequence_number").toInt();
    }

    query.prepare("INSERT INTO Scheduled_tasks(id_project, text_tasks, sequence_number, begin, id_category) VALUES (:id_project, :text_tasks, :sequence_number, :begin, (SELECT id_category FROM Time_categorys WHERE defaultValue = 1))");
    query.bindValue(":id_project", id_project);
    query.bindValue(":text_tasks", "");
    query.bindValue(":sequence_number", ++sequence_number);
    query.bindValue(":begin", ui->calendar->selectedDate().toString("yyyy.MM.dd"));
    if (!query.exec()) return;

    query.prepare("SELECT id_task FROM Scheduled_tasks WHERE id_project=:id_project ORDER BY sequence_number DESC");
    query.bindValue(":id_project", id_project);
    if (!query.exec()) return;

    query.next();
    QString id_task = query.value("id_task").toString();

    int row = ui->tasks->rowCount();
    QTextEdit * te = getTextEditTable(id_task, "", false, row);
    ui->tasks->setRowCount(row+1);
    ui->tasks->setCellWidget(row, 0, getCheckWidgetTable(id_task, false));
    ui->tasks->setCellWidget(row, 1, te);
    te->setFocus();
}

void Planning::on_orderTaskUp_clicked()
{
    int currentRow = ui->tasks->currentRow();
    if (currentRow < 1) return;

    QString id_task = ui->tasks->cellWidget(currentRow,1)->property("id_task").toString();
    QString id_task__ = ui->tasks->cellWidget(currentRow-1,1)->property("id_task").toString();

    QSqlQuery query;
    query.prepare("SELECT sequence_number FROM Scheduled_tasks WHERE id_task=:id_task");
    query.bindValue(":id_task", id_task);
    query.exec();
    query.next();
    int sequence_number = query.value("sequence_number").toInt();

    query.bindValue(":id_task", id_task__);
    query.exec();
    query.next();
    int sequence_number__ = query.value("sequence_number").toInt();


    query.prepare("BEGIN TRANSACTION");
    query.exec();

    query.prepare("UPDATE Scheduled_tasks SET sequence_number = :sequence_number WHERE id_task=:id_task");
    query.bindValue(":sequence_number", sequence_number__);
    query.bindValue(":id_task", id_task);
    query.exec();

    query.prepare("UPDATE Scheduled_tasks SET sequence_number = :sequence_number WHERE id_task=:id_task");
    query.bindValue(":sequence_number", sequence_number);
    query.bindValue(":id_task", id_task__);
    query.exec();

    query.prepare("END TRANSACTION");
    query.exec();

    fillTasks();
    ui->tasks->setCurrentCell(currentRow-1,0);
}

void Planning::on_orderTaskDown_clicked()
{
    int currentRow = ui->tasks->currentRow();
    if (currentRow==-1 || ui->tasks->rowCount()-1==currentRow) return;

    QString id_task = ui->tasks->cellWidget(currentRow,1)->property("id_task").toString();
    QString id_task__ = ui->tasks->cellWidget(currentRow+1,1)->property("id_task").toString();

    QSqlQuery query;
    query.prepare("SELECT sequence_number FROM Scheduled_tasks WHERE id_task=:id_task");
    query.bindValue(":id_task", id_task);
    query.exec();
    query.next();
    int sequence_number = query.value("sequence_number").toInt();

    query.bindValue(":id_task", id_task__);
    query.exec();
    query.next();
    int sequence_number__ = query.value("sequence_number").toInt();

    query.prepare("BEGIN TRANSACTION");
    query.exec();

    query.prepare("UPDATE Scheduled_tasks SET sequence_number = :sequence_number WHERE id_task=:id_task");
    query.bindValue(":sequence_number", sequence_number__);
    query.bindValue(":id_task", id_task);
    query.exec();

    query.prepare("UPDATE Scheduled_tasks SET sequence_number = :sequence_number WHERE id_task=:id_task");
    query.bindValue(":sequence_number", sequence_number);
    query.bindValue(":id_task", id_task__);
    query.exec();

    query.prepare("END TRANSACTION");
    query.exec();

    fillTasks();
    ui->tasks->setCurrentCell(currentRow+1,0);
}

void Planning::on_deleteTask_clicked()
{
    int currentRow = ui->tasks->currentRow();
    if (currentRow==-1) return;

    QMessageBox::StandardButton answer;
    answer = QMessageBox::question(this, "Удаление задачи", "Вы уверены, что хотите удалить задачу?");
    if (answer!=QMessageBox::Yes) return;

    QString id_task = ui->tasks->cellWidget(currentRow, 1)->property("id_task").toString();

    QSqlQuery query;
    query.prepare("DELETE FROM Scheduled_tasks WHERE id_task=:id_task");
    query.bindValue(":id_task", id_task);
    query.exec();

    fillTasks();
}

void Planning::on_projects_itemDoubleClicked(QListWidgetItem *item)
{
    QString nameProject = QInputDialog::getText(this,"Проект", "Название проекта",QLineEdit::Normal, item->text());
    if (nameProject.isEmpty()) return;

    QString id_project = projects[ui->projects->currentRow()];

    QSqlQuery query;
    query.prepare("UPDATE Projects SET name = :name WHERE id_project=:id_project");
    query.bindValue(":name", nameProject);
    query.bindValue(":id_project", id_project);
    query.exec();

    fillProjects();
}
