#ifndef GFILA_H
#define GFILA_H

#include "gno.h"

template <class G>
class Fila
{
private:
    Nos<G> *Primo;
    Nos<G> *Fim;
    uint Count;

    void Decrementa()
    {
        if(!Primo) return;
        Nos<G> *pont = Primo;
        if(Primo == Fim)
            Fim = nullptr;
        Primo = Primo->Segue;
        delete pont;
        Count--;
    }

public:
    Fila()
    {
        Primo = Fim = nullptr;
        Count = 0;
    }

    void Push(const G arg)
    {
        Nos<G> *pont = new Nos<G>(arg);
        if(Empty()) Primo = Fim = pont;
        else
        {
            Fim->Segue = pont;
            Fim = pont;
        }
        Count++;
    }

    G Frente()
    {
        G r;
        if(Primo) r = Primo->Valor;
        return r;
    }

    bool Frente(G &r)
    {
        if(Empty()) return false;
        r = Primo->Valor;
        return true;
    }

    G Pop()
    {
        G r;
        if(Primo)
        {
            r = Primo->Valor;
            Decrementa();
        }
        return r;
    }

    bool Pop(G &r)
    {
        if(Empty()) return false;
        r = Primo->Valor;
        Decrementa();
        return true;
    }

    uint Length()
    {
        return Count;
    }

    bool Empty()
    {
        return (Count == 0);
    }
};

#endif // GFILA_H
