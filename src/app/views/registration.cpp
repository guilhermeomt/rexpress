#include "registration.h"
#include "ui_registration.h"

Registration::Registration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Registration)
{
    ui->setupUi(this);

    ui->btnBox->button(QDialogButtonBox::Ok)->setText("Confirmar");
    ui->btnBox->button(QDialogButtonBox::Cancel)->setText("Cancelar");
}

Registration::~Registration()
{
    delete ui;
}

void Registration::on_btnBox_accepted()
{
    QString firstName = ui->leFirstName->text();;
    QString lastName = ui->leLastName->text();
    QString email = ui->leEmail->text();
    QString password = ui->lePassword->text();
    QString confirmPassword = ui->leConfirmPassword->text();

    QMessageBox msgError;
    msgError.setIcon(QMessageBox::Critical);
    msgError.setWindowTitle("Erro!");
    if((firstName.length() == 0 || lastName.length() == 0) || email.length() == 0
            || password.length() == 0 || confirmPassword.length() == 0) {
        msgError.setText("Preencha todos os campos, por favor.");
        msgError.exec();
        return;
    }

    if(password != confirmPassword) {
        msgError.setText("Senha não corresponde. Tente novamente.");
        msgError.exec();
        return;
    }

    auto userWithSameEmail = m_usersRepository->getByEmail(email);

    if(userWithSameEmail) {
        msgError.setText("Um usuário com este email já existe.");
        msgError.exec();
        return;
    }

    QByteArray baPassword = password.toLocal8Bit();
    QString hashedPassword = QString("%1").arg(QString(QCryptographicHash::hash(baPassword,QCryptographicHash::Md5).toHex()));

    User user("id", firstName, lastName, email, hashedPassword);
    auto userRow = m_usersRepository->create(user);

    if(userRow) {
        QMessageBox msgSuccess;
        msgSuccess.setText("Sua conta criada com sucesso!");
        msgSuccess.setIcon(QMessageBox::Information);
        msgSuccess.setWindowTitle("Bem vindo " + user.getFirstName() + "!");
        int ret = msgSuccess.exec();

        switch(ret) {
        case QMessageBox::Ok:
            this->close();
            break;
        default:
            break;
        }

    } else {
        msgError.setText("Ocorreu algum erro inesperado. Tente novamente mais tarde.");
        msgError.exec();
    }
}


void Registration::on_btnBox_clicked(QAbstractButton *button)
{
    if(button == ui->btnBox->button(QDialogButtonBox::Cancel)) {
        this->close();
    }
}

