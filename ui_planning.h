/********************************************************************************
** Form generated from reading UI file 'planning.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLANNING_H
#define UI_PLANNING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Planning
{
public:
    QVBoxLayout *verticalLayout_4;
    QSplitter *splitter_2;
    QSplitter *splitter;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QCalendarWidget *calendar;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *addProject;
    QPushButton *orderProjectUp;
    QPushButton *orderProjectDown;
    QPushButton *deleteProject;
    QSpacerItem *horizontalSpacer;
    QWidget *widget;
    QVBoxLayout *verticalLayout_3;
    QListWidget *projects;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *layoutCommandsTasks;
    QPushButton *addTask;
    QPushButton *orderTaskUp;
    QPushButton *orderTaskDown;
    QPushButton *deleteTask;
    QCheckBox *showCompletedTasks;
    QSpacerItem *horizontalSpacer_2;
    QTableWidget *tasks;
    QLabel *workload;

    void setupUi(QWidget *Planning)
    {
        if (Planning->objectName().isEmpty())
            Planning->setObjectName(QStringLiteral("Planning"));
        Planning->resize(1002, 750);
        verticalLayout_4 = new QVBoxLayout(Planning);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        splitter_2 = new QSplitter(Planning);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setOrientation(Qt::Horizontal);
        splitter = new QSplitter(splitter_2);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Vertical);
        widget_2 = new QWidget(splitter);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(widget_2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        calendar = new QCalendarWidget(widget_2);
        calendar->setObjectName(QStringLiteral("calendar"));

        verticalLayout->addWidget(calendar);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        addProject = new QPushButton(widget_2);
        addProject->setObjectName(QStringLiteral("addProject"));

        horizontalLayout_2->addWidget(addProject);

        orderProjectUp = new QPushButton(widget_2);
        orderProjectUp->setObjectName(QStringLiteral("orderProjectUp"));

        horizontalLayout_2->addWidget(orderProjectUp);

        orderProjectDown = new QPushButton(widget_2);
        orderProjectDown->setObjectName(QStringLiteral("orderProjectDown"));

        horizontalLayout_2->addWidget(orderProjectDown);

        deleteProject = new QPushButton(widget_2);
        deleteProject->setObjectName(QStringLiteral("deleteProject"));

        horizontalLayout_2->addWidget(deleteProject);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(verticalLayout);

        splitter->addWidget(widget_2);
        widget = new QWidget(splitter);
        widget->setObjectName(QStringLiteral("widget"));
        verticalLayout_3 = new QVBoxLayout(widget);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        projects = new QListWidget(widget);
        projects->setObjectName(QStringLiteral("projects"));

        verticalLayout_3->addWidget(projects);

        splitter->addWidget(widget);
        splitter_2->addWidget(splitter);
        verticalLayoutWidget_2 = new QWidget(splitter_2);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayout_5 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        layoutCommandsTasks = new QHBoxLayout();
        layoutCommandsTasks->setObjectName(QStringLiteral("layoutCommandsTasks"));
        addTask = new QPushButton(verticalLayoutWidget_2);
        addTask->setObjectName(QStringLiteral("addTask"));

        layoutCommandsTasks->addWidget(addTask);

        orderTaskUp = new QPushButton(verticalLayoutWidget_2);
        orderTaskUp->setObjectName(QStringLiteral("orderTaskUp"));

        layoutCommandsTasks->addWidget(orderTaskUp);

        orderTaskDown = new QPushButton(verticalLayoutWidget_2);
        orderTaskDown->setObjectName(QStringLiteral("orderTaskDown"));

        layoutCommandsTasks->addWidget(orderTaskDown);

        deleteTask = new QPushButton(verticalLayoutWidget_2);
        deleteTask->setObjectName(QStringLiteral("deleteTask"));

        layoutCommandsTasks->addWidget(deleteTask);

        showCompletedTasks = new QCheckBox(verticalLayoutWidget_2);
        showCompletedTasks->setObjectName(QStringLiteral("showCompletedTasks"));

        layoutCommandsTasks->addWidget(showCompletedTasks);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        layoutCommandsTasks->addItem(horizontalSpacer_2);


        verticalLayout_5->addLayout(layoutCommandsTasks);

        tasks = new QTableWidget(verticalLayoutWidget_2);
        tasks->setObjectName(QStringLiteral("tasks"));
        tasks->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        tasks->setAlternatingRowColors(false);
        tasks->horizontalHeader()->setStretchLastSection(true);

        verticalLayout_5->addWidget(tasks);

        workload = new QLabel(verticalLayoutWidget_2);
        workload->setObjectName(QStringLiteral("workload"));

        verticalLayout_5->addWidget(workload);

        splitter_2->addWidget(verticalLayoutWidget_2);

        verticalLayout_4->addWidget(splitter_2);


        retranslateUi(Planning);

        QMetaObject::connectSlotsByName(Planning);
    } // setupUi

    void retranslateUi(QWidget *Planning)
    {
        Planning->setWindowTitle(QApplication::translate("Planning", "\320\237\320\273\320\260\320\275\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265. \320\232\320\276\320\275\321\202\321\200\320\276\320\273\321\214 \320\262\321\213\320\277\320\276\320\273\320\275\320\265\320\275\320\270\321\217 \320\267\320\260\320\264\320\260\321\207.", 0));
        addProject->setText(QApplication::translate("Planning", "+", 0));
        orderProjectUp->setText(QApplication::translate("Planning", "\342\206\221", 0));
        orderProjectDown->setText(QApplication::translate("Planning", "\342\206\223", 0));
        deleteProject->setText(QApplication::translate("Planning", "-", 0));
        addTask->setText(QApplication::translate("Planning", "+", 0));
        orderTaskUp->setText(QApplication::translate("Planning", "\342\206\221", 0));
        orderTaskDown->setText(QApplication::translate("Planning", "\342\206\223", 0));
        deleteTask->setText(QApplication::translate("Planning", "-", 0));
        showCompletedTasks->setText(QApplication::translate("Planning", "\320\237\320\276\320\272\320\260\320\267\321\213\320\262\320\260\321\202\321\214 \320\267\320\260\320\262\320\265\321\200\321\210\320\265\320\275\320\275\321\213\320\265 \320\267\320\260\320\264\320\260\321\207\320\270 \320\262 \321\215\321\202\320\276\321\202 \320\264\320\265\320\275\321\214", 0));
        workload->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Planning: public Ui_Planning {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLANNING_H
