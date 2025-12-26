#include "aresta.h"

Aresta::Aresta()
{
    Vi = Vf = "";
    SetKey("-");
}

Aresta::Aresta(const QString ln)
{
    Vi = NormaTexto(ln.left(8));
    Vf = NormaTexto(ln.right(8));
    SetKey((Vi + '-' + Vf));
}

Aresta::Aresta(const QString v0, const QString v1)
{
    Vi = v0;
    Vf = v1;
    SetKey((Vi + '-' + Vf));
}

void Aresta::SetIni(const QString v)
{
    Vi = v;
    SetKey((Vi + '-' + Vf));
}

void Aresta::SetFim(const QString v)
{
    Vf = v;
    SetKey((Vi + '-' + Vf));
}

QString Aresta::GetIni()
{
    return Vi;
}

QString Aresta::GetFim()
{
    return Vf;
}
