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

void Topografia::GeraFaces()
{
    if(La.Empty()) return;
    qDebug()
        << "L35 em GeraFaces";
    Lf.Clear();
    qDebug()
        << "L38 em GeraFaces";
    Nos<Aresta> *ponti = La.GetPrimo(), *pontj, *pontk;
    QString via, vib, vja, vjb, vki, vkj, vka, vkb, v;
    uint n;
    Ponto p;
    while(ponti)
    {
        p = ponti->Valor.GetIni();
        qDebug()
            << "L47 em GeraFaces";
        via = p.GetId();
        qDebug()
            << "L50 em GeraFaces";
        via = ponti->Valor.GetIni().GetId();
        vib = ponti->Valor.GetFim().GetId();
        qDebug()
            << "L54 em GeraFaces";
        pontj = ponti->Segue;
        n = 0;
        while(pontj && (n < 2))
        {
            vja = pontj->Valor.GetIni().GetId();
            vjb = pontj->Valor.GetFim().GetId();
            vki = vkj = "";
            if(via == vja)
            {
                vki = vib;
                vkj = vjb;
                v = via;
            }
            else if(via == vjb)
            {
                vki = vib;
                vkj = vja;
                v = via;
            }
            else if(vib == vja)
            {
                vki = via;
                vkj = vjb;
                v = vib;
            }
            else if(vib == vjb)
            {
                vki = via;
                vkj = vja;
                v = vib;
            }
            if(vki.length())
            {
                bool procura = true;
                pontk = pontj->Segue;
                while(pontk && procura)
                {
                    vka = pontk->Valor.GetIni().GetId();
                    vkb = pontk->Valor.GetFim().GetId();
                    if(((vki == vka) && (vkj == vkb)) || ((vki == vkb) && (vkj == vka)))
                    {
                        Lf.Pushback(Face(v, vki, vkj, Lp.GetPrimo()));
                        procura = false;
                        n++;
                    }
                    pontk = pontk->Segue;
                }
            }
            pontj = pontj->Segue;
        }
        ponti = ponti->Segue;
    }
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

void Topografia::on_pbGSup_clicked()
{
    if(La.Empty()) return;
    qDebug()
        << "L151 em on_pbGSup_clicked";
    GeraFaces();
    qDebug()
        << Lf.Length()
        << " Faces geradas";
}

Topografia::~Topografia()
{
    delete ui;
}
