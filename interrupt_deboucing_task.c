/*
--- BLOCO INICIAL ---
- Definição de bibliotecas, constantes e variáveis globais -
*/

// Definição de bibliotecas
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812.pio.h"

// Definição dos pinos GPIO
const int led_pin_red = 13; // LED Vermelho GPIO 13
const int button_pin_A = 5; // Botão A GPIO 5
const int button_pin_B = 6; // Botão B GPIO 6
const int matriz_leds = 7; // Matriz de LEDs GPIO 7
const int buzzer_A = 21; // Buzzer A GPIO 21
const int buzzer_B = 10; // Buzzer B GPIO 10

// Definição de constantes
#define time_blink 100 // Tempo de LED aceso e apagado
#define NUM_LEDS 25 // Número de LEDs na matriz

// Definição de variáveis globais
static volatile uint32_t last_time = 0; // Armazena o tempo do último clique dos botões 
static volatile uint a = 1; // Armazena a execução do botão A
static volatile uint b = 1; // Armazena a execução do botão B
static volatile uint bounce = 1; // Armazena o fenômeno de bouncing
static volatile uint num_exibido = 0; // Armazena o valor do número mostrado na matriz de lEDs


/*
--- BLOCO DE PIO ---
- Configuração do PIO e funções de manipulação da matriz de LEDs -
*/

// Estrutura do pixel GRB (Padrão do WS2812)
struct pixel_t {
    uint8_t G, R, B; // Define variáveis de 8-bits (0 a 255) para armazenar a cor
};
typedef struct pixel_t pixel_t;
typedef pixel_t npLED_t; // Permite declarar variáveis utilizando apenas "npLED_t"

// Declaração da Array que representa a matriz de LEDs
npLED_t leds[NUM_LEDS];

// Variáveis para máquina PIO
PIO np_pio;
uint sm;

// Função para definir a cor de um LED específico
void cor(const uint index, const uint8_t r, const uint8_t g, const uint8_t b) {
    leds[index].R = r;
    leds[index].G = g;
    leds[index].B = b;
}

// Função para desligar todos os LEDs
void desliga() {
    for (uint i = 0; i < NUM_LEDS; ++i) {
        cor(i, 0, 0, 0);
    }
}

// Função para enviar o estado atual dos LEDs ao hardware  - buffer de saída
void buffer() {
    for (uint i = 0; i < NUM_LEDS; ++i) {
        pio_sm_put_blocking(np_pio, sm, leds[i].G);
        pio_sm_put_blocking(np_pio, sm, leds[i].R);
        pio_sm_put_blocking(np_pio, sm, leds[i].B);
    }
    // sleep_us(100);
}

// Função para converter a posição da matriz para uma posição do vetor.
int getIndex(int x, int y) {
    // Se a linha for par (0, 2, 4), percorremos da esquerda para a direita.
    // Se a linha for ímpar (1, 3), percorremos da direita para a esquerda.
    if (y % 2 == 0) {
        return 24-(y * 5 + x); // Linha par (esquerda para direita).
    } else {
        return 24-(y * 5 + (4 - x)); // Linha ímpar (direita para esquerda).
    }
}

