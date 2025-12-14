/**
 * @date    Início 29/11/25 10:37
 * @brief   Agrupar estruturas de dados gabarito com ligação singular
 */
#ifndef EDGABARITO_H
#define EDGABARITO_H

/**
 * @brief   Nó de dados de ligação simples
 */
template <class T>
class No
{
public:
    No<T> *Segue;
    T Valor;

    No()
    {
        Segue = nullptr;
        Valor = T();
    }

    No(const T& arg)
    {
        Segue = nullptr;
        Valor = T(arg);
    }
};

/**
 * @brief   Estrutura de lista de ligação simples clássica
 */
template <class T>
class Lista
{
public:
    No<T> *Frente;
    No<T> *Fundo;
    No<T> *Atual;
    uint Count;
    uint CAtual;

    Lista()
    {
        Frente = Fundo = Atual = nullptr;
        Count = CAtual = 0;
    }

    void PushFront(const T& arg)
    {
        No<T> *aponta = new No<T>(arg);
        if(Fundo)
        {
            aponta->Segue = Frente;
            Frente = aponta;
        }
        else Frente = Fundo = aponta;
        Count++;
    }

    void PushBack(const T& arg)
    {
        No<T> *aponta = new No<T>(arg);
        if(Fundo)
        {
            Fundo->Segue = aponta;
            Fundo = aponta;
        }
        else Frente = Fundo = aponta;
        Count++;
    }

    bool PopFront(T &var)
    {
        if(!Frente) return false;
        No<T> *aponta = Frente;
        var = Frente->Valor;
        Frente = Frente->Segue;
        delete aponta;
        Count--;
        return true;
    }

    T PopFront()
    {
        T var;
        if(Frente)
        {
            No<T> *aponta = Frente;
            var = Frente->Valor;
            Frente = Frente->Segue;
            delete aponta;
            Count--;
        }
        return var;
    }

    bool PopBack(T &var)
    {
        if(!Fundo) return false;
        if(Count == 1)
        {
            No<T> *aponta = Fundo;
            var = aponta->Valor;
            Frente = Fundo = nullptr;
            delete aponta;
            Count--;
            return true;
        }
        var = Fundo->Valor;
        No<T> *aponta = Frente;
        while(aponta->Segue != Fundo) aponta = aponta->Segue;
        Fundo = aponta;
        aponta = aponta->Segue;
        delete aponta;
        Count--;
        return true;
    }

    T PopBack()
    {
        T var;
        if(Fundo)
        {
            var = Fundo->Valor;
            No<T> *aponta;
            if(Count == 1)
            {
                aponta = Fundo;
                Frente = Fundo = nullptr;
            }
            else
            {
                aponta = Frente;
                while(aponta->Segue != Fundo) aponta = aponta->Segue;
                Fundo = aponta;
                aponta = aponta->Segue;
            }
            Count--;
            delete aponta;
        }
        return var;
    }

    bool GetFront(T &var)
    {
        if(!Frente) return false;
        var = Frente->Valor;
        return true;
    }

    T GetFront()
    {
        T var;
        if(Frente) var = Frente->Valor;
        return var;
    }

    bool GetBack(T &var)
    {
        if(!Fundo) return false;
        var = Fundo->Valor;
        return true;
    }

    T GetBack()
    {
        T var;
        if(Fundo) var = Fundo->Valor;
        return var;
    }

    bool GetN(T &var, const uint n)
    {
        if(Count < n) return false;
        if(CAtual > n || !Atual)
        {
            Atual = Frente;
            CAtual = 1;
        }
        while(CAtual < n)
        {
            Atual = Atual->Segue;
            CAtual++;
        }
        var = Atual->Valor;
        return true;
    }

    T GetN(const uint n)
    {
        T var;
        if(Count >= n)
        {
            if(CAtual > n || !Atual)
            {
                Atual = Frente;
                CAtual = 1;
            }
            while(CAtual < n)
            {
                Atual = Atual->Segue;
                CAtual++;
            }
            var = Atual->Valor;
        }
        return var;
    }

    uint Length()
    {
        return Count;
    }
};

/**
 * @brief   Estrutura de fila de ligação simples clássica
 */
template <class T>
class Fila
{
private:
    Lista<T> lst;
public:
    Fila()
    {}

    void Push(const T& arg)
    {
        lst.PushBack(arg);
    }

    bool Pop(T &var)
    {
        return lst.PopFront(var);
    }

    T Pop()
    {
        return lst.PopFront();
    }

    bool Primo(T &var)
    {
        return lst.GetFront(var);
    }

    T Primo()
    {
        return lst.GetFront();
    }

    uint Lenght()
    {
        return lst.Length();
    }
};

/**
 * @brief   Estrutura de pilha de ligação simples clássica
 */
template <class T>
class Pilha
{
private:
    Lista<T> lst;
public:
    Pilha()
    {}

    void Push(const T& arg)
    {
        lst.PushFront(arg);
    }

    bool Pop(T &var)
    {
        return lst.PopFront(var);
    }

    T Pop()
    {
        return lst.PopFront();
    }

    bool Top(T &var)
    {
        return lst.GetFront(var);
    }

    T Top()
    {
        return lst.GetFront();
    }

    uint Lenght()
    {
        return lst.Length();
    }
};

#endif // EDGABARITO_H
