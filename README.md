# Sensor de Luz BH1750 com Raspberry Pi Pico

Este projeto implementa um sistema de medição de luminosidade usando o sensor BH1750 conectado ao Raspberry Pi Pico. O sistema permite fazer leituras de luz ambiente através de um botão, com indicação visual por LED.

## 📋 Descrição do Projeto

O projeto consiste em um medidor de luminosidade que:
- Utiliza o sensor BH1750 para medição precisa de luz ambiente em Lux
- Possui um botão para acionar as leituras sob demanda
- Indica visualmente quando uma leitura está sendo realizada através de um LED
- Exibe os resultados via monitor serial USB
- Implementa comunicação I2C para interface com o sensor

## 🔧 Hardware Necessário

- **Raspberry Pi Pico W**
- **Sensor BH1750** (sensor de luminosidade digital)
- **LED** (para indicação visual)
- **Botão (push-button)**
- **Resistores** (pull-up para o botão, se necessário)
- **Protoboard e jumpers** para conexões

## 📐 Esquema de Conexões

### Pinout do Raspberry Pi Pico:

| Componente | Pino Pico | GPIO | Função |
|-----------|-----------|------|--------|
| LED | Pino 15 | GPIO 11 | Indicação visual |
| Botão | Pino 7 | GPIO 5 | Entrada (com pull-up interno) |
| BH1750 SDA | Pino 1 | GPIO 0 | Dados I2C |
| BH1750 SCL | Pino 2 | GPIO 1 | Clock I2C |
| BH1750 VCC | 3.3V | - | Alimentação |
| BH1750 GND | GND | - | Terra |

### Diagrama de Conexão:
```
Raspberry Pi Pico          BH1750
     3.3V    -------------- VCC
     GND     -------------- GND
     GPIO 0  -------------- SDA
     GPIO 1  -------------- SCL

     GPIO 11 -------------- LED (+) ---- Resistor ---- GND
     GPIO 5  -------------- Botão ---- GND
```

## 🚀 Como Usar

1. **Compile e carregue o código** no Raspberry Pi Pico
2. **Conecte via USB** e abra o monitor serial (115200 baud)
3. **Pressione o botão** para realizar uma leitura de luminosidade
4. **Observe o LED** acender durante a leitura
5. **Veja o resultado** no monitor serial em Lux

### Exemplo de Saída:
```
--- Projeto Sensor de Luz BH1750 com Botao ---
Pressione o Botao A para ler a luminosidade.
Leitura do Sensor -> Nivel de Luz: 245.67 Lux
Leitura do Sensor -> Nivel de Luz: 1023.45 Lux
```

## 🛠️ Compilação e Upload

### Pré-requisitos:
- **Raspberry Pi Pico SDK** instalado
- **CMake** e **Ninja** configurados
- **VS Code** com extensão Raspberry Pi Pico

### Passos para Compilar:

1. **Clone ou baixe** este repositório
2. **Abra o projeto** no VS Code
3. **Execute a tarefa** "Compile Project" ou use:
   ```bash
   mkdir build
   cd build
   cmake ..
   ninja
   ```
4. **Carregue o arquivo** `sensor-luz.uf2` no Pico

### Upload para o Pico:
- Segure o botão **BOOTSEL** e conecte o Pico via USB
- Copie o arquivo `build/sensor-luz.uf2` para a unidade **RPI-RP2**
- O Pico reiniciará automaticamente com o novo programa

## 📊 Especificações Técnicas

### Sensor BH1750:
- **Resolução**: 1 Lux
- **Faixa de medição**: 1 - 65535 Lux
- **Interface**: I2C (endereço 0x23)
- **Tensão de operação**: 2.4V - 3.6V
- **Tempo de conversão**: ~120ms (modo alta resolução)

### Configurações do Sistema:
- **Velocidade I2C**: 100 kHz
- **Monitor Serial**: USB, 115200 baud
- **Modo do sensor**: Medição contínua, alta resolução

## 📁 Estrutura do Projeto

```
sensor-luz/
├── sensor-luz.c           # Código principal
├── CMakeLists.txt         # Configuração de build
├── pico_sdk_import.cmake  # Import do Pico SDK
├── build/                 # Arquivos de build
└── README.md              # Este arquivo
```

## 🔍 Funcionalidades Implementadas

- ✅ **Inicialização do sensor BH1750**
- ✅ **Leitura de luminosidade em Lux**
- ✅ **Interface de botão com debounce**
- ✅ **Indicação visual por LED**
- ✅ **Comunicação serial via USB**
- ✅ **Tratamento de erros de leitura**
- ✅ **Pull-ups internos configurados**

## 🐛 Solução de Problemas

### Sensor não responde:
- Verifique as conexões I2C (SDA/SCL)
- Confirme a alimentação 3.3V do sensor
- Teste a continuidade dos fios

### LED não acende:
- Verifique a conexão do GPIO 11
- Teste o LED com multímetro
- Confirme a polaridade do LED

### Botão não funciona:
- Verifique a conexão do GPIO 5
- Teste a continuidade do botão
- O pull-up interno está ativado no código

## 📝 Licença

Este projeto é livre para uso educacional e pessoal.

## 👨‍💻 Autor

Desenvolvido como parte da **Residência DPM** - Projeto de Sensoriamento de Luz Ambiente.

---

**💡 Dica**: Para melhores resultados, calibre o sensor em ambiente com iluminação conhecida e ajuste os fatores de conversão se necessário.