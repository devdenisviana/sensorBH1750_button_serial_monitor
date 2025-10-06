#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"

// --- Definições de Hardware ---
// Pinos definidos conforme a sua especificação
const uint LED_PIN = 11;
const uint BUTTON_PIN = 5;
const uint I2C_SDA_PIN = 0;
const uint I2C_SCL_PIN = 1;

// --- Configurações do Sensor BH1750 ---
// Endereço I2C padrão do BH1750
const int BH1750_ADDR = 0x23;

// Comandos do BH1750
const uint8_t BH1750_CMD_POWER_ON = 0x01;
const uint8_t BH1750_CMD_RESET = 0x07;
// Modo de medição contínua com alta resolução (1 lux)
const uint8_t BH1750_CMD_CONT_HIGH_RES = 0x10; 

// Função para inicializar o sensor BH1750
void bh1750_init(i2c_inst_t *i2c) {
    // Envia o comando para ligar o sensor
    i2c_write_blocking(i2c, BH1750_ADDR, &BH1750_CMD_POWER_ON, 1, false);
    sleep_ms(10); // Pequena pausa para estabilizar
    // Configura o modo de medição
    i2c_write_blocking(i2c, BH1750_ADDR, &BH1750_CMD_CONT_HIGH_RES, 1, false);
    sleep_ms(120); // Espera o tempo da primeira conversão
}

// Função para ler o valor de luminosidade (Lux)
float bh1750_read_lux(i2c_inst_t *i2c) {
    uint8_t buffer[2];
    
    // Lê 2 bytes do sensor
    int bytes_read = i2c_read_blocking(i2c, BH1750_ADDR, buffer, 2, false);
    if (bytes_read < 2) {
        return -1.0f; // Retorna um valor de erro se a leitura falhar
    }

    // Combina os dois bytes em um valor de 16 bits
    uint16_t raw_value = (buffer[0] << 8) | buffer[1];
    
    // Converte o valor bruto para Lux (fator de conversão é 1.2, conforme datasheet)
    return (float)raw_value / 1.2f;
}


int main() {
    // Inicializa o stdio (para o Serial Monitor via USB)
    stdio_init_all();
    
    // Espera um pouco para o monitor serial conectar
    sleep_ms(2000); 
    printf("--- Projeto Sensor de Luz BH1750 com Botao ---\n");
    printf("Pressione o Botao A para ler a luminosidade.\n");

    // --- Inicialização dos GPIOs ---
    // Configura o pino do LED como saída
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    // Configura o pino do Botão como entrada com pull-up interno
    // O pull-up garante que o pino leia HIGH quando o botão não está pressionado
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    // --- Inicialização do I2C ---
    // Inicializa o I2C0 com uma velocidade de 100 kHz
    i2c_init(i2c0, 100 * 1000); 
    
    // Define a função dos pinos GPIO0 e GPIO1 para I2C
    gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);
    // Habilita pull-ups internos para as linhas I2C (boa prática)
    gpio_pull_up(I2C_SDA_PIN);
    gpio_pull_up(I2C_SCL_PIN);

    // Inicializa o sensor BH1750
    bh1750_init(i2c0);
    
    // Loop principal infinito
    while (true) {
        // Verifica se o botão foi pressionado (lógica invertida devido ao pull-up)
        // !gpio_get() é verdadeiro quando o pino está em LOW (0V)
        if (!gpio_get(BUTTON_PIN)) {
            // 1. Acende o LED para indicar que a leitura está acontecendo
            gpio_put(LED_PIN, 1);
            
            // 2. Faz a leitura do sensor
            float lux = bh1750_read_lux(i2c0);
            
            // 3. Exibe a informação no monitor serial
            if (lux >= 0) {
                printf("Leitura do Sensor -> Nivel de Luz: %.2f Lux\n", lux);
            } else {
                printf("Erro ao ler o sensor BH1750!\n");
            }

            // 4. Espera o botão ser solto para evitar múltiplas leituras
            while (!gpio_get(BUTTON_PIN)) {
                sleep_ms(10); // Pequeno delay para não sobrecarregar a CPU
            }

            // 5. Apaga o LED
            gpio_put(LED_PIN, 0);
        }
        
        // Pequena pausa no loop para otimizar o uso da CPU
        sleep_ms(20); 
    }

    return 0;
}