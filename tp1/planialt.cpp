#include "planialt.h"
#include "ui_planialt.h"

planialt::planialt(QWidget *parent): QMainWindow(parent), ui(new Ui::planialt)
{
    ui->setupUi(this);
    Passo = 0;
    ui->pte->setEnabled(false);
    ui->pbo->setText("Ler arquivo de pontos");
    this->setWindowTitle("Gerar superfície");
}

bool planialt::LerArquivo(QString dir, QString filtro, QString titulo)
{
    QString id = QFileDialog::getOpenFileName(nullptr, titulo, dir, filtro);
    if(id == "") return false;
    QFile arq;
    arq.setFileName(id);
    if(!arq.open(QFile::ReadOnly | QFile::Text))return false;
    Buffer.clear();
    Buffer = arq.readAll();
    arq.close();
    return true;
}

bool planialt::LerArquivo(QString filtro, QString titulo)
{
    return LerArquivo(IDIR, filtro, titulo);
}

void planialt::on_pbo_clicked()
{
    if(!Passo)
    {
        if(!LerArquivo("Todos (*.*)", "Ler pontos")) return;
        ui->pte->setEnabled(true);
        ui->pte->setPlainText(Buffer);
        ui->pbo->setText("Ler arquivo de arestas");
        Passo++;
        return;
    }
    if(Passo == 1)
    {
        if(!LerArquivo("Todos (*.*)", "Ler arestas")) return;
        ui->pte->setEnabled(true);
        ui->pte->setPlainText(Buffer);
        ui->pbo->setText("Gerar superfície");
        Passo++;
        return;
    }
}

planialt::~planialt()
{
    delete ui;
}
