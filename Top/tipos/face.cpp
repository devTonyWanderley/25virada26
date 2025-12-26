#include "face.h"

Face::Face()
{
    Va = Vb = Vc = "";
}

Face::Face(const QString v0, const QString v1, const QString v2, Nos<Ponto> *pont)
{
    Nos<Ponto> *p0 = GetPonto(pont, v0), *p1 = GetPonto(pont, v1), *p2 = GetPonto(pont, v2), *p;
    if(p0->Valor.GetZ() > p1->Valor.GetZ())
    {
        p = p0;
        p0 = p1;
        p1 = p;
    }
    if(p0->Valor.GetZ() > p2->Valor.GetZ())
    {
        p = p0;
        p0 = p2;
        p2 = p;
    }
    if(p1->Valor.GetZ() > p2->Valor.GetZ())
    {
        p = p1;
        p1 = p2;
        p2 = p;
    }
    Va = p0->Valor.GetId();
    Vb = p1->Valor.GetId();
    Vc = p2->Valor.GetId();
}

Face::Face(const Face &outra)
{
    Va = outra.Va;
    Vb = outra.Vb;
    Vc = outra.Vc;
}

Face::Face(const QString ln)
{
    Va = ln.left(8);
    Vc = ln.right(16);
    Vb = Vc.left(8);
    Vc = Vc.right(8);
}

Nos<Ponto> * Face::GetPonto(Nos<Ponto> *pont, const QString v)
{
    while(pont)
    {
        if(pont->Valor.GetId() == v) return pont;
        pont = pont->Segue;
    }
    return nullptr;
}

Ponto Face::GetvA(Nos<Ponto> *pont)
{
    return Ponto(GetPonto(pont, Va)->Valor);
}

Ponto Face::GetvB(Nos<Ponto> *pont)
{
    return Ponto(GetPonto(pont, Vb)->Valor);
}

Ponto Face::GetvC(Nos<Ponto> *pont)
{
    return Ponto(GetPonto(pont, Vc)->Valor);
}

Face Face::operator =(const Face &outra)
{
    Va = outra.Va;
    Vb = outra.Vb;
    Vc = outra.Vc;
    return *this;
}

bool Face::operator ==(const Face outra)
{
    if(Va != outra.Va) return false;
    if(Vb != outra.Vb) return false;
    return (Vc == outra.Vc);
}
