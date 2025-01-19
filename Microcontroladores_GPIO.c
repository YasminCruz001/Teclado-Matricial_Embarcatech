#include <stdio.h>
#include "pico/stdlib.h"

// Pinos dos LEDs RGB
#define LED_GREEN 11
#define LED_BLUE 12
#define LED_RED 13

// Pino do buzzer
#define BUZZER 21

// Configuração das dimensões do teclado matricial
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

// Inicialização dos GPIOs
void init_gpio() {
    // Configura linhas como saída e colunas como entrada
    for (int i = 0; i < ROWS; i++) {
        gpio_init(linhas[i]);
        gpio_set_dir(linhas[i], GPIO_OUT);
        gpio_put(linhas[i], true);
    }
    for (int i = 0; i < COLS; i++) {
        gpio_init(colunas[i]);
        gpio_set_dir(colunas[i], GPIO_IN);
        gpio_pull_up(colunas[i]);
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

// Função para tocar o buzzer por um período
void tocar_buzzer(int duracao) {
    int tempo = duracao;
    while (tempo > 0) {
        gpio_put(BUZZER, true); // Ligar buzzer
        sleep_ms(1);            
        tempo--;
        gpio_put(BUZZER, false); // Desligar buzzer
        sleep_ms(3);             
        tempo -= 3;
    }
}

// Lê o teclado matricial
char ler_teclado() {
    for (int row = 0; row < ROWS; row++) {
        gpio_put(linhas[row], false);  // Ativa linha
        for (int col = 0; col < COLS; col++) {
            if (!gpio_get(colunas[col])) {  // Checa se a coluna está baixa
                gpio_put(linhas[row], true);
                return keys[row][col];
            }
        }
        gpio_put(linhas[row], true);  // Desativa linha
    }
    return '\0';
}

// Função principal
int main() {
    stdio_init_all();  // Inicializa o sistema padrão de entrada/saída
    init_gpio();       // Inicializa os pinos GPIO

    printf("Sistema inicializado com sucesso. Aguardando entrada do teclado...\n");

    while (1) {
        char tecla = ler_teclado();  // Lê a tecla pressionada
        if (tecla != '\0') {
            printf("Tecla pressionada: %c\n", tecla);

            // Exemplo de reações para cada tecla
            switch (tecla) {
                case '1':
                    gpio_put(LED_GREEN, true);
                    tocar_buzzer(100);
                    sleep_ms(500);
                    gpio_put(LED_GREEN, false);
                    break;
                case '2':
                    gpio_put(LED_BLUE, true);
                    tocar_buzzer(100);
                    sleep_ms(500);
                    gpio_put(LED_BLUE, false);
                    break;
                case '3':
                    gpio_put(LED_RED, true);
                    tocar_buzzer(100);
                    sleep_ms(500);
                    gpio_put(LED_RED, false);
                    break;
                case '4':
                    printf("Ação personalizada para tecla 4\n");
                    tocar_buzzer(200);
                    break;
                case '5':
                    printf("Ação personalizada para tecla 5\n");
                    gpio_put(LED_GREEN, true);
                    sleep_ms(300);
                    gpio_put(LED_GREEN, false);
                    break;
                case '6':
                    printf("Ação personalizada para tecla 6\n");
                    gpio_put(LED_BLUE, true);
                    sleep_ms(300);
                    gpio_put(LED_BLUE, false);
                    break;
                case '7':
                    printf("Ação personalizada para tecla 7\n");
                    gpio_put(LED_RED, true);
                    sleep_ms(300);
                    gpio_put(LED_RED, false);
                    break;
                case '8':
                    printf("Ação personalizada para tecla 8\n");
                    tocar_buzzer(300);
                    break;
                case '9':
                    printf("Ação personalizada para tecla 9\n");
                    gpio_put(LED_GREEN, true);
                    gpio_put(LED_BLUE, true);
                    sleep_ms(300);
                    gpio_put(LED_GREEN, false);
                    gpio_put(LED_BLUE, false);
                    break;
                case '0':
                    printf("Ação personalizada para tecla 0\n");
                    gpio_put(LED_RED, true);
                    gpio_put(LED_GREEN, true);
                    sleep_ms(300);
                    gpio_put(LED_RED, false);
                    gpio_put(LED_GREEN, false);
                    break;
                case 'A':
                    printf("Ação para tecla A: Ativando LED azul e buzzer.\n");
                    gpio_put(LED_BLUE, true);
                    tocar_buzzer(150);
                    gpio_put(LED_BLUE, false);
                    break;
                case 'B':
                    printf("Ação para tecla B: Ciclo de LEDs.\n");
                    gpio_put(LED_GREEN, true);
                    sleep_ms(200);
                    gpio_put(LED_GREEN, false);
                    gpio_put(LED_BLUE, true);
                    sleep_ms(200);
                    gpio_put(LED_BLUE, false);
                    gpio_put(LED_RED, true);
                    sleep_ms(200);
                    gpio_put(LED_RED, false);
                    break;
                case 'C':
                    printf("Ação para tecla C: Todos os LEDs piscando.\n");
                    for (int i = 0; i < 3; i++) {
                        gpio_put(LED_RED, true);
                        gpio_put(LED_GREEN, true);
                        gpio_put(LED_BLUE, true);
                        sleep_ms(200);
                        gpio_put(LED_RED, false);
                        gpio_put(LED_GREEN, false);
                        gpio_put(LED_BLUE, false);
                        sleep_ms(200);
                    }
                    break;
                case 'D':
                    printf("Ação para tecla D: Ativando todos os LEDs.\n");
                    gpio_put(LED_RED, true);
                    gpio_put(LED_GREEN, true);
                    gpio_put(LED_BLUE, true);
                    sleep_ms(500);
                    gpio_put(LED_RED, false);
                    gpio_put(LED_GREEN, false);
                    gpio_put(LED_BLUE, false);
                    break;
                case '*':
                    printf("Encerrando o programa.\n");
                    return 0;  // Encerra o programa
                default:
                    printf("Tecla %c não configurada.\n", tecla);
            }

            // Debounce para evitar múltiplas leituras
            sleep_ms(300);
        }
    }

    return 0;  // Retorna 0 se o programa for finalizado
}
