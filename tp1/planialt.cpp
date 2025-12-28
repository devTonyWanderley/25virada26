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

bool planialt::ExportaFaces()
{
    if(Lf.Empty()) return false;
    Buffer.clear();
    Nos<Face> *pont = Lf.GetPrimo();
//    QString tx;
    while(pont)
    {
        if(Buffer.length()) Buffer += '\n';
//        tx = pont->Valor.GetVa()->Valor.GetId();
//        tx = pont->Valor.FillPreTexto(tx, ' ', 8);
//        Buffer += tx;
        Buffer += pont->Valor.FillPreTexto(pont->Valor.GetVa()->Valor.GetId(), ' ', 8);
//        tx = pont->Valor.GetVb()->Valor.GetId();
//        tx = pont->Valor.FillPreTexto(tx, ' ', 8);
//        Buffer += tx;
        Buffer += pont->Valor.FillPreTexto(pont->Valor.GetVb()->Valor.GetId(), ' ', 8);
//        tx = pont->Valor.GetVc()->Valor.GetId();
//        tx = pont->Valor.FillPreTexto(tx, ' ', 8);
//        Buffer += tx;
        Buffer += pont->Valor.FillPreTexto(pont->Valor.GetVc()->Valor.GetId(), ' ', 8);
        pont = pont->Segue;
    }
    if(!SalvarArquivo(IDIR, "Superfície (*.sup)", "Salvar superfície")) return false;
    return true;
}

bool planialt::ExportaContorno()
{
    if(LPntAux.Empty()) return false;
    Buffer.clear();
    Nos<Ponto> *pont = LPntAux.GetPrimo();
    while(pont)
    {
        if(Buffer.length()) Buffer += '\n';
        Buffer += pont->Valor.FillPreTexto(pont->Valor.GetId(), ' ', 8);
        pont = pont->Segue;
    }
    if(!SalvarArquivo(IDIR, "Contorno (*.con)", "Salvar superfície")) return false;
    return true;
}

uint planialt::NUsoArEmSup(Aresta ar)
{
    uint r = 0;
    Nos<Ponto> *a = ar.GetVini(), *b = ar.GetVfim();
    for(uint i = 0; i < Lf.Length(); i++)
    {
        Nos<Ponto>
            *m = Lf.Getn(i).GetVa(),
            *n = Lf.Getn(i).GetVb(),
            *o = Lf.Getn(i).GetVc();
        if(a == m)
        {
            if(b == n || b == o) r++;
        }
        else if(a == n)
        {
            if(b == m || b == o) r++;
        }
        else if(a == o)
        {
            if(b == m || b == n) r++;
        }
    }
    return r;
}

bool planialt::ArestasExternas()
{
    if(La.Empty()) return false;
    LArAux.Clear();
    for(uint i = 0; i < La.Length(); i++)
    {
        if(NUsoArEmSup(La.Getn(i)) == 1) LArAux.Pushback(La.Getn(i));
    }
    return true;
}

void planialt::EncadeiaPontos()
{
    if(LArAux.Empty()) return;
    LPntAux.Clear();
    Aresta ar = LArAux.Popfront();
    uint nump = LPntAux.Length(), i;
    LPntAux.Pushback(ar.GetVini()->Valor);
    LPntAux.Pushback(ar.GetVfim()->Valor);
    while((!LArAux.Empty()) && (nump != LPntAux.Length()))
    {
        nump = LPntAux.Length();
        i = 0;
        while(i < LArAux.Length())
        {
            ar = LArAux.Getn(i);
            if(ar.GetVini()->Valor == LPntAux.Getfront())
            {
                ar = LArAux.Popn(i);
                LPntAux.Pushfront(ar.GetVfim()->Valor);
            }
            else if(ar.GetVini()->Valor == LPntAux.Getback())
            {
                ar = LArAux.Popn(i);
                LPntAux.Pushback(ar.GetVfim()->Valor);
            }
            else if(ar.GetVfim()->Valor == LPntAux.Getback())
            {
                ar = LArAux.Popn(i);
                LPntAux.Pushback(ar.GetVini()->Valor);
            }
            else if(ar.GetVfim()->Valor == LPntAux.Getfront())
            {
                ar = LArAux.Popn(i);
                LPntAux.Pushfront(ar.GetVini()->Valor);
            }
            else i++;
        }
    }
}

void planialt::on_pbo_clicked()
{
    if(!Passo)  //  passo 0 ..  ler pontos
    {
        if(!LerArquivo("Todos (*.pnt)", "Ler pontos")) return;
        ui->pte->setEnabled(true);
        ui->pte->setPlainText(Buffer);
        ui->pbo->setText("Ler arquivo de arestas");
        GuardaPontos();
        Passo++;
        return;
    }
    if(Passo == 1)  //  passo 1 ..  ler arestas
    {
        if(!LerArquivo("Todos (*.ars)", "Ler arestas")) return;
        ui->pte->setEnabled(true);
        ui->pte->setPlainText(Buffer);
        ui->pbo->setText("Gerar superfície e contorno");
        GuardaArestas();
        Passo++;
        return;
    }
    if(Passo == 2)  //  passo 2 ..  gerar superfície e contorno
    {
        GeraFaces();
        ui->pte->setPlainText(Buffer);
        if(ArestasExternas())
        {
            EncadeiaPontos();
            ui->pbo->setText("Mostrar contorno");
            Passo++;
            return;
        }
        qDebug()
            << "algo errado";
        return;
    }
    if(Passo == 3)  //  passo 3 ..  mostrar contorno
    {
        Buffer.clear();
        for(uint i = 0; i < LPntAux.Length(); i++)
        {
            if(Buffer.length()) Buffer += '\n';
            Buffer += LPntAux.Getn(i).GetId();
        }
        ui->pte->setPlainText(Buffer);
        ui->pbo->setText("Esportar superfície e contorno");
        Passo++;
    }
    if(Passo == 4)  //  passo 4 ..  Esportar superfície e contorno
    {
        if(ExportaFaces())
        {
            if(ExportaContorno())
            {
                Passo = 0;
                ui->pte->setEnabled(false);
                ui->pbo->setText("Ler arquivo de pontos");
                this->setWindowTitle("Gerar superfície");
                return;
            }
        }
    }

    /*

    //  teste de ArestasExternas
    if(ArestasExternas())
    {
        qDebug()
            << LArAux.Length()
            << " Arestas de contorno";
        EncadeiaPontos();
        qDebug()
            << '\n'
            << LArAux.Length()
            << " Arestas de contorno\n"
            << LArAux.Getfront().GetVini()->Valor.GetId()
            << '-'
            << LArAux.Getfront().GetVfim()->Valor.GetId()
            << '\t'
            << LArAux.Getback().GetVini()->Valor.GetId()
            << '-'
            << LArAux.Getback().GetVfim()->Valor.GetId()
            << '\n'
            << LPntAux.Length()
            << " pontos no contorno";
    }
    else
        qDebug() << "algo errado";
    Buffer.clear();
    for(uint i = 0; i < LPntAux.Length(); i++)
    {
        if(Buffer.length()) Buffer += '\n';
        Buffer += LPntAux.Getn(i).GetId();
    }
    ui->pte->setPlainText(Buffer);

    //  passo 3 ..  gerar contorno, calcular área e perímetro
    //  passo 4 ..  gerar curvas de nível
    //  passo 5 ..  salvar elementos gerados
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
    */
}

planialt::~planialt()
{
    delete ui;
}
