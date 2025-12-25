#include "topografia.h"
#include "ui_topografia.h"

Topografia::Topografia(QWidget *parent): QMainWindow(parent), ui(new Ui::Topografia)
{
    ui->setupUi(this);
}

Topografia::~Topografia()
{
    delete ui;
}
