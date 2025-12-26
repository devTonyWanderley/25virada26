#include "aresta.h"

Aresta::Aresta()
{
    Lp = nullptr;
    Vi = Vf = "";
}

Aresta::Aresta(Nos<Ponto> *lp)
{
    Lp = lp;
    Vi = Vf = "";
}

Aresta::Aresta(Nos<Ponto> *lp, const QString v0, const QString v1)
{
    Lp = lp;
    Nos<Ponto> *va = GetPonto(v0), *vb = GetPonto(v1);
    if(!va || !vb)
        Vi = Vf = "";
    else
    {
        if(va->Valor.GetZ() < vb->Valor.GetZ())
        {
            Vi = v0;
            Vf = v1;
        }
        else
        {
            Vi = v1;
            Vf = v0;
        }
    }
}

Aresta::Aresta(Nos<Ponto> *lp, const QString ln)
{
    Lp = lp;
    QString v0 = ln.left(8), v1 = ln.right(8);
    Nos<Ponto> *va = GetPonto(v0), *vb = GetPonto(v1);
    if(!va || !vb)
        Vi = Vf = "";
    else
    {
        if(va->Valor.GetZ() < vb->Valor.GetZ())
        {
            Vi = v0;
            Vf = v1;
        }
        else
        {
            Vi = v1;
            Vf = v0;
        }
    }
}

Nos<Ponto> * Aresta::GetPonto(const QString id)
{
    Nos<Ponto> * pont = Lp;
    while(pont)
    {
        if(pont->Valor.GetId() == id)
            return pont;
        pont = pont->Segue;
    }
    return nullptr;
}

Ponto Aresta::GetIni()
{
    return Ponto(GetPonto(Vi)->Valor);
}

Ponto Aresta::GetFim()
{
    return Ponto(GetPonto(Vf)->Valor);
}

Aresta Aresta::operator =(const Aresta &outra)
{
    Vi = outra.Vi;
    Vf = outra.Vf;
    Lp = outra.Lp;
    return *this;
}

bool Aresta::operator ==(const Aresta outra)
{
    if(Vi != outra.Vi) return false;
    if(Vf != outra.Vf) return false;
    return (Lp == outra.Lp);
}
