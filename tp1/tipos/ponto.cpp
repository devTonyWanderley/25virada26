#include "ponto.h"

Ponto::Ponto(const QString id, const QString atr, const double x, const double y, const double z)
{
    Nome = id;
    Atri = atr;
    Abci = x;
    Orde = y;
    Cota = z;
}

Ponto::Ponto()
{
    Nome = Atri = "";
    Abci = Orde = Cota = 0;
}

Ponto::Ponto(const Ponto& outro)
{
    Nome = outro.Nome;
    Atri = outro.Atri;
    Abci = outro.Abci;
    Orde = outro.Orde;
    Cota = outro.Cota;
}

Ponto::Ponto(const QString ln)
{
    QString lnl = ln, idl, atrl;
    double xl, yl, zl;
    if(LerLinha(lnl,idl, atrl, xl, yl, zl))
    {
        Nome = idl;
        Atri = atrl;
        Abci = xl;
        Orde = yl;
        Cota = zl;
    }
    else
    {
        Nome = Atri = "";
        Abci = Orde = Cota = 0;
    }
}

double Ponto::LerDouble(QString arg)
{
    QString ta = arg.left(arg.length() - 4), tb = arg.right(3);
    double a = ta.toDouble(), b = tb.toDouble();
    b /= 1000.0;
    return (a + b);
}

bool Ponto::LerLinha(QString &ln, QString &id, QString &atr, double &x, double &y, double &z)
{
    //  idididid atratrat    500000,000  1000000,000 1000,000
    //  8           8           10          11          8
    //  1 .. 8   9 .. 16     17 .. 26     27 .. 37    38 .. 45
    //  45           37           29           19           8
    if(ln.length() != 45) return false;
    id = ln.left(8);
    ln = ln.right(37);
    atr = ln.left(8);
    ln = ln.right(29);
    x = LerDouble(ln.left(10));
    ln = ln.right(19);
    y = LerDouble(ln.left(11));
    z = LerDouble(ln.right(8));
    id = NormaTexto(id);
    atr = NormaTexto(atr);
    return true;
}

QString Ponto::NormaTexto(QString arg)
{
    QChar c;
    bool flg = true;
    while(flg)
    {
        c = *arg.data();
        if((c >= '0' && c <='9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) flg = false;
        else arg = arg.right(arg.length() - 1);
    }
    return arg;
}

void Ponto::SetId(QString id)
{
    Nome = id;
}

void Ponto::SetAtr(QString atr)
{
    Atri = atr;
}

void Ponto::SetX(double x)
{
    Abci = x;
}

void Ponto::SetY(double y)
{
    Orde = y;
}

void Ponto::SetZ(double z)
{
    Cota = z;
}

QString Ponto::GetId()
{
    return Nome;
}

QString Ponto::GetAtr()
{
    return Atri;
}

double Ponto::GetX()
{
    return Abci;
}

double Ponto::GetY()
{
    return Orde;
}

double Ponto::GetZ()
{
    return Cota;
}

Ponto Ponto::operator = (const Ponto &outro)
{
    Nome = outro.Nome;
    Atri = outro.Atri;
    Abci = outro.Abci;
    Orde = outro.Orde;
    Cota = outro.Cota;
    return *this;
}

bool Ponto::operator == (const Ponto outro)
{
    if(Abci != outro.Abci) return false;
    if(Orde != outro.Orde) return false;
    return (Cota == outro.Cota);
}
