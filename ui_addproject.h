/********************************************************************************
** Form generated from reading UI file 'addproject.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDPROJECT_H
#define UI_ADDPROJECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AddProject
{
public:
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *AddProject)
    {
        if (AddProject->objectName().isEmpty())
            AddProject->setObjectName(QStringLiteral("AddProject"));
        AddProject->resize(589, 68);
        verticalLayout = new QVBoxLayout(AddProject);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        lineEdit = new QLineEdit(AddProject);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        verticalLayout->addWidget(lineEdit);

        buttonBox = new QDialogButtonBox(AddProject);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(AddProject);
        QObject::connect(buttonBox, SIGNAL(accepted()), AddProject, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), AddProject, SLOT(reject()));

        QMetaObject::connectSlotsByName(AddProject);
    } // setupUi

    void retranslateUi(QDialog *AddProject)
    {
        AddProject->setWindowTitle(QApplication::translate("AddProject", "\320\235\320\276\320\262\321\213\320\271 \320\277\321\200\320\276\320\265\320\272\321\202", 0));
    } // retranslateUi

};

namespace Ui {
    class AddProject: public Ui_AddProject {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDPROJECT_H
