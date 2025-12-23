#include "geral.h"
#include "ui_geral.h"

Geral::Geral(QWidget *parent): QMainWindow(parent), ui(new Ui::Geral)
{
    ui->setupUi(this);
    ui->pbOpera->setText("Abrir arquivo");
    this->setWindowTitle("Começar lendo arquivo.");
    cda = new Arquivo;
}

void Geral::teste()
{
    //  imprimir linhas separadas:  ..  ok
    //  imprimir linhas de dados:   ..  ok
    //  criar lista de pontos e imprimir:   ..  ok
    //      -> criar um ponto com ln:   ..  ok
    //      -> criar lista de pontos:   ..  ok
    //      -> imprimir os pontos:  ..  ok
    QString ln;
    Lista<Ponto> lp;
    while(cda->Buffer.length() > 45)
    {
        ln = cda->Buffer.left(45);
        lp.Pushback(Ponto(ln));
        cda->Buffer = cda->Buffer.right(cda->Buffer.length() - 46);
    }
    qDebug()
        << "lp tem "
        << lp.Length()
        << " elementos";
    uint n = lp.Length();
    for(uint i = 0; i < n; i++)
    {
        //p = lp.Getn(i);
        qDebug()
            << lp.Getn(i).GetId() << '\t'
            << lp.Getn(i).GetAtr() << '\t'
            << lp.Getn(i).GetX() << '\t'
            << lp.Getn(i).GetY() << '\t'
            << lp.Getn(i).GetZ();
    }
    //  Instanciar uma aresta
    Aresta ar(lp.GetPrimo(), "3", "4");
    Ponto p(ar.GetIni()), q(ar.GetFim());
    qDebug()
        << p.GetId() << '\t'
        << p.GetAtr() << '\t'
        << p.GetX() << '\t'
        << p.GetY() << '\t'
        << p.GetZ();
    qDebug()
        << q.GetId() << '\t'
        << q.GetAtr() << '\t'
        << q.GetX() << '\t'
        << q.GetY() << '\t'
        << q.GetZ();
}

void Geral::on_pbOpera_clicked()
{
    if(cda->Buffer.length())        //  aqui devem entrar mais opções
    {
        teste();
        return;
    }
    ui->pbOpera->setText("Mostrar arquivo");
    this->setWindowTitle("Verificar fluxo.");
    cda->show();
}

Geral::~Geral()
{
    delete ui;
}
