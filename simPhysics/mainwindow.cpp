#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cuerpo.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //timer = new QTimer(this);
    //connect(timer,SIGNAL(timeout()), this, SLOT(update()));


    // SISTEMA 1
    std::ofstream outputFile("output.txt", std::ofstream::trunc); //Eliminar contenido de output.txt
    if (!outputFile.is_open()) {
        std::cout << "Failed to open the output file." << std::endl;
    }
    outputFile.close();

    std::cout << "SISTEMA 1" << std::endl;
    sistema.append(new Cuerpo(70, 0, -7000, 2, 0));
    sistema.append(new Cuerpo(70000, 0, 0, 0, 0));
    sistema.append(new Cuerpo(25, 4000, 5000, -1.6, 1.2));

    QList<QPointF> point1Coords;
    point1Coords.append(QPointF(0, -7000));
    coordList.append(point1Coords);

    QList<QPointF> point2Coords;
    point2Coords.append(QPointF(0, 0));
    coordList.append(point2Coords);

    QList<QPointF> point3Coords;
    point3Coords.append(QPointF(4000, 5000));
    coordList.append(point3Coords);

    actCoords();


    /*
    // DESCOMENTAR PARA ANALIZAR EL SISTEMA 2 (y comentar el sistema 1)
    std::cout << "SISTEMA 2" << std::endl;
    sistema.append(new Cuerpo(50000, 0, 0, 0, 0));
    sistema.append(new Cuerpo(70, -5000, 0, 0, -2));
    sistema.append(new Cuerpo(70, 5000, 0, 0, 2));
    sistema.append(new Cuerpo(70, 0, -5000, 2, 0));
    sistema.append(new Cuerpo(70, 0, 5000, -2, 0));

    QList<QPointF> point1Coords;
    point1Coords.append(QPointF(0, 0));
    coordList.append(point1Coords);

    QList<QPointF> point2Coords;
    point2Coords.append(QPointF(-5000, 0));
    coordList.append(point2Coords);

    QList<QPointF> point3Coords;
    point3Coords.append(QPointF(5000, 0));
    coordList.append(point3Coords);

    QList<QPointF> point4Coords;
    point4Coords.append(QPointF(0, -5000));
    coordList.append(point4Coords);

    QList<QPointF> point5Coords;
    point5Coords.append(QPointF(0, 5000));
    coordList.append(point5Coords);

    actCoords();
    */

    for (int i = 0; i < 10000; ++i) {
        update();
    }


    // **********************************************************************************
    // **********************************************************************************
    // QT STUFF
    // **********************************************************************************
    // **********************************************************************************

    scene = new QGraphicsScene(-500, -500, 1000, 1000);
    ui->graphicsView->setScene(scene);

    // limites de la escena
    l1 = new QGraphicsLineItem(-500, -500, 500,-500);
    l2 = new QGraphicsLineItem(-500, 500, 500, 500);
    l3 = new QGraphicsLineItem(-500,-500,-500,500);
    l4 = new QGraphicsLineItem(500,-500,500,500);

    // Se agregan los limites a la escena
    scene->addItem(l1);
    scene->addItem(l2);
    scene->addItem(l3);
    scene->addItem(l4);



    for(QList<QPointF> bodyList : coordList) {

        for (QPointF coordToGraph : bodyList) {
            float scale = 0.05;
            float xToGraph = (coordToGraph.x() - 2) * scale;
            float yToGraph = ((-1*coordToGraph.y()) - 2) * scale;
            QGraphicsEllipseItem* ellipseItem = new QGraphicsEllipseItem(xToGraph, yToGraph, 4, 4); // Creating an ellipse item with 4x4 size
            scene->addItem(ellipseItem);
        }
    }


}




MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::update()
{
    QList<Cuerpo*> sistemaViejo = sistema;

    for (int i = 0; i < sistema.length(); i++) {
        std::pair<float, float> fuerzaTot(0.0, 0.0);

            for (int j = 0; j < sistemaViejo.length(); j++) {
            if(i == j) continue;
            fuerzaTot = sumarVect(fuerzaTot, findForce(sistema[i], sistemaViejo[j]));  // Obtener la fuerza total sobre el objeto sumando las fuerzas que le ejercen cada uno de los objetos del sistema
        }

        sistema[i]->actAcc(fuerzaTot);
        sistema[i]->actPos();
        sistema[i]->actVel();
    }
    actCoords();
}



// calcular fuerza entre dos cuerpos
std::pair<float, float> MainWindow::findForce(Cuerpo * c1, Cuerpo * c2)
{
    float r = sqrt( pow(c2->pos.first - c1->pos.first, 2) + pow(c2->pos.second - c1->pos.second, 2) );
    float cosTh = (c2->pos.first - c1->pos.first) / r;
    float sinTh = (c2->pos.second - c1->pos.second) / r;

    std::pair<float, float> fuerza;
    float fuerzaMag = (G * c1->m * c2->m) / pow(r, 2);
    fuerza.first = fuerzaMag * cosTh;
    fuerza.second = fuerzaMag * sinTh;

    return fuerza;
}



// Método para sumar dos vectores
std::pair<float, float> MainWindow::sumarVect(std::pair<float, float> v1, std::pair<float, float> v2)
{
    std::pair<float, float> vResultante;
    vResultante.first = v1.first + v2.first;
    vResultante.second = v1.second + v2.second;

    return vResultante;
}



// Método para procesar las posiciones de los objetos
void MainWindow::actCoords()
{
    QString lineToFile;
    for (int i = 0; i < coordList.length(); ++i) {
        QPointF coordToAdd(sistema[i]->pos.first, sistema[i]->pos.second); // Coordenadas del i-ésimo cuerpo del sistema

        coordList[i].append(coordToAdd); // Añadir coordenada a la lista de coordenadas del objeto (que está dentro de coordList)

        lineToFile.append(QString("%1\t%2").arg(coordToAdd.x()).arg(coordToAdd.y()));
        lineToFile.append("\t\t");
    }
    lineToFile.append("\n");

    std::ofstream outputFile("output.txt", std::ofstream::app);
    if (!outputFile.is_open()) {
        std::cout << "Failed to open the output file." << std::endl;
    }
    outputFile << lineToFile.toStdString();
    outputFile.close();
}

