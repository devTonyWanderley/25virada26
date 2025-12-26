#ifndef ARESTA_H
#define ARESTA_H

#include "ecivil.h"

class Aresta : public ECivil
{
private:
    QString Vi;
    QString Vf;
public:
    Aresta();
    Aresta(const QString ln);
    Aresta(const QString v0, const QString v1);
    void SetIni(const QString v);
    void SetFim(const QString v);
    QString GetIni();
    QString GetFim();
};

#endif // ARESTA_H
