//  tem alguma coisa insana com a abertura das caixas de diálogo .. as duas abertas ao mesmo tempo!!

#include "arquivo.h"
#include "ui_arquivo.h"

Arquivo::Arquivo(QWidget *parent): QDialog(parent), ui(new Ui::Arquivo)
{
    ui->setupUi(this);
    this->setWindowTitle("Adquirir arquivo");
    ui->pbOk->setText("Ler arquivo");
    ui->pteArq->setVisible(false);
    Buffer.clear();
    Lido = false;
}

bool Arquivo::LerArquivo(QString dir, QString filtro, QString titulo)
{
    QString id = QFileDialog::getOpenFileName(nullptr, titulo, dir, filtro);
    if(id == "") return false;
    QFile arq;
    arq.setFileName(id);
    if(!arq.open(QFile::ReadOnly | QFile::Text))return false;
    Buffer.clear();
    Buffer = arq.readAll();
    arq.close();
    return true;
}

bool Arquivo::LerArquivo(QString filtro, QString titulo)
{
    return LerArquivo(IDIR, filtro, titulo);
}

void Arquivo::on_pbOk_clicked()
{
    while(!Lido)
    {
        if(LerArquivo("Todos (*.*)", "Ler pontos"))
        {
            Lido = true;
            ui->pbOk->setText("Ok");
            ui->pteArq->setVisible(true);
            ui->pteArq->setPlainText(Buffer);
            return;
        }
    }
    Buffer = ui->pteArq->toPlainText();
    this->close();
}

Arquivo::~Arquivo()
{
    delete ui;
}
