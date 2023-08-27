#ifndef TIMECATEGORYS_H
#define TIMECATEGORYS_H

#include <QWidget>
#include <editTimecategory.h>
#include <QCloseEvent>
#include <QListWidgetItem>

namespace Ui {
class TimeCategorys;
}

class TimeCategorys : public QWidget
{
    Q_OBJECT

public:
    explicit TimeCategorys(QWidget *parent = nullptr);
    ~TimeCategorys();

private slots:


    void on_addTimeCategory_clicked();

    void on_timeCategorys_itemDoubleClicked(QListWidgetItem *);

private:
    Ui::TimeCategorys *ui;
    void fillForm();
    QStringList timeCategorys;
    EditTimeCategory *editTimeCategoryForm;
    void deleteCategory();

    // QWidget interface
protected:
    void showEvent(QShowEvent *);

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // TIMECATEGORYS_H
