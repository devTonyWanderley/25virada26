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
