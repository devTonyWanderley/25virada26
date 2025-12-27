#ifndef PLANIALT_H
#define PLANIALT_H

#define IDIR "C:/2025/Soft/IL2/"

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include "ed/glista.h"
#include "tipos/aresta.h"
#include "tipos/face.h"

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

//  Gerar e exportar superfície     ..  ..  ..  ..  ..  ..  ..  ..  ..  ok
//      ->  ler e armazenar pontos  ..  ..  ..  ..  ..  ..  ..  ..  ..  ok
//          ->  ler pontos e mostrar no PTE ..  ..  ..  ..  ..  ..  ..  ok
//          ->  armazenar pontos em lista e mostrar no console  ..  ..  ok
//      ->  ler e armazenar arestas ..  ..  ..  ..  ..  ..  ..  ..  ..  ok
//          ->  ler arestas e mostrar no PTE    ..  ..  ..  ..  ..  ..  ok
//          ->  rever a classe Aresta   ..  ..  ..  ..  ..  ..  ..  ..  ok
//          ->  armazenar arestas em lista e mostrar no console ..  ..  ok
//      ->  gerar superfície        ..  ..  ..  ..  ..  ..  ..  ..  ..  ok
//          ->  criar / rever a classe Face     ..  ..  ..  ..  ..  ..  ok
//          ->  gerar faces     ..  ..  ..  ..  ..  ..  ..  ..  ..  ..  ok
//      ->  exportar superfície     ..  ..  ..  ..  ..  ..  ..  ..  ..  ok
//          ->  complementar texto      ..  ..  ..  ..  ..  ..  ..  ..  ok
//          ->  apresentar no pte       ..  ..  ..  ..  ..  ..  ..  ..  ok
//          ->  salvar arquivo de faces     ..  ..  ..  ..  ..  ..  ..  ok
//
//  Personalizar extensões de nomes de arquivos, conforme o lsp     ..  ok
//      ->  Alterar diretório de instâncias padrão      ..  ..  ..  ..  ok
//      ->  Seguir fluxo de "ler e armazenar pontos" e alterar      ..  ok
//      ->  Seguir fluxo de "ler e armazenar arestas" e alterar     ..  ok
//      ->  Seguir fluxo de "salvar arquivo de faces" e alterar     ..  ok

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
    Lista<Face> Lf;

    bool LerArquivo(QString dir, QString filtro, QString titulo);
    bool LerArquivo(QString filtro, QString titulo);
    bool SalvarArquivo(QString dir, QString filtro, QString titulo);
    void GuardaPontos();
    void GuardaArestas();
    void GeraFaces();
};
#endif // PLANIALT_H
