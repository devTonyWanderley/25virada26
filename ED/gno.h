#ifndef GNO_H
#define GNO_H

#include <QString>

template <class G>
class Nos
{
public:
    Nos<G> *Segue;
    G Valor;
    Nos()
    {
        Segue = nullptr;
        Valor = G();
    }

    Nos(const G &arg)
    {
        Segue = nullptr;
        Valor = G(arg);
    }
};

template <class G>
class Nod
{
public:
    Nod<G> *Smais;
    Nod<G> *Smenos;
    G Valor;
    Nod()
    {
        Smais = Smenos = nullptr;
        Valor = G();
    }
    Nod(const G &arg)
    {
        Smais = Smenos = nullptr;
        Valor = G(arg);
    }
};

#endif // GNO_H
