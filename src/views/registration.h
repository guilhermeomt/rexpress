#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QDialog>
#include <QPushButton>
#include <QMessageBox>
#include <QSettings>
#include <string.h>

#include "database/repositories/usersrepository.h"

namespace Ui {
class Registration;
}

class Registration : public QDialog
{
    Q_OBJECT

public:
    explicit Registration(QWidget *parent = nullptr);
    ~Registration();

private slots:
    void on_btnBox_accepted();

    void on_btnBox_clicked(QAbstractButton *button);

private:
    Ui::Registration *ui;

    UsersRepository* m_usersRepository = nullptr;
};

#endif // REGISTRATION_H
