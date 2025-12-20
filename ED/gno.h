#ifndef GNO_H
#define GNO_H

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

#endif // GNO_H
