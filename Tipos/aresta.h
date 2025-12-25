#ifndef ARESTA_H
#define ARESTA_H

#include "../ED/gno.h"
#include "ponto.h"

class Aresta
{
private:
    QString Vi;
    QString Vf;
    Nos<Ponto> *Lp;

    Nos<Ponto> * GetPonto(const QString id);
public:
    Aresta();
    Aresta(Nos<Ponto> *lp);
    Aresta(Nos<Ponto> *lp, const QString v0, const QString v1);
    Aresta(Nos<Ponto> *lp, const QString ln);

    Ponto GetIni();
    Ponto GetFim();
};

#endif // ARESTA_H
