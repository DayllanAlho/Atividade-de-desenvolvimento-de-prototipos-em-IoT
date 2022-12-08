#include <LiquidCrystal_I2C.h>

// Definindo os pinos utilizados para ligar o display LCD
#define I2C_SDA 4
#define I2C_SCL 5

LiquidCrystal_I2C lcd(0x27, 16, 2);

String senha_correta;

void setup(){
  
  Serial.begin(115200); 
  Wire.begin(I2C_SDA, I2C_SCL);
  lcd.init();
  lcd.backlight();

  Serial.println("Digite senha para salvar");

  while(Serial.available() == 0){}
    senha_correta = Serial.readString();
    lcd.setCursor(0, 0);
    lcd.print("Senha salva!");
    delay(1300);
    lcd.clear();
    Serial.println("Senha salva com sucesso");
    Serial.println("Sua senha é: " + senha_correta);
    lcd.print("Sua senha: " + senha_correta);
    delay(2300);
    lcd.clear();
}

void loop() {
  #ifdef RGB_BUILTIN

  Serial.println("Digite a senha:");

  while (Serial.available() == 0) {}     //wait for data available
  String senha_digitada = Serial.readString();  //read until timeout

  // senha_digitada.trim();                        // remove any \r \n whitespace at the end of the String
  if (senha_digitada == senha_correta){
    Serial.println("Senha correta");
    lcd.setCursor(0, 0);
    lcd.print("Validado");
    
    neopixelWrite(RGB_BUILTIN,0,RGB_BRIGHTNESS,0); // Green
    delay(1000);

    delay(3000);
    lcd.clear();
  }
  
  else {
    Serial.println(" ");
    Serial.println("Erro na senha");
    lcd.setCursor(0, 0);
    lcd.print("Nao Validado");
    
    neopixelWrite(RGB_BUILTIN,RGB_BRIGHTNESS,0,0); // Red
    delay(1000);
    
    delay(500);
    Serial.println("Tente novamente");
    Serial.println(" ");


    lcd.clear();
  }

  neopixelWrite(RGB_BUILTIN,0,0,0); // Off / black
  delay(1000);
#endif
}