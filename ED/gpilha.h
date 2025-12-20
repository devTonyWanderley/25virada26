#ifndef GPILHA_H
#define GPILHA_H

#include "gno.h"

template <class G>
class Pilha
{
private:
    Nos<G> *Topo;
    uint Count;
public:
    Pilha()
    {
        Topo = nullptr;
        Count = 0;
    }

    void Push(const G arg)
    {
        Nos<G> *pont = new Nos<G>(arg);
        pont->Segue = Topo;
        Topo = pont;
        Count++;
    }

    G Top()
    {
        G r;
        if(Topo) r = Topo->Valor;
        return r;
    }

    bool Top(G &r)
    {
        if(!Topo) return false;
        r = Topo->Valor;
        return true;
    }

    G Pop()
    {
        G r;
        if(Topo)
        {
            r = Topo->Valor;
            Nos<G> *pont = Topo;
            Topo = Topo->Segue;
            delete pont;
            Count--;
        }
        return r;
    }

    bool Pop(G &r)
    {
        if(!Topo) return false;
        r = Topo->Valor;
        Nos<G> *pont = Topo;
        Topo = Topo->Segue;
        delete pont;
        Count--;
        return true;
    }

    uint Lenght()
    {
        return Count;
    }

    bool Empty()
    {
        return (Count == 0);
    }
};

#endif // GPILHA_H
