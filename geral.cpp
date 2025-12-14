#include "geral.h"
#include "ui_geral.h"

Geral::Geral(QWidget *parent): QMainWindow(parent), ui(new Ui::Geral)
{
    ui->setupUi(this);
    ui->pbOpera->setText("Abrir arquivo");
    this->setWindowTitle("Começar lendo arquivo.");
    cda = new Arquivo;
}

Geral::~Geral()
{
    delete ui;
}

void Geral::on_pbOpera_clicked()
{
    /*
    if(cda->Buffer.length())        //  aqui devem entrar mais opções
    {
        qDebug() << cda->Buffer;
        return;
    }
    ui->pbOpera->setText("Mostrar arquivo");
    this->setWindowTitle("Verificar fluxo.");
    cda->show();

    QString linha = "00141013,8634998,53949,628 MF_________";
    Pilha<uint> nc;
    nc.Push(6);
    nc.Push(8);
    nc.Push(8);
    nc.Push(4);
    uint a, b;
    nc.Pop(a);
    nc.Pop(b);
    qDebug()
        << linha.left(a)
        << '\n'
        << linha.right(linha.length() - a).left(b);
    a += b;
    nc.Pop(b);
    qDebug()
        << linha.right(linha.length() - a).left(b);
    a += b;
    nc.Pop(b);
    qDebug()
        << linha.right(linha.length() - a).left(b);
    a += b;
    qDebug()
        << linha.right(linha.length() - a);
    qDebug()
        << linha.left(4)
        << '\n'
        << linha.right(linha.length() - 4).left(8)
        << '\n'
        << linha.right(linha.length() - 12).left(8)
        << '\n'
        << linha.right(linha.length() - 20).left(6)
        << '\n'
        << linha.right(linha.length() - 26);
    */
    Ponto p;
    p.teste("00141013,8634998,53949,628 MF_________");
}

