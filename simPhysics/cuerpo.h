#ifndef CUERPO_H
#define CUERPO_H

#include <QGraphicsItem>
#include <utility>

class Cuerpo : public QGraphicsItem
{
public:
    //explicit Cuerpo(QGraphicsItem* parent = nullptr);
    Cuerpo(float m, float x, float y, float vx, float vy);

    std::pair<float, float> pos;
    std::pair<float, float> vel;
    std::pair<float, float> acc;

    //float x, y, vx, vy, ax, ay; // Posición, velocidad, aceleración
    float m; // Masa

    float dt = 1; // Intervalos de tiempo

    void actPos(); // Actualizar posición
    void actVel();
    void actAcc(std::pair<float, float>);

    QRectF boundingRect() const override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
private:

};

#endif // CUERPO_H
