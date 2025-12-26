#ifndef ECIVIL_H
#define ECIVIL_H

#include <QString>

class ECivil
{
private:
    QString Key;
public:
    ECivil();
    QString GetKey();
    void SetKey(const QString ch);

    QString NormaTexto(QString arg);
};

#endif // ECIVIL_H
