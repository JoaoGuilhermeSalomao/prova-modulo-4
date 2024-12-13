#include <WiFi.h>
#include <HTTPClient.h>

#define led_verde 2 // Pino utilizado para controle do led verda
#define led_vermelho 40 // Pino utilizado para controle do led vermelho
#define led_amarelo 9 // Pino utilizado para controle do led azul

const int pinoBotao = 18;  // Pino utilizado para controle do botão
int estadoBotao = 0;  // variavel de leitura do status do botão

const int leitorLdr = 4;  // Pino utilizado para leitura do sensor fotoresistor
int limite=600; //

int led_vermelho_ligado = 0;
int led_amarelo_ligado = 0;
int led_verde_ligado = 0;
int amanhecer = 0;

void setup() {

  // Configuração inicial dos pinos para controle dos leds como OUTPUTs (saídas) do ESP32
  pinMode(led_amarelo,OUTPUT);
  pinMode(led_verde,OUTPUT);
  pinMode(led_vermelho,OUTPUT);

  // Inicialização das entradas
  pinMode(pinoBotao, INPUT); // Initialize the pushbutton pin as an input

  digitalWrite(led_amarelo, LOW);
  digitalWrite(led_verde, LOW);
  digitalWrite(led_vermelho, LOW);

  Serial.begin(9600); // Configuração para debug por interface serial entre ESP e computador com baud rate de 9600
/*
  WiFi.begin("Wokwi-GUEST", ""); // Conexão à rede WiFi aberta com SSID Wokwi-GUEST

  while (WiFi.status() != WL_CONNECT_FAILED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println("Conectado ao WiFi com sucesso!"); // Considerando que saiu do loop acima, o ESP32 agora está conectado ao WiFi (outra opção é colocar este comando dentro do if abaixo)
*/
  // Verifica estado do botão
  estadoBotao = digitalRead(pinoBotao);
  if (estadoBotao == HIGH) {
    Serial.println("Botão pressionado!");
  } else {
    Serial.println("Botão não pressionado!");
  }
/*
  if(WiFi.status() == WL_CONNECTED){ // Se o ESP32 estiver conectado à Internet
    HTTPClient http;

    String serverPath = "http://www.google.com.br/"; // Endpoint da requisição HTTP

    http.begin(serverPath.c_str());

    int httpResponseCode = http.GET(); // Código do Resultado da Requisição HTTP

    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      String payload = http.getString();
      Serial.println(payload);
      }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
      }
      http.end();
    }

  else {
    Serial.println("WiFi Disconnected");
  }*/
}

void loop() {
  int estadoLdr=analogRead(leitorLdr);

  if(estadoLdr<limite){
    Serial.print("its dark turn on led");
    Serial.println(estadoLdr);

    digitalWrite(led_amarelo, LOW);
    digitalWrite(led_verde, LOW);
    digitalWrite(led_vermelho, LOW);
    amanhecer = 1;
    delay(1000);
    digitalWrite(led_amarelo, HIGH);
    delay(1000);

  }
  else{
    Serial.print("its bright turn off light");
    Serial.println(estadoLdr);

    if(amanhecer == 1){
      digitalWrite(led_amarelo, LOW);
      digitalWrite(led_verde, LOW);
      digitalWrite(led_vermelho, HIGH);

      led_amarelo_ligado = 0;
      led_vermelho_ligado = 1;
      led_verde_ligado = 0;
      amanhecer = 0;
    }

    if(led_vermelho_ligado == 1){
      delay (5000);

      digitalWrite(led_amarelo, LOW);
      digitalWrite(led_verde, HIGH);
      digitalWrite(led_vermelho, LOW);

      led_vermelho_ligado = 0;
      led_verde_ligado = 1;
      amanhecer = 0;
    }
    
    if(led_amarelo_ligado == 1){
    delay(2000);

    digitalWrite(led_amarelo, LOW);
    digitalWrite(led_verde, LOW);
    digitalWrite(led_vermelho, HIGH);

    led_amarelo_ligado = 0;
    led_vermelho_ligado = 1;
    amanhecer = 0;

    }

    if(led_verde_ligado == 1){
    delay(3000);

    digitalWrite(led_amarelo, HIGH);
    digitalWrite(led_verde, LOW);
    digitalWrite(led_vermelho, LOW);

    led_verde_ligado = 0;
    led_amarelo_ligado = 1;
    amanhecer = 0;
    }
  }
}