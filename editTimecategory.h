#ifndef EDITTIMECATEGORY_H
#define EDITTIMECATEGORY_H

#include <QWidget>

namespace Ui {
class EditTimeCategory;
}

class EditTimeCategory : public QWidget
{
    Q_OBJECT

public:
    explicit EditTimeCategory(QWidget *parent = nullptr);
    ~EditTimeCategory();
    QString currentIdCategory;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::EditTimeCategory *ui;


signals:
    void categoryEdited();

    // QWidget interface
protected:
    void showEvent(QShowEvent *);
};

#endif // ADDTIMECATEGORY_H
