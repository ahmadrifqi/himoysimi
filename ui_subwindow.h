/********************************************************************************
** Form generated from reading UI file 'subwindow.ui'
**
** Created: Wed Sep 3 15:55:22 2014
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUBWINDOW_H
#define UI_SUBWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QTableView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_subwindow
{
public:
    QGridLayout *gridLayout;
    QTableView *tabel_data;

    void setupUi(QWidget *subwindow)
    {
        if (subwindow->objectName().isEmpty())
            subwindow->setObjectName(QString::fromUtf8("subwindow"));
        subwindow->resize(689, 491);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/icon/table-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        subwindow->setWindowIcon(icon);
        gridLayout = new QGridLayout(subwindow);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tabel_data = new QTableView(subwindow);
        tabel_data->setObjectName(QString::fromUtf8("tabel_data"));

        gridLayout->addWidget(tabel_data, 0, 0, 1, 1);


        retranslateUi(subwindow);

        QMetaObject::connectSlotsByName(subwindow);
    } // setupUi

    void retranslateUi(QWidget *subwindow)
    {
        subwindow->setWindowTitle(QApplication::translate("subwindow", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class subwindow: public Ui_subwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUBWINDOW_H
