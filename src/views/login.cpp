#include "login.h"
#include "ui_login.h"
#include "models/user.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    setWindowTitle(tr("Rexpress"));
}

Login::~Login()
{
    delete ui;
}

void Login::on_btnSignIn_clicked()
{
    qDebug() << "clicked!";
}

