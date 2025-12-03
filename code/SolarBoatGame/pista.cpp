#include "pista.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include <cstdlib>
#include <cmath>
#include <utility>
#include <QDebug>

Pista::Pista() {
    imgIlha.load(":/ilha.png");
    imgBoiaVermelha.load(":/boia_vermelha.png");
    imgBoiaVerde.load(":/boia_verde.png");

    if (imgIlha.isNull()) qDebug() << "AVISO: ilha.png nao carregou";
    posicaoLargada = Ponto2D(2500, 4000);
}

void Pista::criarIlha(QGraphicsScene *scene, float x, float y, float diametro) {
    float raio = diametro / 2.0f;
    float raioLogico = diametro * 0.3f; // Hitbox

    Obstaculo obs;
    obs.posicao = Ponto2D(x, y);
    obs.raio = raioLogico;
    listaObstaculos.append(obs);

    float iso_x = x - y;
    float iso_y = (x + y) / 2.0f;

    if (!imgIlha.isNull()) {
        QGraphicsPixmapItem *item = scene->addPixmap(imgIlha);
        item->setShapeMode(QGraphicsPixmapItem::HeuristicMaskShape);

        float escala = diametro / (float)imgIlha.width();
        item->setScale(escala);

        float w = imgIlha.width() * escala;
        float h = imgIlha.height() * escala;

        // Ajuste de pivô (pé da ilha)
        item->setPos(iso_x - w/2, iso_y - (h * 0.85f));
        item->setZValue(item->y());

        obstaculosVisuais.append(item);
    } else {
        float hVis = diametro * 0.5f;
        QGraphicsEllipseItem* el = scene->addEllipse(iso_x - raio, iso_y - hVis/2, diametro, hVis, Qt::NoPen, QBrush(Qt::green));
        el->setZValue(5);
        obstaculosVisuais.append(el);
    }
}

void Pista::criarBoia(QGraphicsScene *scene, float x, float y, QColor cor) {
    // Evita sobreposição com ilhas
    for (const Obstaculo& obs : listaObstaculos) {
        if (Ponto2D(x, y).dist(obs.posicao) < (obs.raio + 80.0f)) return;
    }

    float diametro = 100.0f;
    float raioLogico = diametro * 0.25f;

    Obstaculo obs;
    obs.posicao = Ponto2D(x, y);
    obs.raio = raioLogico;
    listaObstaculos.append(obs);

    float iso_x = x - y;
    float iso_y = (x + y) / 2.0f;

    QPixmap* refImg = (cor == Qt::red) ? &imgBoiaVermelha : &imgBoiaVerde;

    if (!refImg->isNull()) {
        QGraphicsPixmapItem *item = scene->addPixmap(*refImg);
        item->setShapeMode(QGraphicsPixmapItem::HeuristicMaskShape);

        float escala = diametro / (float)refImg->width();
        item->setScale(escala);
        float w = refImg->width() * escala;
        float h = refImg->height() * escala;

        // Ajuste de boia (flutuando)
        item->setPos(iso_x - w/2, iso_y - (h * 0.80f));
        item->setZValue(item->y());

        obstaculosVisuais.append(item);
    } else {
        float raio = diametro / 2.0f;
        float hVis = diametro * 0.5f;
        QGraphicsEllipseItem* el = scene->addEllipse(iso_x - raio, iso_y - hVis/2, diametro, hVis, Qt::NoPen, QBrush(cor));
        el->setZValue(5);
        obstaculosVisuais.append(el);
    }
}

