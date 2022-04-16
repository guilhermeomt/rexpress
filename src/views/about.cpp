#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);

    ui->lblLogo->setScaledContents(true);
    ui->lblLogo->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
}

About::~About()
{
    delete ui;
}

void About::on_btnOk_clicked()
{
    this->close();
}