// Função que guarda os frames dos números
void frame(int num_frame){
    desliga();

    switch (num_frame){
        case 0: {
            // Frame 0
            int frame0[5][5][3] = {
                {{0, 0, 0}, {255, 133, 0}, {255, 133, 0}, {255, 133, 0}, {0, 0, 0}},
                {{0, 0, 0}, {255, 133, 0}, {0, 0, 0}, {255, 133, 0}, {0, 0, 0}},    
                {{0, 0, 0}, {255, 133, 0}, {0, 0, 0}, {255, 133, 0}, {0, 0, 0}},
                {{0, 0, 0}, {255, 133, 0}, {0, 0, 0}, {255, 133, 0}, {0, 0, 0}},
                {{0, 0, 0}, {255, 133, 0}, {255, 133, 0}, {255, 133, 0}, {0, 0, 0}}
            };
            for (int linha = 0; linha < 5; linha++)
            {
                for (int coluna = 0; coluna < 5; coluna++)
                {
                int posicao = getIndex(linha, coluna);
                cor(posicao, frame0[coluna][linha][0], frame0[coluna][linha][1], frame0[coluna][linha][2]);
                }
            };
            buffer();
            break;
        }
        case 1:{
            // Frame 1
            int frame1[5][5][3] = {
                {{0, 0, 0}, {0, 0, 0}, {0, 245, 255}, {0, 0, 0}, {0, 0, 0}},
                {{0, 0, 0}, {0, 245, 255}, {0, 245, 255}, {0, 0, 0}, {0, 0, 0}},
                {{0, 0, 0}, {0, 0, 0}, {0, 245, 255}, {0, 0, 0}, {0, 0, 0}},
                {{0, 0, 0}, {0, 0, 0}, {0, 245, 255}, {0, 0, 0}, {0, 0, 0}},
                {{0, 0, 0}, {0, 245, 255}, {0, 245, 255}, {0, 245, 255}, {0, 0, 0}}
            };
            for (int linha = 0; linha < 5; linha++)
            {
                for (int coluna = 0; coluna < 5; coluna++)
                {
                int posicao = getIndex(linha, coluna);
                cor(posicao, frame1[coluna][linha][0], frame1[coluna][linha][1], frame1[coluna][linha][2]);
                }
            };
            buffer();
            break;
        }
        case 2:{
            // Frame 2
            int frame2[5][5][3] = {
                {{0, 0, 0}, {0, 245, 255}, {0, 245, 255}, {0, 245, 255}, {0, 0, 0}},
                {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 245, 255}, {0, 0, 0}},        
                {{0, 0, 0}, {0, 245, 255}, {0, 245, 255}, {0, 245, 255}, {0, 0, 0}},
                {{0, 0, 0}, {0, 245, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
                {{0, 0, 0}, {0, 245, 255}, {0, 245, 255}, {0, 245, 255}, {0, 0, 0}}
            };
            for (int linha = 0; linha < 5; linha++)
            {
                for (int coluna = 0; coluna < 5; coluna++)
                {
                int posicao = getIndex(linha, coluna);
                cor(posicao, frame2[coluna][linha][0], frame2[coluna][linha][1], frame2[coluna][linha][2]);
                }
            };
            buffer();
            break;
        }
        case 3:{
            // Frame 3
            int frame3[5][5][3] = {
                {{0, 0, 0}, {0, 245, 255}, {0, 245, 255}, {0, 245, 255}, {0, 0, 0}},
                {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 245, 255}, {0, 0, 0}},
                {{0, 0, 0}, {0, 245, 255}, {0, 245, 255}, {0, 245, 255}, {0, 0, 0}},
                {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 245, 255}, {0, 0, 0}},
                {{0, 0, 0}, {0, 245, 255}, {0, 245, 255}, {0, 245, 255}, {0, 0, 0}}
            };
            for (int linha = 0; linha < 5; linha++)
            {
                for (int coluna = 0; coluna < 5; coluna++)
                {
                int posicao = getIndex(linha, coluna);
                cor(posicao, frame3[coluna][linha][0], frame3[coluna][linha][1], frame3[coluna][linha][2]);
                }
            };
            buffer();
            break;
        }
        case 4:{
            // Frame 4
            int frame4[5][5][3] = {
                {{0, 0, 0}, {0, 245, 255}, {0, 0, 0}, {0, 245, 255}, {0, 0, 0}},
                {{0, 0, 0}, {0, 245, 255}, {0, 0, 0}, {0, 245, 255}, {0, 0, 0}},    
                {{0, 0, 0}, {0, 245, 255}, {0, 245, 255}, {0, 245, 255}, {0, 0, 0}},
                {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 245, 255}, {0, 0, 0}},
                {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 245, 255}, {0, 0, 0}} 
            };
            for (int linha = 0; linha < 5; linha++)
            {
                for (int coluna = 0; coluna < 5; coluna++)
                {
                int posicao = getIndex(linha, coluna);
                cor(posicao, frame4[coluna][linha][0], frame4[coluna][linha][1], frame4[coluna][linha][2]);
                }
            };
            buffer();
            break;
        }
        case 5:{
            // Frame 5
            int frame5[5][5][3] = {
                {{0, 0, 0}, {0, 245, 255}, {0, 245, 255}, {0, 245, 255}, {0, 0, 0}},
                {{0, 0, 0}, {0, 245, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
                {{0, 0, 0}, {0, 245, 255}, {0, 245, 255}, {0, 245, 255}, {0, 0, 0}},
                {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 245, 255}, {0, 0, 0}},
                {{0, 0, 0}, {0, 245, 255}, {0, 245, 255}, {0, 245, 255}, {0, 0, 0}}
            };
            for (int linha = 0; linha < 5; linha++)
            {
                for (int coluna = 0; coluna < 5; coluna++)
                {
                int posicao = getIndex(linha, coluna);
                cor(posicao, frame5[coluna][linha][0], frame5[coluna][linha][1], frame5[coluna][linha][2]);
                }
            };
            buffer();
            break;
        }
        case 6:{
            // Frame 6
            int frame6[5][5][3] = {
                {{0, 0, 0}, {0, 245, 255}, {0, 245, 255}, {0, 245, 255}, {0, 0, 0}},
                {{0, 0, 0}, {0, 245, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},        
                {{0, 0, 0}, {0, 245, 255}, {0, 245, 255}, {0, 245, 255}, {0, 0, 0}},
                {{0, 0, 0}, {0, 245, 255}, {0, 0, 0}, {0, 245, 255}, {0, 0, 0}},    
                {{0, 0, 0}, {0, 245, 255}, {0, 245, 255}, {0, 245, 255}, {0, 0, 0}}
            };
            for (int linha = 0; linha < 5; linha++)
            {
                for (int coluna = 0; coluna < 5; coluna++)
                {
                int posicao = getIndex(linha, coluna);
                cor(posicao, frame6[coluna][linha][0], frame6[coluna][linha][1], frame6[coluna][linha][2]);
                }
            };
            buffer();
            break;
        }
        case 7:{
            // Frame 7
            int frame7[5][5][3] = {
                {{0, 0, 0}, {0, 245, 255}, {0, 245, 255}, {0, 245, 255}, {0, 0, 0}},
                {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 245, 255}, {0, 0, 0}},
                {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 245, 255}, {0, 0, 0}},
                {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 245, 255}, {0, 0, 0}},
                {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 245, 255}, {0, 0, 0}} 
            };
            for (int linha = 0; linha < 5; linha++)
            {
                for (int coluna = 0; coluna < 5; coluna++)
                {
                int posicao = getIndex(linha, coluna);
                cor(posicao, frame7[coluna][linha][0], frame7[coluna][linha][1], frame7[coluna][linha][2]);
                }
            };
            buffer();
            break;
        }
        case 8:{
            // Frame 8
            int frame8[5][5][3] = {
                {{0, 0, 0}, {0, 245, 255}, {0, 245, 255}, {0, 245, 255}, {0, 0, 0}},
                {{0, 0, 0}, {0, 245, 255}, {0, 0, 0}, {0, 245, 255}, {0, 0, 0}},    
                {{0, 0, 0}, {0, 245, 255}, {0, 245, 255}, {0, 245, 255}, {0, 0, 0}},
                {{0, 0, 0}, {0, 245, 255}, {0, 0, 0}, {0, 245, 255}, {0, 0, 0}},
                {{0, 0, 0}, {0, 245, 255}, {0, 245, 255}, {0, 245, 255}, {0, 0, 0}}
            };
            for (int linha = 0; linha < 5; linha++)
            {
                for (int coluna = 0; coluna < 5; coluna++)
                {
                int posicao = getIndex(linha, coluna);
                cor(posicao, frame8[coluna][linha][0], frame8[coluna][linha][1], frame8[coluna][linha][2]);
                }
            };
            buffer();
            break;
        }
        case 9:{
            // Frame 9
            int frame9[5][5][3] = {
                {{0, 0, 0}, {255, 133, 0}, {255, 133, 0}, {255, 133, 0}, {0, 0, 0}},
                {{0, 0, 0}, {255, 133, 0}, {0, 0, 0}, {255, 133, 0}, {0, 0, 0}},    
                {{0, 0, 0}, {255, 133, 0}, {255, 133, 0}, {255, 133, 0}, {0, 0, 0}},
                {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 133, 0}, {0, 0, 0}},       
                {{0, 0, 0}, {255, 133, 0}, {255, 133, 0}, {255, 133, 0}, {0, 0, 0}}
            };
            for (int linha = 0; linha < 5; linha++)
            {
                for (int coluna = 0; coluna < 5; coluna++)
                {
                int posicao = getIndex(linha, coluna);
                cor(posicao, frame9[coluna][linha][0], frame9[coluna][linha][1], frame9[coluna][linha][2]);
                }
            };
            buffer();
            break;
        }
        default:
            break;
    }
}

