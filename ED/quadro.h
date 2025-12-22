#ifndef QUADRO_H
#define QUADRO_H

#include "glista.h"
#include "../Tipos/ponto.h"

class Quadro
{
private:
    double Xc;
    double Yc;
    double Sl;
    double Sa;
    Quadro *NE;
    Quadro *NW;
    Quadro *SW;
    Quadro *SE;
    Lista<Ponto> lst;

    void GetCantos(double &xi, double &yi, double &xa, double &ya);
    void Distribui();
public:
    Quadro();
    Quadro(const double xc, const double yc, const double sl, const double sa);
    Quadro(const Quadro &outro);
    Quadro(Quadro &pai, const bool norte, const bool leste);
    void Push(const Ponto p);
    Ponto BuscaEmQ(const double x, const double y);
    Ponto BuscaMaisProx(const double x, const double y);
};

#endif // QUADRO_H
