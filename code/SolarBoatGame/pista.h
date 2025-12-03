#ifndef PISTA_H
#define PISTA_H

#include <QList>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPixmap>
#include "ponto2d.h"
#include "barcosolar.h"
#include "checkpoint.h"

class Pista
{
public:
    Pista();

    enum Tipo { OVAL_FACIL, OITO_MEDIO, SLALOM_DIFICIL };

    struct Obstaculo {
        Ponto2D posicao;
        float raio;
    };

    void gerarCenario(QGraphicsScene *scene, Tipo tipo);
    bool verificarColisaoVisual(QGraphicsItem *itemBarco, Ponto2D &posObstaculo);

    const QList<Checkpoint*>& getCheckpoints() const;
    const QList<QGraphicsItem*>& getObstaculosVisuais() const;
    Ponto2D getPosicaoLargada() const;
    const QList<Obstaculo>& getObstaculosLogicos() const;

private:
    QList<Obstaculo> listaObstaculos;
    QList<QGraphicsItem*> obstaculosVisuais;
    QList<Checkpoint*> listaCheckpoints;
    Ponto2D posicaoLargada;

    QPixmap imgIlha;
    QPixmap imgBoiaVermelha;
    QPixmap imgBoiaVerde;

    void criarIlha(QGraphicsScene *scene, float x, float y, float diametro);
    void criarBoia(QGraphicsScene *scene, float x, float y, QColor cor);
};

#endif // PISTA_H
