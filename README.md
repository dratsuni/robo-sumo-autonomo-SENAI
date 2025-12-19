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
O sistema do modelo V2 foi construído sobre um chassi impresso em 3D. Os componentes principais utilizados foram:
1. Processamento: 1x Arduino Uno R3 (Microcontrolador ATmega328P).
2. Atuação: 2x Motores DC com caixa de redução (amarelos) e 1x Ponte H L298N (substituída posteriormente).
3. Sensores de Combate: 3x Sensores Ultrassônicos HC-SR04 (posicionamento frontal e lateral).
4. Sensores de Borda: 3x Sensores Infravermelhos (IR) KY-033.

### Justificativa de uso:

## Programação
### Jusiticativa de uso dos Registradores
O projeto foi inteiramente escrito em C. O uso das funções de abstração do Arduino foi evitado. No lugar das funções digitalWrite, analogWrite, digitalRead e pinMode, usamos registradores para extrair o máximo de desempenho do Atmega328P e economizar ciclos de máquina. Além disso, evitamos funções bloqueantes como o pulseIn e usamos interrupção de hardware para detectar mudanças no pino ECHO do sensor ultrassônico HC SR04. O mesmo foi aplicado nos sensores infravermelho KY-033.

Com as interrupções de hardware devidamente ativadas, conseguimos detectar alterações nos pinos dos sensores de forma não bloqueante. Aliviando o processador e economizando ciclos.

## Montagem
- Abordagem modular para facilitar a manutenção. 
- O chassi 3D serviu de base para a fixação dos motores na parte inferior.
- A Ponte H foi centralizada para distribuição equilibrada de peso.

Obs.: jumpers e a protoboard fornecidos no kit apresentaram intermitência mecânica e, como medida corretiva, partes do circuito foram soldadas diretamente e reforçadas para tentar mitigar a instabilidade elétrica causada pela vibração dos motores. 

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
- Instabilidade de Conexões: Os jumpers e a protoboard do kit apresentaram "mau contato" intermitente que desligava o microcontrolador ou falseava leituras dos sensores.
- Fornecimento de Energia: Brown-out (reinício) do Arduino devido as baterias originais não suportarem a corrente de pico dos motores. Foi necessário adaptar baterias de Li-Ion externas.
- Qualidade dos Componentes: A Ponte H original apresentou defeito em um dos canais, exigindo substituição e atrasando a fase de testes integrados. Essa substituição aplica-se também aos sensores ultrassônicos e jumpers.

  ### Possiveis Melhorias
- Considerar substituição total da protoboard por uma Placa de Circuito Impresso (PCI) soldada, a fim de garantir robustez mecânica.