/*
--- BLOCO DE FUNÇÕES GPIO ---
- Funções de manipulação dos pinos GPIO -
*/

// Função para o LED piscar 5 vezes por segundo
void loop_led_blink(){
    gpio_put(led_pin_red, true);
    sleep_ms(time_blink);
    gpio_put(led_pin_red, false);
    sleep_ms(time_blink);
}

// Função que reporta o erro quando incrementa em 9 e decrementa em 0
void erro(int erro){
    if(erro == 1){
        desliga();
        gpio_put(buzzer_A, 1);
        gpio_put(buzzer_B, 1);
        // Frame 9 vermelho
        int frame9v[5][5][3] = {
            {{0, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 0, 0}},
            {{0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}},    
            {{0, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 0, 0}},
            {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}},       
            {{0, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 0, 0}}
        };
        for (int linha = 0; linha < 5; linha++)
        {
            for (int coluna = 0; coluna < 5; coluna++)
            {
            int posicao = getIndex(linha, coluna);
            cor(posicao, frame9v[coluna][linha][0], frame9v[coluna][linha][1], frame9v[coluna][linha][2]);
            }
        };
        buffer();
        busy_wait_ms(100);
        desliga();
        frame(9);
        gpio_put(buzzer_A, 0);
        gpio_put(buzzer_B, 0);
    } else{
        desliga();
        gpio_put(buzzer_A, 1);
        gpio_put(buzzer_B, 1);
        // Frame 0 vermelho
        int frame0v[5][5][3] = {
                {{0, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 0, 0}},
                {{0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}},    
                {{0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}},
                {{0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}},
                {{0, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 0, 0}}
            };
        for (int linha = 0; linha < 5; linha++)
        {
            for (int coluna = 0; coluna < 5; coluna++)
            {
            int posicao = getIndex(linha, coluna);
            cor(posicao, frame0v[coluna][linha][0], frame0v[coluna][linha][1], frame0v[coluna][linha][2]);
            }
        };
        buffer();
        busy_wait_ms(100);
        desliga();
        frame(0);
        gpio_put(buzzer_A, 0);
        gpio_put(buzzer_B, 0);
    }
}