void Pista::gerarCenario(QGraphicsScene *scene, Tipo tipo) {
    obstaculosVisuais.clear();
    listaObstaculos.clear();
    listaCheckpoints.clear();

    auto iso = [](float x, float y) { return QPointF(x - y, (x + y) / 2.0f); };

    if (tipo == OVAL_FACIL) {
        // --- PISTA 1: OVAL ---

        // Ilha Central Grande
        criarIlha(scene, 2500, 2500, 1000);

        // Paredes externas
        criarIlha(scene, 500, 500, 800);
        criarIlha(scene, 4500, 500, 800);
        criarIlha(scene, 500, 4500, 800);
        criarIlha(scene, 4500, 4500, 800);

        struct Portao { float x1, y1, x2, y2; };
        QList<Portao> portoes = {
            {2500, 3500, 2500, 4200}, // 0: Largada (Baixo)
            {3200, 3200, 3700, 3700}, // 1: Curva Sudeste
            {3500, 2500, 4200, 2500}, // 2: Reta Direita
            {3200, 1800, 3700, 1300}, // 3: Curva Nordeste
            {2500, 1500, 2500, 800},  // 4: Topo
            {1800, 1800, 1300, 1300}, // 5: Curva Noroeste
            {1500, 2500, 800, 2500},  // 6: Reta Esquerda
            {1800, 3200, 1300, 3700}  // 7: Curva Sudoeste
        };

        for (int i = 0; i < portoes.size(); ++i) {
            Portao p = portoes[i];
            criarBoia(scene, p.x1, p.y1, Qt::red);   // Interna
            criarBoia(scene, p.x2, p.y2, Qt::green); // Externa

            listaCheckpoints.append(new Checkpoint(i, Ponto2D(p.x1, p.y1), Ponto2D(p.x2, p.y2)));

            if (i == 0) {
                posicaoLargada = Ponto2D(2200, 3800);
                QGraphicsLineItem* l = scene->addLine(iso(p.x1, p.y1).x(), iso(p.x1, p.y1).y(),
                                                      iso(p.x2, p.y2).x(), iso(p.x2, p.y2).y(), QPen(Qt::white, 10));
                l->setZValue(0);
            }
        }
    }
    else if (tipo == OITO_MEDIO) {
        // --- PISTA 2: OITO ---
        criarIlha(scene, 2500, 1800, 600); // Ilha Cima
        criarIlha(scene, 2500, 3200, 600); // Ilha Baixo
        criarIlha(scene, 1000, 2500, 800); // Esquerda
        criarIlha(scene, 4000, 2500, 800); // Direita

        struct Portao { float x1, y1, x2, y2; bool invertido; };
        QList<Portao> portoes = {
            {2500, 2500, 3000, 2500, true}, // 0: Largada
            {3200, 1800, 3800, 1800, true},
            {3200, 1000, 3800, 1000, true},
            {2000, 1000, 1400, 1000, true},
            {1800, 1800, 1200, 1800, true},
            {2000, 2500, 2500, 2500, true},  // Cruzamento Invertido
            {1800, 3200, 1200, 3200, true},
            {2000, 4000, 1400, 4000, true},
            {3200, 4000, 3800, 4000, true},
            {3200, 3200, 3800, 3200, true}
        };

        for (int i = 0; i < portoes.size(); ++i) {
            Portao p = portoes[i];
            criarBoia(scene, p.x1, p.y1, p.invertido ? Qt::green : Qt::red);
            criarBoia(scene, p.x2, p.y2, p.invertido ? Qt::red : Qt::green);
            listaCheckpoints.append(new Checkpoint(i, Ponto2D(p.x1, p.y1), Ponto2D(p.x2, p.y2)));

            if (i == 0) {
                posicaoLargada = Ponto2D(2500, 2200);
                QGraphicsLineItem* l = scene->addLine(iso(p.x1, p.y1).x(), iso(p.x1, p.y1).y(),
                                                      iso(p.x2, p.y2).x(), iso(p.x2, p.y2).y(), QPen(Qt::white, 10));
                l->setZValue(0);
            }
        }
    }
    else {
        // --- PISTA 3: SLALOM ---
        for(int x=500; x<4500; x+=800) {
            criarIlha(scene, x, 500, 400); criarIlha(scene, x, 4500, 400);
            if(x % 1600 == 0) criarIlha(scene, x, 2500, 500);
        }

        struct Portao { float x1, y1, x2, y2; };
        QList<Portao> portoes = {
            {1800, 4200, 3200, 4200},
            {1500, 3500, 2100, 3500},
            {2900, 3000, 3500, 3000},
            {1500, 2500, 2100, 2500},
            {2900, 2000, 3500, 2000},
            {1500, 1500, 2100, 1500},
            {1800, 800,  3200, 800}
        };

        for (int i = 0; i < portoes.size(); ++i) {
            Portao p = portoes[i];
            criarBoia(scene, p.x1, p.y1, Qt::red);
            criarBoia(scene, p.x2, p.y2, Qt::green);
            listaCheckpoints.append(new Checkpoint(i, Ponto2D(p.x1, p.y1), Ponto2D(p.x2, p.y2)));

            if (i == 0) {
                posicaoLargada = Ponto2D(2500, 4500);
                QGraphicsLineItem* l = scene->addLine(iso(p.x1, p.y1).x(), iso(p.x1, p.y1).y(),
                                                      iso(p.x2, p.y2).x(), iso(p.x2, p.y2).y(), QPen(Qt::white, 10));
                l->setZValue(0);
            }
        }
    }
}

bool Pista::verificarColisaoVisual(QGraphicsItem *itemBarco, Ponto2D &posObstaculo) {
    for (int i = 0; i < obstaculosVisuais.size(); ++i) {
        QGraphicsItem* obsItem = obstaculosVisuais[i];
        if (!obsItem) continue;

        if (!itemBarco->collidesWithItem(obsItem, Qt::IntersectsItemBoundingRect)) {
            continue;
        }

        if (itemBarco->collidesWithItem(obsItem, Qt::IntersectsItemShape)) {
            if (i < listaObstaculos.size()) {
                posObstaculo = listaObstaculos[i].posicao;
                return true;
            }
        }
    }
    return false;
}

const QList<Checkpoint*>& Pista::getCheckpoints() const { return listaCheckpoints; }
const QList<QGraphicsItem*>& Pista::getObstaculosVisuais() const { return obstaculosVisuais; }
const QList<Pista::Obstaculo>& Pista::getObstaculosLogicos() const { return listaObstaculos; }
Ponto2D Pista::getPosicaoLargada() const { return posicaoLargada; }
