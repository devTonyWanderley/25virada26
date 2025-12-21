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
    //  imprimir linhas de dados:
    QString ln, id, atr, tx, ty, tz;
    while(cda->Buffer.length() > 45)
    {
        ln = cda->Buffer.left(45);
        id = ln.left(8);
        ln = ln.right(ln.length() - 8);
        atr = ln.left(8);
        ln = ln.right(ln.length() - 8);
        tx = ln.left(10);
        ln = ln.right(ln.length() - 10);
        ty = ln.left(11);
        tz = ln.right(8);
        cda->Buffer = cda->Buffer.right(cda->Buffer.length() - 46);
        qDebug()
            << id << '\t'
            << atr << '\t'
            << tx << '\t'
            << ty << '\t'
            << tz;
    }
    qDebug() << cda->Buffer;
}

void Geral::on_pbOpera_clicked()
{
    if(cda->Buffer.length())        //  aqui devem entrar mais opções
    {
        qDebug()
            << cda->Buffer.length();
        teste();
        return;
    }
    ui->pbOpera->setText("Mostrar arquivo");
    this->setWindowTitle("Verificar fluxo.");
    cda->show();

    /*
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
    Ponto p;
    p.teste("00141013,8634998,53949,628 MF_________");
    Lista<QChar> ls;
    ls.PushFront('0');
    ls.PushFront('1');
    ls.PushFront('2');
    ls.PushFront('3');
    ls.PushFront('4');
    ls.PushFront('5');
    ls.PushFront('6');
    ls.PushFront('7');
    ls.PushFront('8');
    ls.PushFront('9');
    while(ls.Length())
        qDebug()
            << ls.PopFront();
    Pilha<uint> P;
    if(P.Empty())
        qDebug()
            << "Pilha vazia";
    else
        qDebug()
            << "Algo a corrigir";
    P.Push(0);
    if(P.Empty())
        qDebug()
            << "Algo a corrigir";
    else
        qDebug()
            << P.Lenght()
            << " elemento depois do push .. o valor é "
            << P.Top();
    for(uint i = 1; i <= 9; i++)
    P.Push(i);
    if(P.Empty())
        qDebug()
            << "Algo a corrigir";
    else
        qDebug()
            << P.Lenght()
            << " elementos depois do for .. o valor do topo é "
            << P.Top();
    uint v;
    if(!P.Top(v))
        qDebug()
            << "Algo a corrigir com a função Top por referência";
    else
        qDebug()
            << "Por referência o topo vale "
            << v
            << "\nFazendo o Pop .. "
            << P.Pop()
            << "\nEm seguida, revendo o número de elementos .. "
            << P.Lenght();
    //  Fila(), uint Length(), bool Empty(), G Frente(), bool Frente(G &r), G Pop(), bool Pop(G &r)
    //  com a fila vazia:
    Fila<uint> F;
    uint v;
    if(F.Empty())
    {
        qDebug()
            << "bool Empty() .. ok!"
            << "\nuint Length() .. " << F.Length()
            << "\nG Frente() .. " << F.Frente()
            << "\nbool Frente(G &r) .. " << F.Frente(v)
            << "\nG Pop() .. " << F.Pop()
            << "\nbool Pop(G &r) .. " << F.Pop(v);
    }
    //  void Push(const G arg)
    for(uint i = 0; i < 10; i++) F.Push(i);
    if(F.Empty())
        qDebug()
            << "Algo a corrigir";
    else
    {
        qDebug()
            << "bool Empty() .. ok!"
            << "\nuint Length() .. " << F.Length()
            << "\nG Frente() .. " << F.Frente()
            << "\nbool Frente(G &r) .. " << F.Frente(v)
            << "\nG Pop() .. " << F.Pop()
            << "\nbool Pop(G &r) .. " << F.Pop(v);
        while(!F.Empty())
        {
            qDebug()
                << "bool Empty() .. ok!"
                << "\nuint Length() .. " << F.Length()
                << "\nG Frente() .. " << F.Frente()
                << "\nbool Frente(G &r) .. " << F.Frente(v)
                << "\nG Pop() .. " << F.Pop()
                << "\nbool Pop(G &r) .. " << F.Pop(v)
                << "\nv .. " << v;
        }
    }
    teste();
    */
}

Geral::~Geral()
{
    delete ui;
}
