#include <stdio.h>
#include "pico/stdlib.h"

// Definição dos pinos GPIO
const int led_pin_red = 13; // LED Vermelho GPIO 13
const int led_pin_blue = 12;
const int led_pin_green = 11;
const int button_pin_A = 5; // Botão A GPIO 5
const int button_pin_B = 6; // Botão B GPIO 6

// Definição de constantes
#define time_blink 100 // Tempo de LED aceso e apagado

// Definição de variáveis globais
static volatile uint32_t last_time = 0; // Armazena o tempo do último clique dos botões 
static volatile uint a = 1; // Armazena a execução do botão A
static volatile uint b = 1; // Armazena a execução do botão B
static volatile uint bounce = 1; // Armazena o fenômeno de bouncing

// Função para o LED piscar 5 vezes por segundo
void loop_led_blink(){
    gpio_put(led_pin_red, true);
    sleep_ms(time_blink);
    gpio_put(led_pin_red, false);
    sleep_ms(time_blink);
}

// Função de callback da interrupção dos botões
void gpio_irq_handler(uint gpio, uint32_t events){

    // Debouncing
    uint32_t current_time = to_us_since_boot(get_absolute_time()); // Pega o tempo atual e transforma em us

    // Registro do fenômeno de bounce
    printf("Fenômeno de bounce = %d\n", bounce);
    bounce++;

    // 50 ms
    if(current_time - last_time > 200000){
        last_time = current_time; // Atualização de tempo do último clique

        // Verifica qual botão foi clicado
        if(gpio == button_pin_A){
            gpio_put(led_pin_blue, !gpio_get(led_pin_blue));

            // Registra a execução do botão A
            printf("========== Botão A executado = %d\n", a);
            a++;
        } else if(gpio == button_pin_B){
            gpio_put(led_pin_green, !gpio_get(led_pin_green));

            // Registra a execução do botão B
            printf("========== Botão B executado = %d\n", b);
            b++;
        }
    }

}

int main()
{
    // Inicialização das saídas padrão (UART e USB)
    stdio_init_all();

    // Inicialização dos pinos GPIO

    gpio_init(led_pin_red); // Inicializa o pino 13 do LED Vermelho
    gpio_set_dir(led_pin_red, GPIO_OUT); // Configura o pino 13 do LED Vermelho como saída
    gpio_init(led_pin_blue);
    gpio_set_dir(led_pin_blue, GPIO_OUT);
    gpio_init(led_pin_green);
    gpio_set_dir(led_pin_green, GPIO_OUT);

    gpio_init(button_pin_A); // Inicializa o pino do botão A
    gpio_set_dir(button_pin_A, GPIO_IN); // Configura o pino do botão A como entrada
    gpio_pull_up(button_pin_A); // Habilita o pull up interno no botão A

    gpio_init(button_pin_B); // Inicializa o pino do botão B
    gpio_set_dir(button_pin_B, GPIO_IN); // Configura o pino do botão B como entrada
    gpio_pull_up(button_pin_B); // Habilita o pull up interno no botão B

    // Função de interrupção dos botões A e B
    gpio_set_irq_enabled_with_callback(button_pin_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(button_pin_B, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

    while (true) {
        loop_led_blink();
    }
}