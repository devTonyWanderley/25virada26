#ifndef GLISTA_H
#define GLISTA_H

#include "gno.h"

template <class G>
class Lista             //      ..  reformular ar funções (n):
{
private:
    Nos<G> *Primo;
    //Nos<G> *Atu;
    Nos<G> *Fim;
    uint Count;
    //uint CAtu;

    /*void Avante()
    {
        if(Empty()) return;
        uint n = Count - 1;
        if(CAtu < n)
        {
            Atu = Atu->Segue;
            CAtu++;
        }
    }

    void Retro()
    {
        if(Empty()) return;
        if(CAtu)
        {
            uint n = CAtu;
            CAtu = 0;
            Atu = Primo;
            if(n)
            {
                n--;
                while(CAtu < n)
                {
                    Atu = Atu->Segue;
                    CAtu++;
                }
            }
        }
    }*/

public:
    Lista()
    {
        Primo = Fim = nullptr;
        Count = 0;
    }

    void Pushfront(const G arg)
    {
        Nos<G> *pont = new Nos<G>(arg);
        if(Primo)
        {
            pont->Segue = Primo;
            Primo = pont;
        }
        else
            Primo = Fim = pont;
        Count++;
    }

    void Pushback(const G arg)
    {
        Nos<G> *pont = new Nos<G>(arg);
        if(Fim)
        {
            Fim->Segue = pont;
            Fim = pont;
        }
        else
            Primo = Fim = pont;
        Count++;
    }

    /*void Pushn(uint m, const G arg)
    {
        if(!m)
        {
            Pushfront(arg);
            return;
        }
        if(m >= Count)
        {
            Pushback(arg);
            return;
        }
        m--;
        while(CAtu != m)
        {
            if(m < CAtu)
            {
                Avante();
            }
            if(m > CAtu)
            {
                Retro();
            }
        }
        Nos<G> *pont = new Nos<G>(arg);
        pont->Segue = Atu->Segue;
        Atu->Segue = pont;
        Count++;
    }*/

    void Pushn(uint n, const G arg)
    {
        if(!n)
        {
            Pushfront(arg);
            return;
        }
        if(n >= Count)
        {
            Pushback(arg);
            return;
        }
        uint i = 1;
        Nos<G> *pontl = Primo;
        while(i < n)
        {
            pontl = pontl->Segue;
            i++;
        }
        Nos<G> *pont = new Nos<G>(arg);
        pont->Segue = pontl->Segue;
        pontl->Segue = pont;
        Count++;
    }

    G Getfront()
    {
        if(Empty())
        {
            G r;
            return r;
        }
        return Primo->Valor;
    }

    G Getback()
    {
        if(Empty())
        {
            G r;
            return r;
        }
        return Fim->Valor;
    }

    /*G Getn(uint m)
    {
        G r;
        if(!Empty())
        {
            if(!m)
                r = Getfront();     //      ..  testar Getfront     ..  parece ok.
            else if(m >= Count)
                r = Getback();
            else
            {
                //m--;              //      ..  testar com m=1
                while(CAtu != m)
                {
                    if(m < CAtu)
                    {
                        Avante();
                    }
                    if(m > CAtu)
                    {
                        Retro();
                    }
                }
                r = Atu->Valor;
            }
        }
        return r;
    }*/

    G Getn(uint n)
    {
        G r;
        if(Empty()) return r;
        if(!n) return Getfront();
        if(n >= Count) return Getback();
        uint i = 0;
        Nos<G> *pontl = Primo;
        while(i < n)
        {
            pontl = pontl->Segue;
            i++;
        }
        return pontl->Valor;
    }

    G Popfront()
    {
        G r;
        if(Primo)
        {
            Nos<G> *pont = Primo;
            r = pont->Valor;
            if(Primo->Segue)
                Primo = Primo->Segue;
            else
                Primo = Fim = nullptr;
            delete pont;
            Count--;
        }
        return r;
    }

    G Popback()
    {
        G r;
        if(Fim)
        {
            r = Fim->Valor;
            Nos<G> *pont = Primo;
            if(Fim == Primo)
                Primo = Fim = nullptr;
            else
            {
                while(pont->Segue != Fim) pont = pont->Segue;
                Fim = pont;
                pont = pont->Segue;
            }
            delete pont;
            Count--;
        }
        return r;
    }

    /*
    G Popn(uint n){}
    bool Getfront(G &r){}
    bool Getback(G &r){}
    bool Getn(uint n, G &r){}
    bool Popfront(G &r){}
    bool Popback(G &r){}
    bool Popn(uint n, G &r){}
    */
    uint Length()
    {
        return Count;
    }

    bool Empty()
    {
        return (Count == 0);
    }
};

#endif // GLISTA_H
