//Biblioteca LCD
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4); // Use o seu endereço I2C

//Biblioteca Sensor
#include <Adafruit_Sensor.h>  // Biblioteca DHT Sensor Adafruit
#include <DHT.h>
#include <DHT_U.h>
#define DHTTYPE DHT11  // Definindo o tipo de sensor como DHT11
#define DHTPIN 2                     // Pino do Arduino conectado ao sensor DHT
DHT_Unified dht(DHTPIN, DHTTYPE);  // Inicializando o sensor DHT11

// Declaração de pinos
const int sensorPin = A0;
const int led = 13;
const int bot1 = 12;
const int bot2 = 11;
const int bot3 = 10;

// Declaração de variaveis
int estadobot1 = 0;
int estadobot2 = 0;
int estadobot3 = 0;

// Leitura Média
float temp_lida;
float soma = 0.0;
float media;
int contador = 1;

/*Parâmetros do sensor
----Tensão de trabalho----
const float tensaoRef = 5.0;       

const float resolucaoADC = 1023.0;   

//Refêrencia ao sensor temperatura TMP36
const float valorReferencia = 0.5;

//Refêrencia para graus °C
const float celsiusReferencia = 100.0; */

//Timer de leitura
unsigned long tempoAnterior = 0; // Armazena o último momento em que a tarefa foi executada
const long intervalo = 5000; // O intervalo desejado em milissegundos (2 segundos)

void setup() {
  pinMode(sensorPin, INPUT);
  pinMode(bot1, INPUT);
  pinMode(bot2, INPUT);
  pinMode(bot3, INPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  lcd.init(); // Serve para iniciar a comunicação com o display já conectado
  lcd.backlight(); // Serve para ligar a luz do display
  lcd.clear(); // Serve para limpar a tela do display
  Inicia_lcd();
}

void loop(){
  /*Chamada da função
  float temp = temperatura();*/
  sensors_event_t event;  // inicializa o evento da Temperatura
  
  Menu_lcd();
    
    ///// MODO AUTOMÁTICO /////
    digitalWrite(led, LOW);
    
  while(estadobot2 == 1){
      
  //Inicia o timer
  unsigned long tempoAtual = millis(); // Obtém o tempo atual em milissegundos
  // Verifica se já passou o intervalo de tempo desejado
  if ((tempoAtual - tempoAnterior) >= intervalo) {
 
    //Chamada da função
  	float temp = temperatura();
    
    lcd.setCursor(1,0); 
  	lcd.print("Temp:");
    lcd.print(temp);
    lcd.print(" C ");
    
    //condição
  	if(temp > 30){
    	digitalWrite(led, HIGH);
    	Serial.print("Temperatura Alta ");
    	Serial.print(temp);
  		Serial.println("C   ");
      	lcd.setCursor(1, 1); 
  		lcd.print("Sistema: ON  "); 
  	} else {
    	digitalWrite(led, LOW);
		Serial.print("Temperatura: ");
  		Serial.print(temp);
  		Serial.println("C   ");
      	lcd.setCursor(1, 1); 
  		lcd.print("Sistema: OFF"); 
      
    	}
    tempoAnterior = tempoAtual;
  	}
  
    if(digitalRead(bot2) == 0){
   		estadobot2 = !estadobot2;
     	delay(200);
    	}
   }
    
    ///// MODO MANUAL /////
    
    while(estadobot1 == 1){
  //Inicia o timer
  unsigned long tempoAtual = millis(); // Obtém o tempo atual em milissegundos
  // Verifica se já passou o intervalo de tempo desejado
  if ((tempoAtual - tempoAnterior) >= intervalo) {
    //Chamada da função
  	float temp = temperatura();
    
    lcd.setCursor(1,0); 
  	lcd.print("Temp:");
    lcd.print(temp);
    lcd.print(" C  ");
    tempoAnterior = tempoAtual;
    lcd.setCursor(1,1); 
  	lcd.print("Aperte bot2");
    digitalWrite(led, LOW);
  }
    if(digitalRead(bot2) == 0){
   		estadobot2 = !estadobot2;
     	delay(200);
    	}
     while(estadobot2 == 1){
       	digitalWrite(led, HIGH);
       	lcd.setCursor(1,1); 
  		lcd.print("Sistema: ON  ");
       	if(digitalRead(bot2) == 0){
   			estadobot2 = !estadobot2;
     		delay(200);
    		}
     	}
    if(digitalRead(bot1) == 0){
   		estadobot1 = !estadobot1;
     	delay(200);
    }
  }
  
  ///// MODO LEITURA MÉDIA /////
  while(estadobot3 == 1){
    
  	while (contador < 10) {
    	//Inicia o timer
  		unsigned long tempoAtual = millis(); // Obtém o tempo atual em milissegundos
  		// Verifica se já passou o intervalo de tempo desejado
  		if ((tempoAtual - tempoAnterior) >= intervalo) {
      		//Chamada da função
      		float temp = temperatura();
    		temp_lida = temp;
          	soma += temp_lida;
    		tempoAnterior = tempoAtual;
          	contador++;
          	lcd.setCursor(1,0); 
  			lcd.print("  aguardando  ");
          	lcd.setCursor(1,1); 
  			lcd.print("  medicao  ");
  			}
    }
    //lcd.clear();
    media = soma / contador;
    lcd.setCursor(1,0); 
  	lcd.print("Media:");
    lcd.print(media);
    lcd.print(" C    ");
    lcd.setCursor(1,1); 
    lcd.print("N de medicao:");
    lcd.print(contador);
    if(digitalRead(bot3) == 0){
   		estadobot3 = !estadobot3;
     	delay(200);
    	}
  	
  }
}

//Inicialização do Display
void Inicia_lcd(){
  lcd.setCursor(1,0); 
  lcd.print("   Battery   "); 
  lcd.setCursor(1, 1); 
  lcd.print("   Control    ");  
  delay(3000); 
  lcd.clear();
  lcd.setCursor(1 ,0); 
  lcd.print("Inicializando"); 
  lcd.setCursor(6 ,1);
  lcd.print("Menu");   
  delay(3000);  
  lcd.clear(); 
}

//Menu do Display
void Menu_lcd(){
  lcd.setCursor(0,0); 
  lcd.print( "1:Manual            "); 
  lcd.setCursor(0, 1); 
  lcd.print( "2:Automatico        ");
  lcd.setCursor(0, 2); 
  lcd.print( "3:Media             ");
  
   if(digitalRead(bot2) == 0){
   		estadobot2 = !estadobot2;
     	delay(200);
     	lcd.clear();
   }
    
    if(digitalRead(bot1) == 0){
   		estadobot1 = !estadobot1;
     	delay(200);
     	lcd.clear();
   }
  	
  	if(digitalRead(bot3) == 0){
   		estadobot3 = !estadobot3;
     	delay(200);
     	lcd.clear();
   }
}

//Função converte tensão em temperatura
float temperatura() {
  sensors_event_t event;
  dht.temperature().getEvent(&event);

  if (isnan(event.temperature)) {
    Serial.println("Erro na leitura da Temperatura!");
    return 0;  // Retorna 0 em caso de erro
  } else {
    return event.temperature;
  }
}