// Função de callback da interrupção dos botões
void gpio_irq_handler(uint gpio, uint32_t events){

    // Debouncing
    uint32_t current_time = to_us_since_boot(get_absolute_time()); // Pega o tempo atual e transforma em us

    // Registro do fenômeno de bounce
    printf("Fenômeno de bounce = %d\n", bounce);
    bounce++;

    // 200 ms
    if(current_time - last_time > 200000){
        last_time = current_time; // Atualização de tempo do último clique

        // Verifica qual botão foi clicado
        if(gpio == button_pin_A){
            if(num_exibido > 8){
                erro(1);
            } else{
                num_exibido++;
                frame(num_exibido);
            }
            // Registra a execução do botão A
            printf("========== Botão A executado = %d\n", a);
            a++;
        } else if(gpio == button_pin_B){
            if(num_exibido < 1){
                erro(0);
            } else{
                num_exibido--;
                frame(num_exibido);
            }
            // Registra a execução do botão B
            printf("========== Botão B executado = %d\n", b);
            b++;
        }
    }

}


/*
--- BLOCO PRINCIPAL ---
- Função principal do código -
*/

int main()
{
    // Inicialização das saídas padrão (UART e USB)
    stdio_init_all();

    // Inicialização dos pinos GPIO
    gpio_init(led_pin_red); // Inicializa o pino 13 do LED Vermelho
    gpio_set_dir(led_pin_red, GPIO_OUT); // Configura o pino 13 do LED Vermelho como saída

    gpio_init(button_pin_A); // Inicializa o pino do botão A
    gpio_set_dir(button_pin_A, GPIO_IN); // Configura o pino do botão A como entrada
    gpio_pull_up(button_pin_A); // Habilita o pull up interno no botão A

    gpio_init(button_pin_B); // Inicializa o pino do botão B
    gpio_set_dir(button_pin_B, GPIO_IN); // Configura o pino do botão B como entrada
    gpio_pull_up(button_pin_B); // Habilita o pull up interno no botão B

    gpio_init(buzzer_A); // Inicializa o pino do Buzzer A
    gpio_set_dir(buzzer_A, GPIO_OUT); // Configura o pino do buzzer A como saída
    gpio_init(buzzer_B); // Inicializa o pino do Buzzer B
    gpio_set_dir(buzzer_B, GPIO_OUT); // Configura o pino do buzzer B como saída

    // Inicializar o PIO para controle da matriz de LEDs
    np_pio = pio0;
    sm = pio_claim_unused_sm(np_pio, true);
    uint offset = pio_add_program(pio0, &ws2818b_program);
    ws2818b_program_init(np_pio, sm, offset, matriz_leds, 800000);
    desliga(); // Para limpar o buffer dos LEDs
    frame(num_exibido);

    // Função de interrupção dos botões A e B
    gpio_set_irq_enabled_with_callback(button_pin_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(button_pin_B, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

    while (true) {
        loop_led_blink();
    }
}