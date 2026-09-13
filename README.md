# Sensor de Estacionamento Ultrassônico (Park Assist)

Sistema de auxílio de estacionamento desenvolvido com *rduino Uno e o sensor ultrassônico HC-SR04. O projeto simula o funcionamento dos assistentes de ré de veículos modernos, emitindo alertas visuais progressivos via LEDs e alertas sonoros via Buzzer conforme a proximidade do obstáculo.

---

##  Esquemático / Circuito

<img width="766" height="519" alt="image" src="https://github.com/user-attachments/assets/ca7de7a9-6a45-4c26-858a-e28606362639" />

---

## Tecnologias e Componentes

### **Hardware**
* **Microcontrolador:** Arduino Uno R3
* **Sensor de Distância:** Sensor Ultrassônico HC-SR04
* **Atuador Sonoro:** 1x Buzzer Piezoelétrico (5V)
* **Sinalização Visual:** 3x LEDs (Verde, Amarelo e Vermelho)
* **Passivos:** 3x Resistores de 220Ω (Limitação de corrente dos LEDs)

### **Software**
* **Linguagem:** C / C++ (IDE Arduino)
* **Comunicação:** Serial UART (9600 Baud) para telemetria em tempo real

---

##  Conceitos de Engenharia Aplicados

### **1. Telemetria por Ultrassom**
O sensor aciona o pino `Trig` emitindo uma onda sonora de 40kHz por 10µs. O cálculo da distância é realizado através da medição do tempo que a onda leva para atingir o objeto e retornar ao pino `Echo`:

$$\text{Distância (cm)} = \frac{\text{Tempo (µs)} \times 0.034}{2}$$

### **2. Temporização Não-Bloqueante (`millis()`)**
Diferente das implementações tradicionais que travam a CPU com a função `delay()`, os bips intermitentes utilizam controle de tempo baseado no timer nativo do microcontrolador (`millis()`). Isso garante que a leitura do sensor seja contínua e responda a aproximações repentinas.

---

## 🚦 Zonas de Alerta

| Zona | Distância (cm) | LED Ativo | Sinal Sonoro |
| :--- | :--- | :--- | :--- |
| **Longe / Seguro** | $> 200 \text{ cm}$ | Verde | Silencioso |
| **Atenção** | $120 \text{ cm} - 200 \text{ cm}$ | Amarelo | Bip lento (300ms) |
| **Perigo** | $50 \text{ cm} - 120 \text{ cm}$ | Vermelho | Bip rápido (120ms) |
| **Parada Imediata** | $\le 50 \text{ cm}$ | Vermelho | Apito contínuo |

---

## Pinagem (Mapeamento de Hardware)

| Componente | Pino do Arduino | Função |
| :--- | :--- | :--- |
| **HC-SR04 (Trig)** | D9 | Emissor do sinal ultrassônico |
| **HC-SR04 (Echo)** | D10 | Leitura do tempo de retorno |
| **Buzzer** | D5 | Saída de frequência áudio (PWM) |
| **LED Verde** | D2 | Indicador de distância segura |
| **LED Amarelo** | D3 | Indicador de atenção |
| **LED Vermelho** | D4 | Indicador de parada |

---

## Como Rodar o Projeto

1. acesse: https://www.tinkercad.com/things/gjeXhrp7Kcx-sensor-de-aproximacao?sharecode=wvRyeZftPkoyeeHT4BGPPeshRBsdei7CZFeQ_P1IAdc

ou

2. Monte fisicamente
4. Abra o arquivo `sensor_de_aproximação_Park.ino` no Arduino IDE.
3. Conecte o Arduino Uno ao computador.
4. Faça o upload do código e abra o **Monitor Serial** para ver a distância em tempo real.

---

## Autor

Desenvolvido por **Guilherme Perrota**  
* Projeto disponibilizado para fins de estudo e portfólio.
