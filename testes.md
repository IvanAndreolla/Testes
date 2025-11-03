# Testes

>[!NOTE]
> Relatar o processo de testes do sistema, especificando quais testes foram realizados e os resultados obtidos.

Foram planejados dois tipos principais de testes para garantir a qualidade e o funcionamento correto do jogo:

### Testes de Unidade

Testes focados em verificar o funcionamento de classes e métodos de forma isolada.
* **Classe **:
    * **Teste de Aceleração**: Verificar se o método  aumenta a velocidade e diminui a bateria na proporção correta.
    * **Teste de Carregamento**: Verificar se o método  aumenta o nível da bateria corretamente.
    * **Teste de Limites**: Verificar se a bateria não ultrapassa 100% e não fica abaixo de 0%.
* **Classe **:
    * **Teste de Checkpoint**: Verificar se a lógica de passagem por um checkpoint funciona e se a contagem de voltas é incrementada corretamente.

### Testes de Jogo (Playtesting)

Testes realizados por um jogador para avaliar a experiência de jogo, a jogabilidade e a dificuldade.
* **Teste de Jogabilidade**: Avaliar se os controles do barco são responsivos e intuitivos.
* **Teste de Balanceamento**: Verificar se o consumo e a geração de energia estão bem calibrados. A corrida é desafiadora, mas não impossível?
* **Teste de Colisão**: Navegar pela pista e verificar se a detecção de colisão com os limites e obstáculos está funcionando como esperado.
* **Teste de Condição de Vitória**: Completar uma corrida para garantir que a tela de vitória é acionada corretamente.

<div align="center">

[Retroceder](implementacao.md) | [Início](README.md)

</div>
