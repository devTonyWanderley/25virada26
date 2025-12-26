#ifndef PLANIALT_H
#define PLANIALT_H

#define IDIR "C:/2025/Soft/InstLocal/"

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include "ed/glista.h"
#include "tipos/ponto.h"
#include "tipos/aresta.h"

/**
 * Fluxo:
 *      Ler pontos
 *      Ler arestas
 *      Gerar faces
 *      Salvar faces
 */

QT_BEGIN_NAMESPACE
namespace Ui {class planialt;}
QT_END_NAMESPACE

//  Gerar e exportar superfície
//      ->  ler e armazenar pontos  ..  ..  ..  ..  ..  ..  ..  ..  ..  ok
//          ->  ler pontos e mostrar no PTE ..  ..  ..  ..  ..  ..  ..  ok
//          ->  armazenar pontos em lista e mostrar no console  ..  ..  ok
//      ->  ler e armazenar arestas
//          ->  ler arestas e mostrar no PTE    ..  ..  ..  ..  ..  ..  ok
//          ->  rever a classe Aresta   ..  ..  ..  ..  ..  ..  ..  ..  ok
//          ->  referenciar os pontos através da aresta
//          ->  armazenar arestas em lista e mostrar no console ..  ..  ok
//      ->  gerar superfície
//          ->  criar / rever a classe Face
//          ->  referenciar os pontos através da face
//          ->  gerar faces
//      ->  exportar superfície

class planialt : public QMainWindow
{
    Q_OBJECT

public:
    planialt(QWidget *parent = nullptr);
    ~planialt();

private slots:
    void on_pbo_clicked();

private:
    Ui::planialt *ui;
    QString Buffer;
    uint Passo;
    Lista<Ponto> Lp;
    Lista<Aresta> La;

    bool LerArquivo(QString dir, QString filtro, QString titulo);
    bool LerArquivo(QString filtro, QString titulo);
    void GuardaPontos();
    void GuardaArestas();
};
#endif // PLANIALT_H
