#include "timecategorys.h"
#include "ui_timecategorys.h"
#include <QSqlQuery>
#include <QShortcut>
#include <QMessageBox>
#include <QDebug>

TimeCategorys::TimeCategorys(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimeCategorys)
{
    ui->setupUi(this);
    editTimeCategoryForm = new EditTimeCategory;
    connect(editTimeCategoryForm, &EditTimeCategory::categoryEdited, this, &TimeCategorys::fillForm);

    QShortcut* shortcut = new QShortcut(this);
    shortcut->setKey(Qt::Key_Escape);
    connect(shortcut, &QShortcut::activated, this, &QWidget::hide);

    shortcut = new QShortcut(this);
    shortcut->setKey(Qt::Key_Delete);
    connect(shortcut, &QShortcut::activated, this, &TimeCategorys::deleteCategory);
}

TimeCategorys::~TimeCategorys()
{
    delete ui;
}

void TimeCategorys::fillForm()
{
    ui->timeCategorys->clear();
    timeCategorys.clear();

    QFont fontForDefaultCategory("Times", 10, QFont::Bold);
    QFont fontForOtherCategorys("Times", 10);

    QSqlQuery query;
    query.prepare("SELECT id_category, name, min_from, min_to, defaultValue  FROM Time_categorys ORDER BY defaultValue DESC");
    query.exec();

    timeCategorys.clear();
    while (query.next())
    {
        bool defaultValue = query.value("defaultValue").toBool();

        QString id_category = query.value("id_category").toString();
        QString nameCategory = query.value("name").toString();
        QString min_from = query.value("min_from").toString();
        QString min_to = query.value("min_to").toString();

        nameCategory += QString(" (%1 - %2)").arg(min_from).arg(min_to);

        QListWidgetItem *item = new QListWidgetItem;
        item->setText(nameCategory);

        if (defaultValue) item->setFont(fontForDefaultCategory);
        else item->setFont(fontForOtherCategorys);

        ui->timeCategorys->addItem(item);
        timeCategorys.append(id_category);
    }
}

void TimeCategorys::deleteCategory()
{
    int currentRow = ui->timeCategorys->currentRow();
    if (currentRow==-1) return;

    QMessageBox::StandardButton answer;
    answer = QMessageBox::question(this, "Удаление категории трудоемкости", "Вы уверены, что хотите удалить категорию трудоемкости?");
    if (answer!=QMessageBox::Yes) return;

    QString id_category = timeCategorys[currentRow];

    QSqlQuery query;
    query.prepare("SELECT "
                  "id_task"
                  "FROM Scheduled_tasks "
                  "WHERE id_category=:id_category");

    query.bindValue(":id_category", id_category);
    query.exec();

//    qDebug() << ui->timeCategorys->currentRow();

    if(query.next())
    {
       QMessageBox::warning(this, "", "Уже есть задачи, у которых установлена эта категория. Удаление невозможно");
       return;
    }

    query.prepare("DELETE FROM Time_categorys WHERE id_category=:id_category");
    query.bindValue(":id_category", id_category);
    query.exec();
    fillForm();

}

void TimeCategorys::showEvent(QShowEvent *)
{
    fillForm();
}

void TimeCategorys::closeEvent(QCloseEvent *event)
{
    event->ignore();
    hide();
}



void TimeCategorys::on_addTimeCategory_clicked()
{
    editTimeCategoryForm->show();
}

void TimeCategorys::on_timeCategorys_itemDoubleClicked(QListWidgetItem *)
{
    editTimeCategoryForm->currentIdCategory = timeCategorys[ui->timeCategorys->currentRow()];
    editTimeCategoryForm->show();
}
