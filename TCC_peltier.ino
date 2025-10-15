int botao1 = 5;     // Botão para LIGAR
int botao2 = 7;     // Botão para DESLIGAR
int peltier = 10;   // Saída para o módulo Peltier
int v1 = 11;        // Saída para o relé

void setup() {
  pinMode(botao1, INPUT); 
  pinMode(botao2, INPUT); 
  pinMode(peltier, OUTPUT);
  pinMode(v1, OUTPUT);

  digitalWrite(peltier, HIGH); 
  digitalWrite(v1, HIGH);
}

void loop() {
  // --- Botão 1: LIGA ---
  if (digitalRead(botao1) == LOW) { 
    digitalWrite(v1, HIGH);      // Liga o relé
    digitalWrite(peltier, HIGH); // Liga o Peltier
    delay(300); 
  }

  // --- Botão 2: DESLIGA ---
  if (digitalRead(botao2) == LOW) {
    digitalWrite(v1, LOW);       // Desliga o relé
    digitalWrite(peltier, LOW);  // Desliga o Peltier
    delay(300); 
  }
}
