/********************************************************************************
** Form generated from reading UI file 'form.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_H
#define UI_FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QLabel *label_18;
    QWidget *formLayoutWidget_7;
    QFormLayout *formLayout_7;
    QFormLayout *formLayout_6;
    QLabel *label_15;
    QLabel *label_14;
    QLabel *label;
    QFormLayout *formLayout_5;
    QLabel *updatedAt_3;
    QLabel *label_16;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(775, 566);
        label_18 = new QLabel(Form);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(80, 100, 421, 71));
        label_18->setWordWrap(true);
        formLayoutWidget_7 = new QWidget(Form);
        formLayoutWidget_7->setObjectName(QString::fromUtf8("formLayoutWidget_7"));
        formLayoutWidget_7->setGeometry(QRect(80, 240, 501, 121));
        formLayout_7 = new QFormLayout(formLayoutWidget_7);
        formLayout_7->setObjectName(QString::fromUtf8("formLayout_7"));
        formLayout_7->setContentsMargins(0, 0, 0, 0);
        formLayout_6 = new QFormLayout();
        formLayout_6->setObjectName(QString::fromUtf8("formLayout_6"));
        label_15 = new QLabel(formLayoutWidget_7);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        formLayout_6->setWidget(0, QFormLayout::LabelRole, label_15);

        label_14 = new QLabel(formLayoutWidget_7);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        formLayout_6->setWidget(2, QFormLayout::LabelRole, label_14);

        label = new QLabel(formLayoutWidget_7);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout_6->setWidget(1, QFormLayout::LabelRole, label);


        formLayout_7->setLayout(0, QFormLayout::LabelRole, formLayout_6);

        formLayout_5 = new QFormLayout();
        formLayout_5->setObjectName(QString::fromUtf8("formLayout_5"));
        updatedAt_3 = new QLabel(formLayoutWidget_7);
        updatedAt_3->setObjectName(QString::fromUtf8("updatedAt_3"));

        formLayout_5->setWidget(1, QFormLayout::FieldRole, updatedAt_3);

        label_16 = new QLabel(formLayoutWidget_7);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        formLayout_5->setWidget(0, QFormLayout::FieldRole, label_16);


        formLayout_7->setLayout(0, QFormLayout::FieldRole, formLayout_5);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        label_18->setText(QCoreApplication::translate("Form", "<html><head/><body><p><span style=\" font-size:14pt;\">REQ01 - O sistema deve ter login</span></p><p><span style=\" font-size:14pt;\"><br/></span></p></body></html>", nullptr));
        label_15->setText(QCoreApplication::translate("Form", "Criado por:", nullptr));
        label_14->setText(QCoreApplication::translate("Form", "Atualizado em:", nullptr));
        label->setText(QCoreApplication::translate("Form", "Criado em:", nullptr));
        updatedAt_3->setText(QString());
        label_16->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_H
