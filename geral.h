/**
 * edgabarito.h -> estruturas clássicas lista, fila e pilha .. revisar
 * edpontos.h & .cpp -> estrutura de pontos em quadro .. revisar
 *
 * ->   Iniciar por ler/editar arquivo  ..  |   ..  Iniciado. Posteriormente, criar funcionalidades.
 * ->   Introduzir as estruturas de dados e fazer a devida revisão  ..  |   ..  Introduzido,
 *      inclusive com ensaio de parametrização de entrada de dados de comprimento fixo na classe Ponto
 * ->   Sobrecarregar Pop & Top e afins em edgabarito, com retorno <T> .. comitar agora
 */

#ifndef GERAL_H
#define GERAL_H

#include <QMainWindow>
#include "interface/arquivo.h"
//#include "ED/edpontos.h"
#include "ED/gpilha.h"
#include "ED/gfila.h"

QT_BEGIN_NAMESPACE
namespace Ui {class Geral;}
QT_END_NAMESPACE

class Geral : public QMainWindow
{
    Q_OBJECT

public:
    Geral(QWidget *parent = nullptr);
    ~Geral();

private slots:
    void on_pbOpera_clicked();

private:
    Ui::Geral *ui;
    Arquivo *cda;
};
#endif // GERAL_H
