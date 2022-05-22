#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QMessageBox>

#include "mainwindow.h"
#include "about.h"
#include "database/repositories/usersrepository.h"
#include "registration.h"

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT
public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_btnLogin_clicked();

    void on_btnAbout_clicked();

    void on_btnRegister_clicked();

    IOC_INJECTABLE(UsersRepository, m_usersRepository);
private:
    CMainWindow* m_w = nullptr;
    About* m_about = nullptr;
    Registration* m_registration = nullptr;
    Ui::Login *ui;
    UsersRepository* m_usersRepository = nullptr;
};

#endif // LOGIN_H
