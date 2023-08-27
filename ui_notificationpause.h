/********************************************************************************
** Form generated from reading UI file 'notificationpause.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOTIFICATIONPAUSE_H
#define UI_NOTIFICATIONPAUSE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_PauseForm
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QPushButton *pushButton;

    void setupUi(QDialog *PauseForm)
    {
        if (PauseForm->objectName().isEmpty())
            PauseForm->setObjectName(QStringLiteral("PauseForm"));
        PauseForm->resize(321, 78);
        verticalLayout = new QVBoxLayout(PauseForm);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(PauseForm);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        pushButton = new QPushButton(PauseForm);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);


        retranslateUi(PauseForm);

        QMetaObject::connectSlotsByName(PauseForm);
    } // setupUi

    void retranslateUi(QDialog *PauseForm)
    {
        PauseForm->setWindowTitle(QString());
        label->setText(QApplication::translate("PauseForm", "\320\240\320\260\320\261\320\276\321\202\320\260 \321\201\321\202\320\276\320\270\321\202!", 0));
        pushButton->setText(QApplication::translate("PauseForm", "\320\236\320\232", 0));
    } // retranslateUi

};

namespace Ui {
    class PauseForm: public Ui_PauseForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOTIFICATIONPAUSE_H
