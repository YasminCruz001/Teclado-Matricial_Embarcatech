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

void tocar_buzzer(int duracao)
{
    int tempo = duracao;
    while (tempo > 0)
    {
        gpio_put(BUZZER, true); // Liga o buzzer
        sleep_ms(0.5);            
        tempo--;
        gpio_put(BUZZER, false); // Desliga o buzzer
        sleep_ms(2);             
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

// Liga um LED
void ligar_led(uint led_pin) {
    gpio_put(led_pin, true);
}

// Desliga um LED
void desligar_led(uint led_pin) {
    gpio_put(led_pin, false);
}

int main() {
    stdio_init_all();  
    init_gpio();       

    while (true) {
        char key = ler_teclado();
        if (key != '\0') {
            printf("Tecla Pressionada: %c\n", key);

            // Processa tecla pressionada
            switch (key) {
                case 'A': ligar_led(LED_RED); break;
                case 'B': ligar_led(LED_BLUE); break;
                case 'C': ligar_led(LED_GREEN); break;
                case 'D':
                    ligar_led(LED_RED);
                    ligar_led(LED_GREEN);
                    ligar_led(LED_BLUE);
                    break;
                case '#': tocar_buzzer(1000); break;
                default:
                    desligar_led(LED_RED);
                    desligar_led(LED_GREEN);
                    desligar_led(LED_BLUE);
                    break;
            }

            sleep_ms(500);  // Debounce

            // Desliga LEDs após debounce
            desligar_led(LED_RED);
            desligar_led(LED_GREEN);
            desligar_led(LED_BLUE);
        }
    }
}
