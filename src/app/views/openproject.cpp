#include "openproject.h"
#include "ui_openproject.h"

OpenProject::OpenProject(User *authUser, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenProject),
    m_authUser(authUser)
{
    ui->setupUi(this);

    ui->btnBox->button(QDialogButtonBox::Ok)->setText("Selecionar");
    ui->btnBox->button(QDialogButtonBox::Cancel)->setText("Cancelar");

    auto vec = m_projectsRepository->getByUserId(m_authUser->getId());

    if(!vec) {
        return;
    }

    for(Project *project : *vec) {
        ui->list->addItem(project->getName());
    }
}

OpenProject::~OpenProject()
{
    delete ui;
}


void OpenProject::on_list_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if(previous) {
        previous->setIcon(QIcon());
    }
    current->setIcon(QIcon(":/icons/svg/checkmark.svg"));
}


void OpenProject::on_btnBox_accepted()
{
    auto list = ui->list->selectedItems();

    if(list.empty()) {
        QMessageBox msgError;
        msgError.setText("Selecione algum projeto.");
        msgError.setIcon(QMessageBox::Critical);
        msgError.setWindowTitle("Erro!");
        msgError.exec();
        return;
    }

    auto selectedItem = list.first();

    Project* project = m_projectsRepository->getByName(selectedItem->text());

    emit accept(project);
}

