/********************************************************************************
** Form generated from reading UI file 'selectwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTWINDOW_H
#define UI_SELECTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectWindow
{
public:
    QVBoxLayout *verticalLayout;
    QGraphicsView *graphicsView;

    void setupUi(QWidget *SelectWindow)
    {
        if (SelectWindow->objectName().isEmpty())
            SelectWindow->setObjectName(QStringLiteral("SelectWindow"));
        SelectWindow->resize(742, 553);
        verticalLayout = new QVBoxLayout(SelectWindow);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        graphicsView = new QGraphicsView(SelectWindow);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        verticalLayout->addWidget(graphicsView);


        retranslateUi(SelectWindow);

        QMetaObject::connectSlotsByName(SelectWindow);
    } // setupUi

    void retranslateUi(QWidget *SelectWindow)
    {
        SelectWindow->setWindowTitle(QApplication::translate("SelectWindow", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class SelectWindow: public Ui_SelectWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTWINDOW_H
