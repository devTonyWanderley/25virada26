#include "quadro.h"

Quadro::Quadro()
{
    Xc = Yc = Sl = Sa = 0;
    NE = NW = SW = SE = nullptr;
}

Quadro::Quadro(const double xc, const double yc, const double sl, const double sa)
{
    Xc = xc;
    Yc = yc;
    Sl = sl;
    Sa = sa;
    NE = NW = SW = SE = nullptr;
}

Quadro::Quadro(const Quadro &outro)
{
    Xc = outro.Xc;
    Yc = outro.Yc;
    Sl = outro.Sl;
    Sa = outro.Sa;
    NE = NW = SW = SE = nullptr;
}

Quadro::Quadro(Quadro &pai, const bool norte, const bool leste)
{
    Xc = pai.Xc;
    Yc = pai.Yc;
    Sl = pai.Sl / 2;
    Sa = pai.Sa / 2;
    if(norte)
        Yc += Sa;
    else
        Yc -= Sa;
    if(leste)
        Xc += Sl;
    else
        Xc -= Sl;
    NE = NW = SW = SE = nullptr;
}

void Quadro::Push(const Ponto p)
{
    lst.Pushback(p);
}

void Quadro::GetCantos(double &xi, double &yi, double &xa, double &ya)
{
    xi = xa = lst.Getfront().GetX();
    yi = ya = lst.Getfront().GetY();
    uint n = lst.Length();
    for(uint i = 1; i < n; i++)
    {
        if(xi > lst.Getn(i).GetX())
            xi = lst.Getn(i).GetX();
        else if(xa < lst.Getn(i).GetX())
            xa = lst.Getn(i).GetX();
        if(yi > lst.Getn(i).GetY())
            yi = lst.Getn(i).GetY();
        else if(ya < lst.Getn(i).GetY())
            ya = lst.Getn(i).GetY();
    }
}

void Quadro::Distribui()
{
    double cantos[4];
    GetCantos(cantos[0], cantos[1], cantos[2], cantos[3]);
}

Ponto Quadro::BuscaEmQ(const double x, const double y)
{
    Ponto r;
    return r;
}

Ponto Quadro::BuscaMaisProx(const double x, const double y)
{
    Ponto r;
    return r;
}
