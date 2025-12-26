#ifndef FACE_H
#define FACE_H

#include "aresta.h"

class Face
{
private:
    QString Va;
    QString Vb;
    QString Vc;

    Nos<Ponto> * GetPonto(Nos<Ponto> *pont, const QString v);
public:
    Face();
    Face(const QString v0, const QString v1, const QString v2, Nos<Ponto> *pont);
    Face(const Face &outra);
    Face(const QString ln);

    Ponto GetvA(Nos<Ponto> *pont);
    Ponto GetvB(Nos<Ponto> *pont);
    Ponto GetvC(Nos<Ponto> *pont);

    Face operator =(const Face &outra);
    bool operator ==(const Face outra);
};

#endif // FACE_H
