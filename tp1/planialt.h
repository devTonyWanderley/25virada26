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
 * Criar contorno da superfície:
 *  Fluxo:
 *      Listar as arestas externas
 *      Ordenar arestas em sequencia
 *      Salvar polígono
 */

QT_BEGIN_NAMESPACE
namespace Ui {class planialt;}
QT_END_NAMESPACE

//  Criar e salvar contorno da superfície
//      ->  criar lista de arestas externas     ..  ..  ..  ..  ..  ..  ..  ..  ..  ..  ..  ok
//          ->  criar e testar Popn em glista   ..  ..  ..  ..  ..  ..  ..  ..  ..  ..  ..  ok
//          ->  implementar e testar operador de atribuição em arestas .. cria cópia    ..  ok
//      ->  criar lista de pontos encadeados a partir da lista de arestas       ..  ..  ..  ok
//          ->  acrescentar ao lsp a funcionalidade de desenhar o nome do ponto ..  ..  ..  ok
//      ->  salvar o contorno da superfície     ..  ..  ..  ..  ..  ..  ..  ..  ..  ..  ..  ok
//          -> dividir GeraFaces() em GeraFaces() e SalvaFaces()    ..  ..  ..  ..  ..  ..  ok
//          -> criar o SalvaContorno()      ..  ..  ..  ..  ..  ..  ..  ..  ..  ..  ..  ..  ok

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
    Lista<Ponto> LPntAux;    //  Auxiliar para armazenamento temporário de pontos
    Lista<Aresta> La;
    Lista<Aresta> LArAux;    //  Auxiliar para armazenamento temporário de arestas
    Lista<Face> Lf;

    bool LerArquivo(QString dir, QString filtro, QString titulo);
    bool LerArquivo(QString filtro, QString titulo);
    bool SalvarArquivo(QString dir, QString filtro, QString titulo);
    void GuardaPontos();
    void GuardaArestas();
    void GeraFaces();
    uint NUsoArEmSup(Aresta ar);
    bool ArestasExternas();
    void EncadeiaPontos();
    bool ExportaFaces();
    bool ExportaContorno();
};
#endif // PLANIALT_H
