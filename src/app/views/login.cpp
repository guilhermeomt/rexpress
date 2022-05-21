#include "login.h"
#include "ui_login.h"
#include "models/user.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    setWindowTitle(tr("Rexpress"));
    ui->lblLogo->setFixedSize(QSize(231, 140));
    ui->lblLogo->setScaledContents(true);
    ui->lblLogo->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    QPixmap logo(":/images/logo.png");
    ui->lblLogo->setPixmap(logo.scaled(ui->lblLogo->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->lblLogo->setAlignment(Qt::AlignCenter);
}

Login::~Login()
{
    delete ui;
}

void Login::on_btnLogin_clicked()
{
    QString email = ui->leEmail->text();
    QString password = QString("%1").arg(QString(QCryptographicHash::hash(ui->lePassword->text().toUtf8(),QCryptographicHash::Md5).toHex()));

    QSettings settings(":/settings/settings.ini", QSettings::IniFormat);
    m_usersRepository = new UsersRepository(settings);
    auto user = m_usersRepository->getByEmailAndPassword(email, password);

    if(!user) {
        QMessageBox msgError;
        msgError.setText("Email e/ou senha incorreto(s).");
        msgError.setIcon(QMessageBox::Critical);
        msgError.setWindowTitle("Login inválido!");
        msgError.exec();
    } else {
        this->hide();
        m_w = new CMainWindow(user);
        m_w->show();
    }

    delete m_usersRepository;
}


void Login::on_btnAbout_clicked()
{
    if (!m_about) m_about = new About();
    if (!m_about->isVisible()) m_about->show();
}


void Login::on_btnRegister_clicked()
{
    if (!m_registration) m_registration = new Registration(this);
    if (!m_registration->isVisible()) m_registration->show();
}

