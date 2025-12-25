#ifndef TOPOGRAFIA_H
#define TOPOGRAFIA_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {class Topografia;}
QT_END_NAMESPACE

//  Gerar e exportar superfície
//      ->  ler e armazenar pontos
//      ->  ler e armazenar arestas
//      ->  gerar superfície

class Topografia : public QMainWindow
{
    Q_OBJECT

public:
    Topografia(QWidget *parent = nullptr);
    ~Topografia();

private:
    Ui::Topografia *ui;
};
#endif // TOPOGRAFIA_H
