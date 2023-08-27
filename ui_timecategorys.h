/********************************************************************************
** Form generated from reading UI file 'timecategorys.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIMECATEGORYS_H
#define UI_TIMECATEGORYS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TimeCategorys
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *addTimeCategory;
    QSpacerItem *horizontalSpacer;
    QListWidget *timeCategorys;

    void setupUi(QWidget *TimeCategorys)
    {
        if (TimeCategorys->objectName().isEmpty())
            TimeCategorys->setObjectName(QStringLiteral("TimeCategorys"));
        TimeCategorys->resize(400, 300);
        verticalLayout = new QVBoxLayout(TimeCategorys);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        addTimeCategory = new QPushButton(TimeCategorys);
        addTimeCategory->setObjectName(QStringLiteral("addTimeCategory"));

        horizontalLayout->addWidget(addTimeCategory);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        timeCategorys = new QListWidget(TimeCategorys);
        timeCategorys->setObjectName(QStringLiteral("timeCategorys"));

        verticalLayout->addWidget(timeCategorys);


        retranslateUi(TimeCategorys);

        QMetaObject::connectSlotsByName(TimeCategorys);
    } // setupUi

    void retranslateUi(QWidget *TimeCategorys)
    {
        TimeCategorys->setWindowTitle(QApplication::translate("TimeCategorys", "\320\232\320\260\321\202\320\265\320\263\320\276\321\200\320\270\320\270 \321\202\321\200\321\203\320\264\320\276\320\265\320\274\320\272\320\276\321\201\321\202\320\270", 0));
        addTimeCategory->setText(QApplication::translate("TimeCategorys", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", 0));
    } // retranslateUi

};

namespace Ui {
    class TimeCategorys: public Ui_TimeCategorys {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMECATEGORYS_H
