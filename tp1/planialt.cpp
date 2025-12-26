#include "planialt.h"
#include "ui_planialt.h"

planialt::planialt(QWidget *parent): QMainWindow(parent), ui(new Ui::planialt)
{
    ui->setupUi(this);
    Passo = 0;
    ui->pte->setEnabled(false);
    ui->pbo->setText("Ler arquivo de pontos");
    this->setWindowTitle("Gerar superfície");
}

bool planialt::LerArquivo(QString dir, QString filtro, QString titulo)
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

bool planialt::LerArquivo(QString filtro, QString titulo)
{
    return LerArquivo(IDIR, filtro, titulo);
}

bool planialt::SalvarArquivo(QString dir, QString filtro, QString titulo)
{
    QString id = QFileDialog::getSaveFileName(nullptr, titulo, dir, filtro);
    if(id == "") return false;
    QFile arq;
    arq.setFileName(id);
    if(!arq.open(QFile::WriteOnly | QFile::Text))return false;
    QTextStream out(&arq);
    out << Buffer;
    arq.close();
    return true;
}

void planialt::GuardaPontos()
{
    if(!Buffer.length()) return;
    Lp.Clear();
    while(Buffer.length() > 45)
    {
        Lp.Pushback(Ponto(Buffer.left(45)));
        Buffer = Buffer.right(Buffer.length() - 46);
    }
    qDebug()
        << Lp.Length()
        << " pontos lidos";
}

void planialt::GuardaArestas()
{
    if(!Buffer.length()) return;
    La.Clear();
    while(Buffer.length() > 16)
    {
        La.Pushback(Aresta(Buffer.left(16), Lp.GetPrimo()));
        Buffer = Buffer.right(Buffer.length() - 17);
    }
    qDebug()
        << La.Length()
        << " arestas lidas";
}

void planialt::GeraFaces()
{
    Nos<Aresta> *ai = La.GetPrimo(), *aj, *ak;
    Nos<Ponto> *pa, *pb, *pc;
    uint n;
    while(ai)
    {
        aj = ai->Segue;
        n = 0;
        pa = pb = pc = nullptr;
        while(aj && n < 2)
        {
            if(ai->Valor.GetVini() == aj->Valor.GetVini())
            {
                pa = ai->Valor.GetVini();
                pb = ai->Valor.GetVfim();
                pc = aj->Valor.GetVfim();
            }
            else if(ai->Valor.GetVini() == aj->Valor.GetVfim())
            {
                pa = ai->Valor.GetVini();
                pb = ai->Valor.GetVfim();
                pc = aj->Valor.GetVini();
            }
            else if(ai->Valor.GetVfim() == aj->Valor.GetVfim())
            {
                pa = ai->Valor.GetVfim();
                pb = ai->Valor.GetVini();
                pc = aj->Valor.GetVini();
            }
            else if(ai->Valor.GetVfim() == aj->Valor.GetVini())
            {
                pa = ai->Valor.GetVfim();
                pb = ai->Valor.GetVini();
                pc = aj->Valor.GetVfim();
            }
            if(pa)
            {
                ak = aj->Segue;
                uint m = n;
                while(ak && m == n)
                {
                    if(
                        (ak->Valor.GetVini() == pb || ak->Valor.GetVini() == pc)
                        &&
                        (ak->Valor.GetVfim() == pb || ak->Valor.GetVfim() == pc)
                        )
                    {
                        Lf.Pushback(Face(pa, pb, pc));
                        n++;
                    }
                    ak = ak->Segue;
                }
            }
            pa = pb = pc = nullptr;
            aj = aj->Segue;
        }
        ai = ai->Segue;
    }
    qDebug()
        << Lf.Length()
        << " faces geradas";
    Buffer.clear();
    Nos<Face> *pont = Lf.GetPrimo();
    QString tx;
    while(pont)
    {
        if(Buffer.length()) Buffer += '\n';
        tx = pont->Valor.GetVa()->Valor.GetId();
        tx = pont->Valor.FillPreTexto(tx, ' ', 8);
        Buffer += tx;
        tx = pont->Valor.GetVb()->Valor.GetId();
        tx = pont->Valor.FillPreTexto(tx, ' ', 8);
        Buffer += tx;
        tx = pont->Valor.GetVc()->Valor.GetId();
        tx = pont->Valor.FillPreTexto(tx, ' ', 8);
        Buffer += tx;
        pont = pont->Segue;
    }
    qDebug()
        << Buffer.length()
        << " caracteres";
}

void planialt::on_pbo_clicked()
{
    if(!Passo)
    {
        if(!LerArquivo("Todos (*.*)", "Ler pontos")) return;
        ui->pte->setEnabled(true);
        ui->pte->setPlainText(Buffer);
        ui->pbo->setText("Ler arquivo de arestas");
        GuardaPontos();
        Passo++;
        return;
    }
    if(Passo == 1)
    {
        if(!LerArquivo("Todos (*.*)", "Ler arestas")) return;
        ui->pte->setEnabled(true);
        ui->pte->setPlainText(Buffer);
        ui->pbo->setText("Gerar superfície");
        GuardaArestas();
        Passo++;
        return;
    }
    if(Passo == 2)
    {
        GeraFaces();
        ui->pte->setPlainText(Buffer);
        ui->pbo->setText("Salvar superfície");
        Passo++;
        return;
    }
    if(Passo == 3)
    {
        if(Buffer.length())
        {
            if(!SalvarArquivo(IDIR, "Superfície (*.sup)", "Salvar superfície"))
                qDebug()
                    << "Algo errado";
        }
    }
    Passo = 0;
    ui->pte->setEnabled(false);
    ui->pbo->setText("Ler arquivo de pontos");
    this->setWindowTitle("Gerar superfície");
}

planialt::~planialt()
{
    delete ui;
}
