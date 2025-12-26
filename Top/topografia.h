#ifndef TOPOGRAFIA_H
#define TOPOGRAFIA_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include "ed/glista.h"
#include "tipos/ponto.h"
#include "tipos/aresta.h"

#define IDIR "C:/2025/Soft/InstLocal/"

QT_BEGIN_NAMESPACE
namespace Ui {class Topografia;}
QT_END_NAMESPACE

//  Gerar e exportar superfície
//      ->  ler e armazenar pontos  ..  ok
//      ->  ler e armazenar arestas  ..  ok
//      ->  gerar superfície
//      ->  exportar superfície

class Topografia : public QMainWindow
{
    Q_OBJECT

public:
    Topografia(QWidget *parent = nullptr);
    ~Topografia();

private slots:
    void on_pbLerPts_clicked();

    void on_pbLerArs_clicked();

private:
    Ui::Topografia *ui;
    QString Buffer;
    Lista<Ponto> Lp;
    Lista<Aresta> La;

    bool LerArquivo(QString dir, QString filtro, QString titulo);
    bool LerArquivo(QString filtro, QString titulo);
};
#endif // TOPOGRAFIA_H
