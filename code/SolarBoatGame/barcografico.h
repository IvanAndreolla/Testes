#ifndef BARCOGRAFICO_H
#define BARCOGRAFICO_H

#include "gameobjectgrafico.h"
#include <QPainter>
#include <QPixmap>
#include <QPainterPath>
#include <QVector>

class BarcoGrafico : public GameObjectGrafico
{
    Q_OBJECT
public:
    BarcoGrafico(QGraphicsItem *parent = nullptr);

    void atualizarPosicaoTela(Ponto2D posicaoLogica, float anguloLogico) override;

    void atualizarDebugInfo(Ponto2D motor, Ponto2D arrasto, Ponto2D resultante, float leme);
    void setDebug(bool ativado);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    QVector<QPixmap> frames;
    QVector<QPainterPath> formas;
    int indiceAtual;

    // Debug
    bool debugEnabled;
    Ponto2D vMotor, vArrasto, vRes;
    float valLeme;
    float anguloLogicoAtual;
};

#endif // BARCOGRAFICO_H
