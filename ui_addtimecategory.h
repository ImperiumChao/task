/********************************************************************************
** Form generated from reading UI file 'addtimecategory.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDTIMECATEGORY_H
#define UI_ADDTIMECATEGORY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddTimeCategory
{
public:
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QVBoxLayout *verticalLayout;
    QLineEdit *name;
    QLineEdit *from;
    QLineEdit *to;
    QCheckBox *defaultValue;
    QDialogButtonBox *buttonBox;

    void setupUi(QWidget *AddTimeCategory)
    {
        if (AddTimeCategory->objectName().isEmpty())
            AddTimeCategory->setObjectName(QStringLiteral("AddTimeCategory"));
        AddTimeCategory->resize(272, 148);
        verticalLayout_4 = new QVBoxLayout(AddTimeCategory);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label = new QLabel(AddTimeCategory);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_2->addWidget(label);

        label_2 = new QLabel(AddTimeCategory);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_2->addWidget(label_2);

        label_3 = new QLabel(AddTimeCategory);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_2->addWidget(label_3);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        name = new QLineEdit(AddTimeCategory);
        name->setObjectName(QStringLiteral("name"));

        verticalLayout->addWidget(name);

        from = new QLineEdit(AddTimeCategory);
        from->setObjectName(QStringLiteral("from"));

        verticalLayout->addWidget(from);

        to = new QLineEdit(AddTimeCategory);
        to->setObjectName(QStringLiteral("to"));

        verticalLayout->addWidget(to);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_3->addLayout(horizontalLayout);

        defaultValue = new QCheckBox(AddTimeCategory);
        defaultValue->setObjectName(QStringLiteral("defaultValue"));
        defaultValue->setTristate(false);

        verticalLayout_3->addWidget(defaultValue);


        verticalLayout_4->addLayout(verticalLayout_3);

        buttonBox = new QDialogButtonBox(AddTimeCategory);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_4->addWidget(buttonBox);


        retranslateUi(AddTimeCategory);

        QMetaObject::connectSlotsByName(AddTimeCategory);
    } // setupUi

    void retranslateUi(QWidget *AddTimeCategory)
    {
        AddTimeCategory->setWindowTitle(QApplication::translate("AddTimeCategory", "\320\235\320\276\320\262\320\260\321\217 \320\272\320\260\321\202\320\265\320\263\320\276\321\200\320\270\321\216 \321\202\321\200\321\203\320\264\320\276\320\265\320\274\320\272\320\276\321\201\321\202\320\270", 0));
        label->setText(QApplication::translate("AddTimeCategory", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265:", 0));
        label_2->setText(QApplication::translate("AddTimeCategory", "\320\236\321\202:", 0));
        label_3->setText(QApplication::translate("AddTimeCategory", "\320\224\320\276:", 0));
        defaultValue->setText(QApplication::translate("AddTimeCategory", "\320\241\321\202\320\260\320\262\320\270\321\202\321\214 \320\277\320\276 \321\203\320\274\320\276\320\273\321\207\320\260\320\275\320\270\321\216", 0));
    } // retranslateUi

};

namespace Ui {
    class AddTimeCategory: public Ui_AddTimeCategory {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDTIMECATEGORY_H
