#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QMessageBox>

#include "mainwindow.h"
#include "about.h"
#include "database/repositories/usersrepository.h"

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

private:
    CMainWindow* m_w;
    About* m_about = nullptr;
    Ui::Login *ui;
    UsersRepository* m_usersRepository = nullptr;
};

#endif // LOGIN_H
