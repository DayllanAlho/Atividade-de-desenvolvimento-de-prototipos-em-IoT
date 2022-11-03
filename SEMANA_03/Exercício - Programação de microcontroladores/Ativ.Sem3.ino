#define ledr 6
#define ledb 15
#define ledg 16
#define ledy 17

#define buzzer 7
#define button 1

#define buttonmestre 2
#define ldr 4

int binaryValue[16] = { 10, 10, 10, 10, 20, 20, 20, 20, 30, 30, 30, 30, 40, 40, 40, 40}; //criação de lista para converte a divisão em binário.(Coloquei estes valores para conseguir verificar a mudança de status dos valores binários).

int soundBuzzer[4] = {0, 0, 0, 0}; //Criando os 4 sons do buzzer.
int ind = 0; // pegando o index.


void Converteandsavebinary(int value){ //  recebe um valor do ldr (0 - 4095), transforma de 0 a 15, converte para binário e salva.

  int addbinary[4] = {0, 0, 0, 0}; // Ao clicar no botão irá salvar o binário da vez.

  for (int i = 3; value != 0; i--){ //começa a contar os 3 primeiros elementos e se for diferente de zero, diminui 1 até zerar.
    addbinary[i] = value % 2; // ele colocar 1 ou 0 dependendo do valor.
    value = value / 2; // converte valor.
  }
    if (addbinary[0] == 1){
      digitalWrite(ledr, HIGH); // acendendo led
      delay(500);
    }

    if (addbinary[1] == 1){
      digitalWrite(ledb, HIGH); // acendendo led
    }

    if (addbinary[2] ==1){
      digitalWrite(ledg, HIGH); // acendendo led
    }

    if (addbinary[3] == 1){
      digitalWrite(ledy, HIGH); // acendendo led
    }
    tone(buzzer, soundBuzzer[ind/4]); // tocando buzzer

    delay(500);
    tone(buzzer, 0); // parando de tocar buzzer

    digitalWrite(ledr, LOW); // apagando led
    digitalWrite(ledb, LOW); // apagando led
    digitalWrite(ledg, LOW); // apagando led
    digitalWrite(ledy, LOW); // apagando led

  int size = (sizeof(binaryValue))/4; // o int pensam 4 byts, pego o tamanho e divido por 4 pois sei que são 16 elementos.
  
  binaryValue[ind] = addbinary[0]; // add valor
  binaryValue[ind+1] = addbinary[1]; // add valor
  binaryValue[ind+2] = addbinary[2]; // add valor
  binaryValue[ind+3] = addbinary[3]; // add valor

  if (ind!= size) { // verificação de é o último elemento, se não for, add mais 4.
    ind+= 4;
  }

}
int convertInterval(int n) {
  return n/ 273; // Conversão de intervalo de 0 a 15 que ler o valor do LDR (0 a 4095)
}

void setup() {
  Serial.begin(9600);
  pinMode(ledr, OUTPUT);
  pinMode(ledb, OUTPUT);
  pinMode(ledg, OUTPUT);
  pinMode(ledy, OUTPUT);

  pinMode(buzzer, OUTPUT);
  
  pinMode(button, INPUT);
  pinMode(buttonmestre, INPUT);
}
void loop() {
  int buttonValue = digitalRead(button);
  int buttonmestreValue = digitalRead(buttonmestre);
  if (buttonmestreValue == 1) { //Pega o valor exato do ldr no momento que o botão mestre for acionado.
    delay(1000);
    ind= 0;
    for (int i = 0; i < 16; i = i+4) {
      if (binaryValue[i] == 1) {
        digitalWrite(ledr, HIGH);
      }
      if (binaryValue[i+1] == 1) {
        digitalWrite(ledb, HIGH);
      }
      if (binaryValue[i+2] == 1) {
        digitalWrite(ledg, HIGH);
      }
      if (binaryValue[i+3] == 1) {
        digitalWrite(ledy, HIGH);
      }
      tone(buzzer, soundBuzzer[i/4]); // tocando o buzzer na ordem do led.
      delay(1000);
      digitalWrite(ledr, LOW);
      digitalWrite(ledb, LOW);
      digitalWrite(ledg, LOW);
      digitalWrite(ledy, LOW);
      tone(buzzer, 0);
      delay(500);
    }
    Serial.print("\n");
    for (int ind= 0; ind< sizeof(binaryValue)/4; ind++) {
      binaryValue[ind] = 0;
    }
    for (int ind= 0; ind< sizeof(soundBuzzer); ind++) {
      soundBuzzer[ind] = 0;
    }
    Serial.println("Valores Zerados");
    Serial.println("Sons Zerados");
  }
  if (buttonValue == 1) {
    delay(1000);
    int ldrValue = analogRead(ldr);
    ldrValue = convertInterval(ldrValue);
    Serial.println(ind);
    
    soundBuzzer[ind/4] = ldrValue * 150;
    Serial.println(ldrValue);

    Converteandsavebinary(ldrValue);
  for (int element : binaryValue) {
    Serial.print(element);
    Serial.print(" ");
  }
  Serial.print("\n");
}
}