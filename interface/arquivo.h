#ifndef ARQUIVO_H
#define ARQUIVO_H

#include <QDialog>
#include <QFile>
#include <QFileDialog>

#define IDIR "C:/2025/Soft/InstLocal/"

namespace Ui {class Arquivo;}

class Arquivo : public QDialog
{
    Q_OBJECT

public:
    QString Buffer;
    explicit Arquivo(QWidget *parent = nullptr);
    ~Arquivo();

private slots:
    void on_pbOk_clicked();

private:
    Ui::Arquivo *ui;
    bool Lido;
    bool LerArquivo(QString dir, QString filtro, QString titulo);
    bool LerArquivo(QString filtro, QString titulo);
};

#endif // ARQUIVO_H
