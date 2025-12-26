#include "topografia.h"
#include "ui_topografia.h"

Topografia::Topografia(QWidget *parent): QMainWindow(parent), ui(new Ui::Topografia)
{
    ui->setupUi(this);
    ui->pte->setEnabled(false);
    ui->pbLerArs->setEnabled(false);
    ui->pbGSup->setEnabled(false);
    ui->pte->setReadOnly(true);
}

bool Topografia::LerArquivo(QString dir, QString filtro, QString titulo)
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

bool Topografia::LerArquivo(QString filtro, QString titulo)
{
    return LerArquivo(IDIR, filtro, titulo);
}

void Topografia::on_pbLerPts_clicked()
{
    ui->pbGSup->setEnabled(false);
    if(!LerArquivo("Todos (*.*)", "Ler pontos")) return;
    ui->pte->clear();
    ui->pte->setPlainText(Buffer);
    ui->pte->setEnabled(true);
    ui->pbLerArs->setEnabled(true);
    Lp.Clear();
    while(Buffer.length() > 45)
    {
        Lp.Pushback(Ponto(Buffer.left(45)));
        Buffer = Buffer.right(Buffer.length() - 46);
    }
    qDebug()
        << Lp.Length()
        << " pontos lidos";
}

void Topografia::on_pbLerArs_clicked()
{
    ui->pbGSup->setEnabled(false);
    if(!LerArquivo("Todos (*.*)", "Ler Arestas")) return;
    ui->pte->clear();
    ui->pte->setPlainText(Buffer);
    ui->pte->setEnabled(true);
    La.Clear();
    while(Buffer.length() > 16)
    {
        La.Pushback(Aresta(Lp.GetPrimo(), Buffer.left(16)));
        Buffer = Buffer.right(Buffer.length() - 17);
    }
    qDebug()
        << La.Length()
        << " arestas lidas";
    if(!La.Empty() && !Lp.Empty()) ui->pbGSup->setEnabled(true);
}

Topografia::~Topografia()
{
    delete ui;
}
