#ifndef PONTO_H
#define PONTO_H

#include <QString>

class Ponto
{
private:
    QString Nome;
    QString Atri;
    double Abci;
    double Orde;
    double Cota;

    double LerDouble(QString arg);
    bool LerLinha(QString &ln, QString &id, QString &atr, double &x, double &y, double &z);
public:
    Ponto(const QString id, const QString atr, const double x, const double y, const double z);     //  Valores
    Ponto();                                                                                        //  Vazio
    Ponto(const Ponto& outro);                                                                      //  Cópia
    Ponto(const QString ln);                                                                        //  Comprimento fixo
    void SetId(QString id);
    void SetAtr(QString atr);
    void SetX(double x);
    void SetY(double y);
    void SetZ(double z);
    QString GetId();
    QString GetAtr();
    double GetX();
    double GetY();
    double GetZ();
    Ponto operator = (const Ponto& outro);
    bool operator == (const Ponto outro);
};

#endif // PONTO_H
