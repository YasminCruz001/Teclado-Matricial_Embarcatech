# Projeto: Controle de LEDs e Buzzer com Teclado Matricial

## Descrição
Este projeto é uma tarefa do programa EMBARCATECH para realizar a implementação de um sistema de controle de LEDs RGB e um buzzer usando um teclado matricial 4x4 em uma Raspberry Pi Pico W. Cada tecla do teclado aciona diferentes padrões de iluminação dos LEDs e sinais sonoros no buzzer.

## Funcionalidades
- Leitura do teclado matricial 4x4.
- Acionamento dos LEDs RGB com diferentes combinações.
- Emissão de sons pelo buzzer conforme a tecla pressionada.
- Finalização do programa ao pressionar '*'.

## Hardware Necessário
- Raspberry Pi Pico
- Teclado matricial 4x4
- LED RGB (ou três LEDs individuais: vermelho, verde e azul)
- Buzzer passivo
- Resistores adequados
- Jumpers para conexão

## Mapeamento das Teclas
| Tecla | Ação |
|--------|------------------------------------------------|
| 1      | Acende LED Verde e toca o buzzer brevemente  |
| 2      | Acende LED Azul e toca o buzzer brevemente   |
| 3      | Acende LED Vermelho e toca o buzzer brevemente |
| 4      | Aciona sequência de buzzer                    |
| 5      | Pisca LED Verde                              |
| 6      | Pisca LED Azul                               |
| 7      | Pisca LED Vermelho com toques sonoros       |
| 8      | Sequência de tons sonoros                   |
| 9      | Acende LED Verde e Azul e emite dois tons   |
| 0      | Acende LED Vermelho e Verde com som         |
| A      | Acende LED Azul e toca o buzzer             |
| B      | Sequência de LEDs com som                   |
| C      | Todos os LEDs piscam com som                |
| D      | Acende todos os LEDs                        |
| #      | Sequência de cores e tons                   |
| *      | Finaliza o programa                         |

## Configuração e Execução do Projeto

### 1. Instalação do Wokwi no VS Code
O Wokwi permite simular a execução do código sem a necessidade do hardware físico. Para configurá-lo no VS Code, siga os passos:

1. Instale o [Visual Studio Code](https://code.visualstudio.com/).
2. Instale a extensão **Wokwi for VS Code** na aba de extensões (`Ctrl+Shift+X`).
3. Abra o projeto no VS Code.

### 2. Compilação e Execução no Wokwi

1. Instale o compilador para Raspberry Pi Pico (SDK do RP2040).
2. Compile o projeto utilizando:
   ```sh
   mkdir build && cd build
   cmake ..
   make
   ```
3. Para rodar no Wokwi, use o atalho `Ctrl+Shift+P`, digite **"Wokwi: Start Simulation"** e selecione a opção.
4. O terminal exibirá a saída do código, e o teclado matricial do Wokwi permitirá a interação.

## Link do video no Youtube
https://youtu.be/_yieleeHDm0
