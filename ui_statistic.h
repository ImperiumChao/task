/********************************************************************************
** Form generated from reading UI file 'statistic.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATISTIC_H
#define UI_STATISTIC_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Statistic
{
public:
    QHBoxLayout *horizontalLayout_2;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QTableWidget *periods;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QCalendarWidget *calendar;
    QLabel *metrics;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QPushButton *back;
    QSpacerItem *horizontalSpacer;
    QPushButton *forward;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_2;
    QTableWidget *tasks;

    void setupUi(QWidget *Statistic)
    {
        if (Statistic->objectName().isEmpty())
            Statistic->setObjectName(QStringLiteral("Statistic"));
        Statistic->resize(1560, 573);
        horizontalLayout_2 = new QHBoxLayout(Statistic);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetMinimumSize);
        splitter = new QSplitter(Statistic);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetMaximumSize);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(label);

        periods = new QTableWidget(layoutWidget);
        if (periods->columnCount() < 3)
            periods->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        periods->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        periods->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        periods->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        periods->setObjectName(QStringLiteral("periods"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(periods->sizePolicy().hasHeightForWidth());
        periods->setSizePolicy(sizePolicy1);
        periods->setMinimumSize(QSize(0, 0));
        periods->setAlternatingRowColors(true);
        periods->horizontalHeader()->setStretchLastSection(true);

        verticalLayout_2->addWidget(periods);

        splitter->addWidget(layoutWidget);
        layoutWidget1 = new QWidget(splitter);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        calendar = new QCalendarWidget(layoutWidget1);
        calendar->setObjectName(QStringLiteral("calendar"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(calendar->sizePolicy().hasHeightForWidth());
        calendar->setSizePolicy(sizePolicy2);
        calendar->setMinimumSize(QSize(0, 0));
        calendar->setMaximumSize(QSize(16777215, 16777215));
        calendar->setMouseTracking(false);
        calendar->setGridVisible(false);

        verticalLayout->addWidget(calendar);

        metrics = new QLabel(layoutWidget1);
        metrics->setObjectName(QStringLiteral("metrics"));

        verticalLayout->addWidget(metrics);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetMaximumSize);
        back = new QPushButton(layoutWidget1);
        back->setObjectName(QStringLiteral("back"));
        QSizePolicy sizePolicy3(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(back->sizePolicy().hasHeightForWidth());
        back->setSizePolicy(sizePolicy3);

        horizontalLayout->addWidget(back);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        forward = new QPushButton(layoutWidget1);
        forward->setObjectName(QStringLiteral("forward"));
        sizePolicy3.setHeightForWidth(forward->sizePolicy().hasHeightForWidth());
        forward->setSizePolicy(sizePolicy3);

        horizontalLayout->addWidget(forward);


        verticalLayout->addLayout(horizontalLayout);

        splitter->addWidget(layoutWidget1);
        layoutWidget2 = new QWidget(splitter);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        verticalLayout_3 = new QVBoxLayout(layoutWidget2);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setSizeConstraint(QLayout::SetMaximumSize);
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget2);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);

        verticalLayout_3->addWidget(label_2);

        tasks = new QTableWidget(layoutWidget2);
        if (tasks->columnCount() < 3)
            tasks->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tasks->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tasks->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tasks->setHorizontalHeaderItem(2, __qtablewidgetitem5);
        tasks->setObjectName(QStringLiteral("tasks"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(tasks->sizePolicy().hasHeightForWidth());
        tasks->setSizePolicy(sizePolicy4);
        tasks->setMinimumSize(QSize(0, 0));
        tasks->setAlternatingRowColors(true);
        tasks->horizontalHeader()->setStretchLastSection(true);

        verticalLayout_3->addWidget(tasks);

        splitter->addWidget(layoutWidget2);

        horizontalLayout_2->addWidget(splitter);


        retranslateUi(Statistic);

        QMetaObject::connectSlotsByName(Statistic);
    } // setupUi

    void retranslateUi(QWidget *Statistic)
    {
        Statistic->setWindowTitle(QApplication::translate("Statistic", "\320\241\321\202\320\260\321\202\320\270\321\201\321\202\320\270\320\272\320\260", 0));
        label->setText(QApplication::translate("Statistic", "\320\236\321\202\321\200\320\265\320\267\320\272\320\270:", 0));
        QTableWidgetItem *___qtablewidgetitem = periods->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("Statistic", "\320\227\320\260\320\264\320\260\321\207\320\260", 0));
        QTableWidgetItem *___qtablewidgetitem1 = periods->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("Statistic", "\320\235\320\260\321\207\320\260\320\273\320\276", 0));
        QTableWidgetItem *___qtablewidgetitem2 = periods->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("Statistic", "\320\232\320\276\320\275\320\265\321\206", 0));
        metrics->setText(QApplication::translate("Statistic", "\320\230\320\275\320\264\320\265\320\272\321\201 \320\277\320\265\321\200\320\265\320\272\320\273\321\216\321\207\320\260\320\265\320\274\320\276\321\201\321\202\320\270:", 0));
        back->setText(QApplication::translate("Statistic", "<", 0));
        forward->setText(QApplication::translate("Statistic", ">", 0));
        label_2->setText(QApplication::translate("Statistic", "\320\227\320\260\320\264\320\260\321\207\320\270:", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tasks->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QApplication::translate("Statistic", "\320\227\320\260\320\264\320\260\321\207\320\260", 0));
        QTableWidgetItem *___qtablewidgetitem4 = tasks->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QApplication::translate("Statistic", "\320\222\321\200\320\265\320\274\321\217", 0));
        QTableWidgetItem *___qtablewidgetitem5 = tasks->horizontalHeaderItem(2);
        ___qtablewidgetitem5->setText(QApplication::translate("Statistic", "\320\222\321\201\320\265\320\263\320\276", 0));
    } // retranslateUi

};

namespace Ui {
    class Statistic: public Ui_Statistic {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATISTIC_H
