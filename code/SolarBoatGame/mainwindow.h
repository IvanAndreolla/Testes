#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QProgressBar>
#include <QLabel>
#include <QPushButton>
#include <QFrame>
#include "gamemanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsView *view;

    QWidget *uiLayer;

    // Painel Agrupador
    QFrame *painelHUD;

    QProgressBar *barraBateria;
    QLabel *labelVelocidade;
    QLabel *labelVoltas;
    QLabel *labelPosicao;

    QPushButton *btnPista1;
    QPushButton *btnPista2;
    QPushButton *btnPista3;
    QPushButton *btnReiniciar;

    QPushButton *btnRetomar;
    QPushButton *btnMenuPrincipal;

    QLabel *labelTitulo;

    GameManager *gameManager;
};

#endif // MAINWINDOW_H
