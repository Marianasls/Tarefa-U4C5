/**
 * Atividade 2 - Alarme com temporizador de disparo único.
 * Autor: Mariana Santos.
 * Simulação online: https://wokwi.com/projects/420099632987314177
 */
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/clocks.h"

// Configurações dos pinos 
const uint8_t led_rgb_pins[3] = {12,13,11};     // R = 13, B = 12, G = 11
const uint8_t button_a = 5;        // Botão A = 5, Botão B = 6 , BotãoJoy = 22
// Variaveis globais
bool led_on = false;        // armazenar o estado do LED 
bool led_active = false;    // Indica se o LED está atualmente aceso 
absolute_time_t turn_off_time = 3000;  // armazena o tempo em que o LED deve ser desligado
int indice = 0; // armazena indice do led para ser desligado

// Prototipo da função de inicialização dos pinos
void init_all_pins();
// Prototipo das funções para alternar estado dos LEDs
int64_t alarm_callback1(alarm_id_t id, void *user_data);
int64_t alarm_callback2(alarm_id_t id, void *user_data);
int64_t alarm_callback3(alarm_id_t id, void *user_data);


int main() {
    // inicializa todos os pinos utilizados
    init_all_pins();

    while (true) {
        // Verifica se o botão foi pressionado (nível baixo no pino) e se o LED não está ativo.
        if (!gpio_get(button_a) && !led_active) {
            // Adiciona um pequeno atraso para debounce, evitando leituras errôneas.
            sleep_ms(50);
            printf("botão foi pressionado.\n");
            // Verifica novamente o estado do botão após o debounce.
            if (!gpio_get(button_a)) {
                for(int i=0; i<3; i++) {
                    gpio_put(led_rgb_pins[i], true);
                }
                // Define 'led_active' como true para indicar que o LED está aceso.
                led_active = true;

                // Agenda um alarme para desligar o LED após 3 segundos (3000 ms).
                // A função 'turn_off_callback' será chamada após esse tempo.
                // Desliga led verde
                indice = 0;
                int64_t alarm = add_alarm_in_ms(turn_off_time, alarm_callback1, NULL, false);  
                if (alarm < 0) printf("O alarme não foi ativado.");

            }
        }
        sleep_ms(10);
    }
    return 0;
}

/**
 * Função de callback que sera chamada pelo temporizador para apagar o LED azul.
 */
int64_t alarm_callback1(alarm_id_t id, void *user_data) {
    if (id < 0) return -1;
    printf("desliga led azul.\n");

    led_on = gpio_get(led_rgb_pins[0]);
    if(led_on) {
        gpio_put(led_rgb_pins[0], false);
    }

    // desliga led azul
    int64_t alarm = add_alarm_in_ms(turn_off_time, alarm_callback2, NULL, false);  
    if (alarm < 0) printf("O alarme não foi ativado.");

    return 0;
}

/**
 * Função de callback que sera chamada pelo temporizador para apagar o LED vermelho.
 */
int64_t alarm_callback2(alarm_id_t id, void *user_data) {
    if (id < 0) return -1;
    printf("desliga led vermelho.\n");

    led_on = gpio_get(led_rgb_pins[1]);
    if(led_on) {
        gpio_put(led_rgb_pins[1], false);
    }

    // desliga led vermelho
    int64_t alarm = add_alarm_in_ms(turn_off_time, alarm_callback3, NULL, false);  
    if (alarm < 0) printf("O alarme não foi ativado.");
    return 0;
}

/**
 * Função de callback que sera chamada pelo temporizador para apagar o LED verde.
 */
int64_t alarm_callback3(alarm_id_t id, void *user_data) {
    if (id < 0) return -1;
    printf("desliga led verde.\n");

    led_on = gpio_get(led_rgb_pins[2]);
    if(led_on) {
        gpio_put(led_rgb_pins[2], false);
    }
    led_active = false;

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
    // Inicializa o botão
    gpio_init(button_a);
    gpio_set_dir(button_a, GPIO_IN); // Configura o pino como entrada
    gpio_pull_up(button_a);          // Habilita o pull-up interno
}

