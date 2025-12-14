/**
 * @date    Início 29/11/25 12:41
 * @brief   Agrupar estruturas de dados de pontos e seus auxiliares
 *          Utiliza as estruturas-gabarito de 'edgabarito.h'
 */
#ifndef EDPONTOS_H
#define EDPONTOS_H

#include <QString>
#include <cmath>
#include "edgabarito.h"

#include <QDebug>

#define ORD_CAMPO "NOME", "ABCI", "ORDE", "COTA", "ATRI"
#define COM_CAMPO 4, 8, 8, 6

/**
 * @brief   Tipo pra procura no plano xy
 */
class Locus
{
public:
    Locus();
    Locus(double x, double y);
    Locus(const Locus& outro);
    void set_x(double x);
    void set_y(double y);
    double get_x();
    double get_y();
    Locus operator = (const Locus& outro);
private:
    double X;
    double Y;
};

/**
 * @brief   ..
 * ->   Sobrecarregar construtor para aceitar linha de dados de comprimento fixo e com separador
 *      de dados, parametrizando a órdem e o comprimento dos dados. Para tanto, vou experimentar
 *      enum.
 */
class Ponto
{
public:
    Ponto();
    Ponto(QString id, QString atr, double x, double y, double z);
    Ponto(QString linha);               //  Implementar entrada de linha de dados de comprimento fixo
    Ponto(QString linha, QChar sep);    //  Implementar entrada de linha de dados com separador
    Ponto(const Ponto& outro);
    void setId(QString id);
    void setAtr(QString atr);
    void setX(double x);
    void setY(double y);
    void setZ(double z);
    QString getId();
    QString getAtr();
    double getX();
    double getY();
    double getZ();
    Ponto projEmXy();
    double dist(const Ponto outro);
    Ponto operator = (const Ponto& outro);
    bool operator == (Ponto outro);
    void teste(QString ln);
private:
    QString Nome;
    QString Atri;
    double Abci;
    double Orde;
    double Cota;
};

/**
 * @brief   Compartimento de pontos
 */

class Quadro
{
private:
    double Xc;
    double Yc;
    double Sl;
    double Sa;
public:
    Quadro *NE;
    Quadro *NW;
    Quadro *SW;
    Quadro *SE;
    Lista<Ponto> Lp;
    Quadro();
    Quadro(double xc, double yc, double sl, double sa);
    Quadro(const Quadro& outro);
    Quadro operator = (const Quadro& outro);
    void GetDimQuadro(double &xc, double &yc, double &sl, double &sa);
    double GetXc();
    double GetYc();
    double GetSl();
    double GetSa();
    void SetDimQuadro(double xc, double yc, double sl, double sa);
    void SetXc(double arg);
    void SetYc(double arg);
    void SetSl(double arg);
    void SetSa(double arg);
    void DimQuadro(double xi, double yi, double xa, double ya);
    void DimQuadro(Quadro tronco, bool norte, bool este);
};

#endif // EDPONTOS_H
