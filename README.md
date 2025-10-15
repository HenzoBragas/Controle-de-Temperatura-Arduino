# ⚡ Controle de Temperatura de Baterias de Trens 8500

## 📖 Descrição do Projeto
Projeto desenvolvido como **TCC do curso Técnico em Manutenção de Sistemas Ferroviários**.  
Objetivo: **monitorar e controlar a temperatura das baterias dos trens 8500**, utilizadas para alimentar o pantógrafo e conectar o trem à rede elétrica.  

O sistema possui três modos de operação:  
1. **Manual** – Controle direto pelo usuário.  
2. **Automático** – Liga ou desliga ventilador e módulo Peltier de acordo com a temperatura.  
3. **Média** – Realiza múltiplas leituras e calcula a temperatura média.

---

## 🛠 Tecnologias Utilizadas
- **💻 Arduino IDE** – Desenvolvimento do código.  
- **🔧 Arduino Uno** – Placa utilizada.  
- **🌡 DHT11** – Sensor de temperatura e umidade.  
- **📟 LCD 20x4 I2C** – Display para exibição de informações.  
- **⚡ Módulo Peltier** – Controle de temperatura.  
- **💨 Ventilador** – Dissipação térmica do sistema.  
- **🟢 Bibliotecas**:
  - `LiquidCrystal_I2C`
  - `Adafruit_Sensor`
  - `DHT`
  - `DHT_U`

---

## 📝 Funcionalidades
- Leitura contínua da temperatura das baterias.  
- Controle automático do ventilador e do módulo Peltier.  
- Cálculo da média de temperatura em leituras sucessivas.  
- Exibição de dados em **tempo real** no LCD.  
- Menu interativo para seleção de modos de operação.

---

## 🚀 Como Executar
1. **Instalar a Arduino IDE**:  
   [Download Arduino IDE](https://www.arduino.cc/en/software)

2. **Instalar Bibliotecas**:  
   Na Arduino IDE, vá em **Sketch > Incluir Biblioteca > Gerenciar Bibliotecas** e instale:
   - `LiquidCrystal_I2C`
   - `DHT sensor library` (Adafruit)
   - `Adafruit Unified Sensor`

3. **Conectar o Hardware**:
   - LCD I2C: `SDA` -> A4, `SCL` -> A5  
   - Sensor DHT11: Pino digital 2  
   - Botões: Pinos 10, 11 e 12  
   - Ventilador: Pino 8  
   - Módulo Peltier: Pino 9  

4. **Carregar o Código**:
   - Abrir o arquivo `controle_baterias.ino` na Arduino IDE.
   - Selecionar a placa: **Arduino Uno**.
   - Selecionar a porta correta.
   - Clicar em **Upload**.

5. **Operar o Sistema**:
   - Ao ligar o Arduino, o LCD mostrará o menu principal.  
   - Pressione **Botão 1** para Modo Manual, **Botão 2** para Modo Automático, **Botão 3** para Modo Média.
