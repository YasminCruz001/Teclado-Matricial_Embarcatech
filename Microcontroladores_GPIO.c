#include <stdio.h>
#include "pico/stdlib.h"

// Definições dos pinos dos LEDs RGB
#define LED_GREEN 11
#define LED_BLUE 12
#define LED_RED 13

// Definição do pino do buzzer
#define BUZZER 21

// Configuração do teclado matricial
#define ROWS 4
#define COLS 4

// Pinos para as linhas e colunas do teclado
const uint linhas[ROWS] = {8, 7, 6, 5};
const uint colunas[COLS] = {4, 3, 2, 1};

// Layout do teclado
const char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// Debounce (em milissegundos)
#define DEBOUNCE_TIME_MS 300

// Função para inicializar GPIOs
void init_gpio() {
    // Configura as linhas como saída e colunas como entrada
    for (int i = 0; i < ROWS; i++) {
        gpio_init(linhas[i]);
        gpio_set_dir(linhas[i], GPIO_OUT);
        gpio_put(linhas[i], true); // Estado padrão
    }
    for (int i = 0; i < COLS; i++) {
        gpio_init(colunas[i]);
        gpio_set_dir(colunas[i], GPIO_IN);
        gpio_pull_up(colunas[i]); // Ativa pull-up
    }

    // Configura LEDs e buzzer como saída
    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_put(LED_RED, false);

    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_put(LED_GREEN, false);

    gpio_init(LED_BLUE);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    gpio_put(LED_BLUE, false);

    gpio_init(BUZZER);
    gpio_set_dir(BUZZER, GPIO_OUT);
}

// Função para tocar o buzzer
void tocar_buzzer(int duracao) {
    if (duracao <= 0) return; // Ignora valores inválidos

    while (duracao > 0) {
        gpio_put(BUZZER, true);
        sleep_ms(1);
        gpio_put(BUZZER, false);
        sleep_ms(3);
        duracao -= 4;
    }
}

// Função para ler o teclado matricial
char ler_teclado() {
    for (int row = 0; row < ROWS; row++) {
        gpio_put(linhas[row], false); // Ativa a linha

        for (int col = 0; col < COLS; col++) {
            if (!gpio_get(colunas[col])) { // Coluna baixa
                gpio_put(linhas[row], true); // Restaura a linha
                return keys[row][col];
            }
        }

        gpio_put(linhas[row], true); // Restaura a linha
    }
    return '\0'; // Nenhuma tecla pressionada
}

// Função para ativar/desativar LEDs com temporização
void controlar_led(uint led, bool estado, int duracao_ms) {
    gpio_put(led, estado);
    if (duracao_ms > 0) sleep_ms(duracao_ms);
    gpio_put(led, false);
}

// Função principal
int main() {
    stdio_init_all();  // Inicializa entrada/saída padrão
    init_gpio();       // Configura os GPIOs

    printf("Sistema inicializado com sucesso. Aguardando entrada do teclado...\n");

    while (1) {
        char tecla = ler_teclado();  // Lê a tecla pressionada
        if (tecla != '\0') {         // Se uma tecla foi pressionada
            // Exibe a tecla pressionada no Serial Monitor
            printf("Tecla pressionada: %c\n", tecla);

            // Executa ações com base na tecla pressionada
            switch (tecla) {
                case '1':
                    controlar_led(LED_GREEN, true, 500);
                    tocar_buzzer(100);
                    break;
                case '2':
                    controlar_led(LED_BLUE, true, 500);
                    tocar_buzzer(100);
                    break;
                case '3':
                    controlar_led(LED_RED, true, 500);
                    tocar_buzzer(100);
                    break;
                case '4':
                    printf("Ação personalizada para tecla 4\n");
                    tocar_buzzer(500);
                    break;
                case '5':
                    controlar_led(LED_GREEN, true, 300);
                    break;
                case '6':
                    controlar_led(LED_BLUE, true, 300);
                    break;
                case '7':
                    printf("Ação personalizada para tecla 7\n");
                    controlar_led(LED_RED, true, 200);
                    tocar_buzzer(200);
                    break;
                case '8':
                    tocar_buzzer(300);
                    break;
                case '9':
                    controlar_led(LED_GREEN, true, 150);
                    controlar_led(LED_BLUE, true, 150);
                    tocar_buzzer(150);
                    break;
                case '0':
                    controlar_led(LED_RED, true, 100);
                    controlar_led(LED_GREEN, true, 100);
                    break;
                case 'A':
                    printf("Ação para tecla A\n");
                    controlar_led(LED_BLUE, true, 150);
                    tocar_buzzer(150);
                    break;
                case 'B':
                    printf("Ciclo de LEDs para tecla B\n");
                    controlar_led(LED_GREEN, true, 200);
                    controlar_led(LED_BLUE, true, 200);
                    controlar_led(LED_RED, true, 200);
                    break;
                case 'C':
                    printf("Todos os LEDs piscando (tecla C)\n");
                    for (int i = 0; i < 3; i++) {
                        controlar_led(LED_RED, true, 200);
                        controlar_led(LED_GREEN, true, 200);
                        controlar_led(LED_BLUE, true, 200);
                        sleep_ms(200);
                    }
                    break;
                case 'D':
                    printf("Ativando todos os LEDs (tecla D)\n");
                    controlar_led(LED_RED, true, 500);
                    controlar_led(LED_GREEN, true, 500);
                    controlar_led(LED_BLUE, true, 500);
                    break;
                case '#':
                    printf("Efeito especial (#)\n");
                    controlar_led(LED_BLUE, true, 150);
                    controlar_led(LED_RED, true, 300);
                    controlar_led(LED_GREEN, true, 600);
                    break;
                case '*':
                    printf("Encerrando o programa.\n");
                    return 0;
                default:
                    printf("Tecla %c não configurada.\n", tecla);
            }

            // Tempo de debounce
            sleep_ms(DEBOUNCE_TIME_MS);
        }
    }

    return 0;
}