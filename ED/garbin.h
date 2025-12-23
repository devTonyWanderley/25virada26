#ifndef GARBIN_H
#define GARBIN_H

#include "gno.h"

#include <QDebug>

template <class G>
class Arbin
{
private:
    Nod<G> *Raiz;
    uint Count;

    void Equilibra(){}
public:
    Arbin()
    {
        Raiz = nullptr;
        Count = 0;
    }

    void Insere(const G arg)
    {
        if(!Raiz)
        {
            Raiz = new Nod<G>(arg);
            Count++;
            return;
        }
        Nod<G> *pont = Raiz;
        while(true)
        {
            if(arg > pont->Valor)
            {
                if(pont->Smais)
                    pont = pont->Smais;
                else
                {
                    pont->Smais = new Nod<G>(arg);
                    Count++;
                    break;
                }
            }
            else
            {
                if(pont->Smenos)
                    pont = pont->Smenos;
                else
                {
                    pont->Smenos = new Nod<G>(arg);
                    Count++;
                    break;
                }
            }
        }
    }

    void Pre(Nod<G> *no)
    {
        if(!no) return;
        qDebug()
            << no->Valor;
        Pre(no->Smenos);
        Pre(no->Smais);
    }

    void Pre()
    {
        Pre(Raiz);
    }

    void Ordenada(Nod<G> *no)
    {
        if(!no) return;
        Ordenada(no->Smenos);
        qDebug()
            << no->Valor;
        Ordenada(no->Smais);
    }

    void Ordenada()
    {
        Ordenada(Raiz);
    }

    void Pos(Nod<G> *no)
    {
        if(!no) return;
        Pre(no->Smenos);
        Pre(no->Smais);
        qDebug()
            << no->Valor;
    }

    void Pos()
    {
        Pos(Raiz);
    }


    G Ler(const G li, const G ls){return li;}
    G Retira(const G li, const G ls){return li;}
    uint Length()
    {
        return Count;
    }

    uint Hight(Nod<G> *no)
    {
        if(!no) return 0;
        uint he = Hight(no->Smenos);
        uint hd = Hight(no->Smais);
        if(he > hd)
            return he + 1;
        else
            return hd + 1;
    }

    uint Hight()
    {
        return Hight(Raiz);
    }

    bool Empty()
    {
        return (Count == 0);
    }
};

#endif // GARBIN_H
