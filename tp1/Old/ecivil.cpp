#include "ecivil.h"

ECivil::ECivil()
{
    Key = "";
}

QString ECivil::GetKey()
{
    return Key;
}

void ECivil::SetKey(const QString ch)
{
    Key = ch;
}

QString ECivil::NormaTexto(QString arg)
{
    QChar c;
    bool flg = true;
    while(flg)
    {
        c = *arg.data();
        if((c >= '0' && c <='9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) flg = false;
        else arg = arg.right(arg.length() - 1);
    }
    return arg;
}
