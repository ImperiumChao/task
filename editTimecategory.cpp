#include "EditTimeCategory.h"
#include "ui_EditTimeCategory.h"
#include <QSqlQuery>

EditTimeCategory::EditTimeCategory(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditTimeCategory)
{
    ui->setupUi(this);
    ui->from->setValidator(new QIntValidator(ui->from));
    ui->to->setValidator(new QIntValidator(ui->to));

    currentIdCategory = "";
}

EditTimeCategory::~EditTimeCategory()
{
    delete ui;
}

void EditTimeCategory::on_buttonBox_accepted()
{
    int defaultValue;
    if (ui->defaultValue->isChecked()) defaultValue = 1;
    else defaultValue = 0;

    QSqlQuery query;
    if (!currentIdCategory.isEmpty())
    {
        query.prepare("UPDATE Time_categorys SET name=:name, min_from=:min_from, min_to=:min_to, defaultValue=:defaultValue WHERE id_category=:id_category");
        query.bindValue(":name", ui->name->text());
        query.bindValue(":min_from", ui->from->text().toInt());
        query.bindValue(":min_to", ui->to->text().toInt());
        query.bindValue(":defaultValue", defaultValue);
        query.bindValue(":id_category", currentIdCategory);
        query.exec();
    }
    else
    {
        query.prepare("INSERT INTO Time_categorys(name, min_from, min_to, defaultValue) VALUES(:name, :min_from, :min_to, :defaultValue)");
        query.bindValue(":name", ui->name->text());
        query.bindValue(":min_from", ui->from->text().toInt());
        query.bindValue(":min_to", ui->to->text().toInt());
        query.bindValue(":defaultValue", defaultValue);
        query.exec();

        if (defaultValue ==1)
        {
            query.prepare("SELECT last_insert_rowid()");
            query.exec();
            query.next();
            QString id_timeCatecory = query.value(0).toString();

            query.prepare("UPDATE Time_categorys SET defaultValue = 0 WHERE id_category<>:id_category");
            query.bindValue(":id_category", id_timeCatecory);
            query.exec();
        }
        currentIdCategory.clear();
    }

    emit categoryEdited();

    hide();
}

void EditTimeCategory::on_buttonBox_rejected()
{
    hide();
}

void EditTimeCategory::showEvent(QShowEvent *)
{
    if (currentIdCategory.isEmpty())
    {
        ui->name->clear();
        ui->from->clear();
        ui->to->clear();
        ui->defaultValue->setChecked(false);
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT name, min_from, min_to, defaultValue  FROM Time_categorys WHERE id_category = :id_category");
    query.bindValue(":id_category", currentIdCategory);
    query.exec();

    query.next();

    ui->name->setText(query.value("name").toString());
    ui->from->setText(query.value("min_from").toString());
    ui->to->setText(query.value("min_to").toString());
    ui->defaultValue->setChecked(query.value("defaultValue").toBool());


}
