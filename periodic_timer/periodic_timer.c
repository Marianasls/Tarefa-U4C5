/**
 * Atividade 1 - Semaforo com temporizador periodico.
 * Autor: Mariana Santos.
 */
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/clocks.h"

// Configurações dos pinos 
const uint8_t led_rgb_pins[3] = {13,12,11};     // R = 13, B = 12, G = 11
const uint8_t colors[3][3] = {
    {1,0,0}, // vermelho
    {1,0,1}, // amarelo
    {0,0,1}  // verde
};
const uint8_t button_a = 5;        // Botão A = 5, Botão B = 6 , BotãoJoy = 22

// Prototipo da função de callback do temporizador
bool repeating_timer_callback();
// Prototipo da função de inicialização dos pinos
void init_all_pins();
// Prototipo da função para ligar e desligar LEDs
void turn_on_leds(int color_id);

int main() {
    // inicializa todos os pinos utilizados
    init_all_pins();
    // Atividade 1
    struct repeating_timer timer;
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    while (true) {
        printf("Semaforo\n");
        sleep_ms(1000);
    }
    return 0;
}

void init_all_pins() {
    // Inicializações
    stdio_init_all();
    // Inicializa os LEDs RGB
    for (int i=0; i<3; i++){
        gpio_init(led_rgb_pins[i]);              // Inicializa o pino do LED RED
        gpio_set_dir(led_rgb_pins[i], GPIO_OUT); // Configura o pino como saída
    }
}

// Acende e apaga os Leds RGB a depender da cor selecionada
void turn_on_leds(int color_id) {
    for (int i=0; i<3; i++){
        gpio_put(led_rgb_pins[i], colors[color_id][i]);
    }
}

/**
 * Função de callback que sera chamada periodicamente pelo temporizador para alternar entre as cores vermelho, amarelo e azul.
 * Acionar cada cor por 3 segundos (3000ms)
 */
bool repeating_timer_callback(struct repeating_timer *t) {
    static uint8_t count = 0;
    printf("Cor LED RGB: %d %d %d\n", colors[count][0], colors[count][1], colors[count][2]);

    turn_on_leds(count);
    count++;
    if (count > 2) count = 0;
    return true;
}