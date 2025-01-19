#include "pico/stdlib.h"

// Definições de pinos
#define LED_RED 10
#define LED_GREEN 11
#define LED_BLUE 12
#define BUZZER 13

// Função para inicializar GPIOs
void setup_gpio() {
    // Inicializar LEDs
    gpio_init(LED_RED);
    gpio_init(LED_GREEN);
    gpio_init(LED_BLUE);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_set_dir(LED_BLUE, GPIO_OUT);

    // Inicializar buzzer
    gpio_init(BUZZER);
    gpio_set_dir(BUZZER, GPIO_OUT);
}

// Função para tocar o buzzer por um tempo especificado (em milissegundos)
void tocar_buzzer(int duration_ms) {
    gpio_put(BUZZER, true);
    sleep_ms(duration_ms);
    gpio_put(BUZZER, false);
}

int main() {
    stdio_init_all();
    setup_gpio();

    // Loop principal
    while (true) {
        // Simulação de leitura de uma tecla
        char tecla = getchar_timeout_us(1000000); // Aguarda tecla por 1 segundo
        if (tecla != PICO_ERROR_TIMEOUT) {
            printf("Tecla pressionada: %c\n", tecla);

            switch (tecla) {
                case 'A':
                    printf("Ação para tecla A: LED vermelho piscando.\n");
                    gpio_put(LED_RED, true);
                    tocar_buzzer(150);
                    sleep_ms(200);
                    gpio_put(LED_RED, false);
                    break;
                case 'C':
                    printf("Ação para tecla C: Todos os LEDs piscando.\n");
                    for (int i = 0; i < 3; i++) {
                        gpio_put(LED_RED, true);
                        gpio_put(LED_GREEN, true);
                        gpio_put(LED_BLUE, true);
                        tocar_buzzer(300);
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
                    tocar_buzzer(500);
                    gpio_put(LED_GREEN, true);
                    tocar_buzzer(500);
                    gpio_put(LED_BLUE, true);
                    tocar_buzzer(500);
                    sleep_ms(500);
                    gpio_put(LED_RED, false);
                    gpio_put(LED_GREEN, false);
                    gpio_put(LED_BLUE, false);
                    break;
                case '#':
                    gpio_put(LED_BLUE, true);
                    tocar_buzzer(150);
                    gpio_put(LED_BLUE, false);
                    sleep_ms(150);
                    gpio_put(LED_RED, true);
                    tocar_buzzer(300);
                    gpio_put(LED_RED, false);
                    sleep_ms(300);
                    gpio_put(LED_GREEN, true);
                    tocar_buzzer(600);
                    gpio_put(LED_GREEN, false);
                    break;
                case '*':
                    printf("Encerrando o programa.\n");
                    return 0; // Encerra o programa
                default:
                    printf("Tecla %c não configurada.\n", tecla);
            }

            // Debounce para evitar múltiplas leituras
            sleep_ms(300);
        }
    }

    return 0; // Retorna 0 se o programa for finalizado
}

