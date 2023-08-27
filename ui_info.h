/********************************************************************************
** Form generated from reading UI file 'info.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INFO_H
#define UI_INFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include "buttonimage.h"

QT_BEGIN_NAMESPACE

class Ui_Info
{
public:
    QHBoxLayout *horizontalLayout;
    ButtonImage *labelPlay;
    ButtonImage *labelPause;
    QLabel *label;

    void setupUi(QWidget *Info)
    {
        if (Info->objectName().isEmpty())
            Info->setObjectName(QStringLiteral("Info"));
        Info->resize(400, 300);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Info->sizePolicy().hasHeightForWidth());
        Info->setSizePolicy(sizePolicy);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(0, 0, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Light, brush1);
        QBrush brush2(QColor(255, 85, 255, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Highlight, brush1);
        palette.setBrush(QPalette::Active, QPalette::HighlightedText, brush1);
        QBrush brush3(QColor(0, 0, 0, 128));
        brush3.setStyle(Qt::SolidPattern);
//        palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Highlight, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::HighlightedText, brush1);
//        palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush3);
        QBrush brush4(QColor(120, 120, 120, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        QBrush brush5(QColor(0, 120, 215, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Highlight, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::HighlightedText, brush1);
//        palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush3);
        Info->setPalette(palette);
        horizontalLayout = new QHBoxLayout(Info);
        horizontalLayout->setSpacing(9);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetFixedSize);
        horizontalLayout->setContentsMargins(9, 9, 9, 9);
        labelPlay = new ButtonImage(Info);
        labelPlay->setObjectName(QStringLiteral("labelPlay"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labelPlay->sizePolicy().hasHeightForWidth());
        labelPlay->setSizePolicy(sizePolicy1);
        labelPlay->setMinimumSize(QSize(35, 35));
        labelPlay->setCursor(QCursor(Qt::PointingHandCursor));
        labelPlay->setScaledContents(true);

        horizontalLayout->addWidget(labelPlay);

        labelPause = new ButtonImage(Info);
        labelPause->setObjectName(QStringLiteral("labelPause"));
        sizePolicy1.setHeightForWidth(labelPause->sizePolicy().hasHeightForWidth());
        labelPause->setSizePolicy(sizePolicy1);
        labelPause->setMinimumSize(QSize(35, 35));
        labelPause->setScaledContents(true);

        horizontalLayout->addWidget(labelPause);

        label = new QLabel(Info);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setWordWrap(true);

        horizontalLayout->addWidget(label);


        retranslateUi(Info);

        QMetaObject::connectSlotsByName(Info);
    } // setupUi

    void retranslateUi(QWidget *Info)
    {
        Info->setWindowTitle(QApplication::translate("Info", "Form", 0));
        labelPlay->setText(QApplication::translate("Info", "\320\232\320\260\321\200\321\202\320\270\320\275\320\272\320\260", 0));
#ifndef QT_NO_WHATSTHIS
        labelPause->setWhatsThis(QApplication::translate("Info", "\320\237\320\260\321\203\320\267\320\260", 0));
#endif // QT_NO_WHATSTHIS
        labelPause->setText(QApplication::translate("Info", "\320\232\320\260\321\200\321\202\320\270\320\275\320\272\320\260", 0));
        label->setText(QApplication::translate("Info", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class Info: public Ui_Info {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFO_H
