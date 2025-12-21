#ifndef GLISTA_H
#define GLISTA_H

#include "gno.h"

template <class G>
class Lista
{
private:
    Nos<G> *Primo;
    Nos<G> *Atu;
    Nos<G> *Fim;
    uint Count;
    uint CAtu;

    void Avante()
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
    }

public:
    Lista()
    {
        Primo = Atu = Fim = nullptr;
        Count = CAtu = 0;
    }

    void Pushfront(const G arg)
    {
        Nos<G> *pont = new Nos<G>(arg);
        if(Primo)
        {
            pont->Segue = Primo;
            Primo = pont;
            CAtu++;
        }
        else
            Primo = Atu = Fim = pont;
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
            Primo = Atu = Fim = pont;
        Count++;
    }

    void Pushn(uint m, const G arg)
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

    G Getn(uint m)
    {
        if(Empty())
        {
            G r;
            return r;
        }
        if(!m)
        {
            Getfront();
            return;
        }
        if(m >= Count)
        {
            Getback();
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
        return Atu->Valor;
    }

    G Popfront()
    {
        G r;
        if(Primo)
        {
            Nos<G> *pont = Primo;
            r = pont->Valor;
            if(Primo->Segue)
            {
                if(CAtu) CAtu--;
                else Atu = Atu->Segue;
                Primo = Primo->Segue;
            }
            else
            {
                Primo = Atu = Fim = nullptr;
            }
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
            {
                Primo = Atu = Fim = nullptr;
                delete pont;
            }
            else
            {
                while(pont->Segue != Fim) pont = pont->Segue;
                if(CAtu == (Count - 1))
                {
                    Atu = pont;
                    CAtu--;
                }
                Fim = pont;
                pont = pont->Segue;
                delete pont;
            }
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

    uint Atual(G &r)
    {
        r = Atu->Valor;
        return CAtu;
    }

    bool Empty()
    {
        return (Count == 0);
    }
};

#endif // GLISTA_H
