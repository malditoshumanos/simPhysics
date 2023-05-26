#include "cuerpo.h"
#include <QPainter>

//Cuerpo::Cuerpo(QGraphicsItem* parent) : QGraphicsItem(parent)
Cuerpo::Cuerpo(float m, float x, float y, float vx, float vy)
{
    this->m = m;
    // Estos son los valores iniciales con que se inicializa el objeto
    this->pos.first = x;
    this->pos.second = y;
    this->vel.first = vx;
    this->vel.second = vy;
    this->acc.first = 0;
    this->acc.second = 0;
}



QRectF Cuerpo::boundingRect() const
{
    // Define and return the bounding rectangle of your item
}

void Cuerpo::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    // Implement the painting code for your item
}


// Creo que se deben correr primero actAcc, luego actPos y finalmente actVel (para que la vi en la ec. para x sea la correcta)
void Cuerpo::actPos(){
    // x = xi + vi*t + (1/2)*a*(t**2)
    this->pos.first += (this->vel.first * dt) + ( (0.5)*(this->acc.first)*(dt*dt) );
    this->pos.second += (this->vel.second * dt) + ( (0.5)*(this->acc.second)*(dt*dt) );

}

void Cuerpo::actVel(){
    // v = vi + a*dt
    this->vel.first += dt * this->acc.first;
    this->vel.second += dt * this->acc.second;
}

void Cuerpo::actAcc(std::pair<float, float> totF){
    // totF es la fuerza total sobre el objeto
    this->acc.first = totF.first / m;
    this->acc.second = totF.second / m;
}

