/*
Programador: Guilherme Perrota
Data: 08/06/2026
PROJETO: Estacionamento com sensor
OBJETIVO: Medir a distância até o obstaculo usando ultrassom e 
emitir alertas visuais e sonoros
*/

//Variáveis Globais
const int PIN_TRIG = 9; //PULSO
const int PIN_ECHO = 10; //RECEBE O ECO
const int PIN_BUZZER = 5;

const int LED_VERDE = 2; 
const int LED_AMARELO = 3; 
const int LED_VERMELHO = 4; 

const int Explo = 1;

//VARIÁVEIS DE CÁLCULO
long duracao; //Armazena o tempo que a leva leva e volta
int distancia; //Armazena a distância final convertida para cm

void setup() {
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(Explo, OUTPUT);

  pinMode(PIN_BUZZER, OUTPUT);
  digitalWrite(Explo, LOW);

  //Inicializa a comunicação para terminal de leitura
  Serial.begin(9600);
}

void loop() {
  //Etapa A: EMISSÃO DA ONDA ULTRASSONICA
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(2);

  //ENVIA UM PULSO DE 10 MICROSEGUNDOS 
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);


  //ETAPA B: LEITURA DO TEMPO DE DISTANCIA
  duracao = pulseIn(PIN_ECHO, HIGH); //DEFINE A DURAÇÃO COM BASE NA DISTANCIA 

  //CALCULO DA DISTANCIA
  //VELOCIDADO DO AR: ~0,034CM POR MICROSEGUNDOS
  //DIVIDIMOS POR 2 PORQUE A ONDA VAI E VOLTA
  distancia = duracao * 0.034 / 2;

  Serial.print("Distânia lida: ");
  Serial.print(distancia);
  Serial.println(" cm");
  
  //ETAPA C: LÓGICA DOS ALERTAS QUE SÃO AS CONDICIONAIS
  desligarAlertas();

  //ZONA 1: SEGURA
  if (distancia > 200) {
    digitalWrite(LED_VERDE, HIGH);
  }

  //ZONA 2: Alerta 
  else if (distancia > 120 && distancia <= 200) {
    digitalWrite(LED_AMARELO, HIGH);
    emitirBip(100, 200);
  }

  //ZONA 3: PERIGO
  else if (distancia > 50 && distancia <= 120) {
    digitalWrite(LED_VERMELHO, HIGH);
    emitirBip(100,60);
  }

  //ZONA 4: PARADA IMEDIATA
  else if (distancia <= 50 && distancia > 0) {
    digitalWrite(LED_VERMELHO, HIGH);
    digitalWrite(Explo, HIGH);
    tone(PIN_BUZZER, 1000);

    delay(50);
  }

}

void desligarAlertas() {
  noTone(PIN_BUZZER);
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AMARELO, LOW);
  digitalWrite(LED_VERMELHO, LOW);
}

void emitirBip(int duracaoBip, int tempoBip) {
  tone(PIN_BUZZER, 1000);
  delay(duracaoBip);
  noTone(PIN_BUZZER);
  delay(tempoBip);
}