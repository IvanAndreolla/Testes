### Diagrama de Casos de Uso

```mermaid
graph TD
    subgraph Sistema: Jogo de Barco Solar
        UC1(Iniciar Nova Corrida)
        UC2(Controlar Barco Solar)
        UC3(Visualizar HUD)
        UC4(Pausar/Retomar Corrida)
        UC5(Gerenciar Energia)
        UC6(Sair da Corrida)
    end

    Ator((Jogador)) --|> UC1
    Ator --|> UC2
    Ator --|> UC3
    Ator --|> UC4
    Ator --|> UC6

    UC2 --|> UC5 : <<includes>>
```
