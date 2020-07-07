#include "principal.h"
#include "ui_principal.h"
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

Principal::Principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Principal)
{
    ui->setupUi(this);
    connect(ui->cmdCalcular,SIGNAL(released()),this,SLOT(calcular()));
    connect(ui->mnuCalcular,SIGNAL(triggered(bool)),this,SLOT(calcular()));
    connect(ui->mnuSalir,SIGNAL(triggered(bool)),this,SLOT(close()));
    connect(ui->mnuGuardar,SIGNAL(triggered(bool)),this,SLOT(guardar()));
    connect(ui->mnuAcercade,SIGNAL(triggered(bool)),this,SLOT(info()));
    connect(ui->mnuAbrir,SIGNAL(triggered(bool)),this,SLOT(abrir()));

}

Principal::~Principal()
{
    delete ui;
}

void Principal::calcular()
{

    //Obtener datos
    QString nombre = ui->inNombre->text();
    int horas = ui->inHoras->value();
    float const HORA_EXTRA = 20.10;

    //Calcular horas extra

    int extra = 0;
    if(horas > 40){
        extra = horas -40;
        horas= 40;
    }
    if(nombre =="" || horas == 0){
        ui->statusbar->showMessage("No se ha ingresado datos para calcular",2000);
        return;
    }

    //Calculo de salario
    float salario =0;

    if(ui->inMatutina->isChecked()){
        salario = horas * 5.15 + extra *HORA_EXTRA;
    }else if(ui->inVespertina->isChecked()){
        salario = horas * 8.50 + extra * HORA_EXTRA;

    }else if(ui->inNocturna->isChecked()){
        salario = horas * 12.65 + extra * HORA_EXTRA;
    }

    //Calcular el descuento
    float descuento =salario * 9.5 / 100;
    float salario_neto = salario- descuento;

    //Imprimir resultados
    QString resultado = "\nObrero" + nombre +"\n";
    resultado +="Salario: $"+ QString::number(salario)+"\n";
    resultado +="Descuento(9.5%): $"+ QString::number(descuento)+"\n";
    resultado +="Salario neto: $"+ QString::number(salario_neto)+"\n";
    resultado +="--\n";

    ui->outResultado->appendPlainText(resultado);
    limpiar();
}

void Principal::guardar()
{
    QString fileName = QFileDialog::getSaveFileName(this,"Guardar datos",QDir::home().absolutePath(), "Archivo de texto (*.txt)");
    QFile data(fileName);

    if(data.open(QFile::WriteOnly | QFile::Truncate)){

       QTextStream salida(&data);
       salida << ui->outResultado->toPlainText();
       ui->statusbar->showMessage("Datos almacenados en"+fileName,5000);
    }
    data.close();
}

void Principal::info()
{
    QMessageBox::information(this,"acerca de","Salary Calculator\n Desarrollador: Mateo Calero\n Ultima actualización: Sab,4,Jun,2020\n Iconos diseñados por <a href=https://www.flaticon.es/autores/monkik title=monkik>monkik</a> from <a href=https://www.flaticon.es/ title=Flaticon> www.flaticon.es</a>");
}

void Principal::abrir()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Abrir datos",QDir::home().absolutePath(), "Archivo de texto (*.txt)");
    QFile data(fileName);

    if(!fileName.isEmpty()){
        QFile file(fileName);
        if(file.open(QFile::ReadOnly)){
            ui->outResultado->setPlainText(file.readAll());
        }
    }

    data.close();

}

void Principal::limpiar()
{
    ui->inNombre->setText("");
    ui->inHoras->setValue(0);
    ui->inMatutina->setChecked(true);
    ui->inNombre->setFocus();

}


