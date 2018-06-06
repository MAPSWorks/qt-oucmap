/********************************************************************************
** Form generated from reading UI file 'oucmap.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OUCMAP_H
#define UI_OUCMAP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_oucmapClass
{
public:

    void setupUi(QWidget *oucmapClass)
    {
        if (oucmapClass->objectName().isEmpty())
            oucmapClass->setObjectName(QStringLiteral("oucmapClass"));
        oucmapClass->resize(600, 400);

        retranslateUi(oucmapClass);

        QMetaObject::connectSlotsByName(oucmapClass);
    } // setupUi

    void retranslateUi(QWidget *oucmapClass)
    {
        oucmapClass->setWindowTitle(QApplication::translate("oucmapClass", "oucmap", nullptr));
    } // retranslateUi

};

namespace Ui {
    class oucmapClass: public Ui_oucmapClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OUCMAP_H
