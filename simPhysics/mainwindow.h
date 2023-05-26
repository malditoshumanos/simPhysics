#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QList>
#include <QPointF>
#include <QString>

#include <iostream>
#include <cmath>
#include <fstream>

#include "cuerpo.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();      

private:
    Ui::MainWindow *ui;

    QGraphicsScene *scene;
    //limites
    QGraphicsLineItem *l1;
    QGraphicsLineItem *l2;
    QGraphicsLineItem *l3;
    QGraphicsLineItem *l4;

    // temporizador para el pulso
    QTimer *timer;

    // crear lista de objetos sisas
    QList<Cuerpo*> sistema;
    QList<QList<QPointF>> coordList; // Lista de listas de coordenadas de cada objeto del sistema

    // actualizar las listad e coordenadas
    void actCoords();

    // calcular fuerza entre dos cuerpos
    float G = 1; // constante gravitacional
    std::pair<float, float> findForce(Cuerpo *, Cuerpo *);
    std::pair<float, float> sumarVect(std::pair<float, float>, std::pair<float, float>);

public slots:
    void update();
};
#endif // MAINWINDOW_H
