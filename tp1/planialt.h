#ifndef PLANIALT_H
#define PLANIALT_H

#define IDIR "C:/2025/Soft/InstLocal/"

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>

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
//      ->  ler e armazenar pontos
//          ->  ler pontos e mostrar no PTE ..  ..  ..  ..  ..  ..  ..  ok
//          ->  armazenar pontos em lista e mostrar no console
//      ->  ler e armazenar arestas
//          ->  ler arestas e mostrar no PTE ..  ..  ..  ..  ..  ..  ..  ok
//          ->  rever a classe Aresta
//          ->  rever a classe Lista - procura por chave
//          ->  armazenar arestas em lista e mostrar no console
//      ->  gerar superfície
//          ->  criar / rever a classe Face
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

    bool LerArquivo(QString dir, QString filtro, QString titulo);
    bool LerArquivo(QString filtro, QString titulo);
};
#endif // PLANIALT_H
