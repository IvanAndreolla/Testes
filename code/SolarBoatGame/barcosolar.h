#ifndef BARCOSOLAR_H
#define BARCOSOLAR_H

#include "ponto2d.h"
#include <QString>

class BarcoSolar
{
protected:
    Ponto2D posicao;
    Ponto2D velocidade;
    Ponto2D aceleracao;

    float massa;
    float angulo;
    float velocidadeAngular;
    float aceleracaoAngular;

    float nivelBateria;
    float capacidadeBateria;
    float taxaConsumo;
    float taxaRecarga;
    float intensidadeSolar;

    int voltaAtual;
    int proximoCheckpointId;
    float raioColisao;

    QString nome;
    bool terminado;

    // --- VARIÁVEIS DE DEBUG ---
    Ponto2D debugForcaMotor;
    Ponto2D debugForcaArrasto;
    Ponto2D debugForcaResultante;
    float debugAnguloLeme; // Para saber quanto o leme está virado

public:
    BarcoSolar(float x, float y, QString nome);

    void resetar(float x, float y);
    void limparDebug(); // Zera os vetores no começo do frame

    void setIntensidadeSolar(float valor);

    void aplicarForca(Ponto2D forca);
    void aplicarHidrodinamica();
    void verificarLimitesMapa();

    void chocar(Ponto2D posObstaculo);
    void colidirComBarco(BarcoSolar* outroBarco);

    void atualizar(float deltaTime);

    void acelerar();
    void virar(float val);
    void carregarBateria();

    void buscarAlvo(Ponto2D alvo);
    void incrementarCheckpoint(int totalCheckpoints);

    void setTerminado(bool t);
    bool isTerminado() const;

    Ponto2D getPosicao() const;
    float getAngulo() const;
    float getBateria() const;
    float getVelocidadeAtual() const;
    int getProximoCheckpointId() const;
    int getVoltaAtual() const;
    float getRaioColisao() const;
    QString getNome() const;

    int getScoreCorrida() const;

    // Getters para o Gráfico desenhar
    Ponto2D getDebugForcaMotor() const;
    Ponto2D getDebugForcaArrasto() const;
    Ponto2D getDebugForcaResultante() const;
    float getDebugAnguloLeme() const;
};

#endif // BARCOSOLAR_H
