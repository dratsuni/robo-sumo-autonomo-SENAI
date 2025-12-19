# Relatorio do Projeto

## Objetivos
O objetivo principal deste projeto foi o desenvolvimento e a implementação de um robô autônomo para a modalidade "Sumô de Robôs", capaz de operar em uma arena circular respeitando as restrições de peso (1kg) e dimensões estabelecidas.

## Objetivos Específicos
1. Integrar sistemas de hardware e software utilizando arquitetura baseada em HAL (Hardware Abstraction Layer).
2. Implementar lógica de controle via manipulação direta de registradores do microcontrolador ATmega328P para otimização de tempo de resposta.
3. Aplicar conhecimentos de eletrônica na substituição e adaptação de componentes do kit básico para superação de falhas de hardware.

## Descrição 

### Fluxograma do Robô
<img src="fluxograma.png" alt="Fluxograma" width="75%">

## Componentes
1. componente
2. componente
3. componente
4. componente

### Justificativa de uso:

## Programação
### Jusiticativa de uso dos Registradores

apontar também a modularidade do codigo e o HAL

## Montagem

### Esquema do circuito elétrico

![esquema_eletrico](https://imgur.com/a/2QBZJJs)

## Estrátegia

#### A estratégia do robô é dividida em 3 prioridades:

| Prioridade | Condição | Estado | Descrição |
| :---: | :---: | :---: | :--- |
| **1** | Linha Branca | **FLEE** | Verificação da linha branca e fuga |
| **2** | Avistar Inimigo | **ATTACK** | Detecção do inimigo e ataque ativo |
| **3** | Oscioso | **SCAN** | Procurar o inimigo na arena |

---

### Explicação dos Estados do Robô 

  #### Estado FLEE
  * coloco a explicao de como é a fuga e verificações internas extras
  #### Estado ATACK
  * como é o ataque (bem como as estrategias de ataque)
  #### Estado SCAN
  * como é o scaneamento
  
## Testes e Conclusões

  #### Playlist da equipe
  * https://youtube.com/playlist?list=PLKnvuzxRsdl1yls-MqXq9lSY66JDN-sMj&si=i5gbV4IcVIsQtO6N

  ### Dificuldades
  ### Possiveis Melhorias






