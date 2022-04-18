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
    const char* firstName = ui->leFirstName->text().toStdString().c_str();
    const char* lastName = ui->leLastName->text().toStdString().c_str();
    const char* email = ui->leEmail->text().toStdString().c_str();
    const char* password = ui->lePassword->text().toStdString().c_str();
    const char* confirmPassword = ui->leConfirmPassword->text().toStdString().c_str();

    QMessageBox msgError;
    msgError.setIcon(QMessageBox::Critical);
    msgError.setWindowTitle("Erro!");
    if((strlen(firstName) == 0) || (strlen(lastName) == 0) || (strlen(email) == 0)
            || (strlen(password) == 0) || (strlen(confirmPassword) == 0)) {
        msgError.setText("Preencha todos os campos, por favor.");
        msgError.exec();
        return;
    }

    if(strcmp(password, confirmPassword)) {
        msgError.setText("Senha não corresponde. Tente novamente.");
        msgError.exec();
        return;
    }

    QSettings settings(":/settings/settings.ini", QSettings::IniFormat);
    m_usersRepository = new UsersRepository(settings);

    auto userWithSameEmail = m_usersRepository->getByEmail(email);

    if(userWithSameEmail) {
        msgError.setText("Um usuário com este email já existe.");
        msgError.exec();
        return;
    }

    User user(firstName, lastName, email, password);
    auto userRow = m_usersRepository->create(user);

    qDebug()  << userRow;
    if(userRow) {
        QMessageBox msgSuccess;
        msgSuccess.setText("Sua conta criada com sucesso!");
        msgSuccess.setIcon(QMessageBox::Information);
        msgSuccess.setWindowTitle("Bem vindo " + user.getFirstName() + "!");
        msgSuccess.exec();
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

