// Load Wi-Fi library
#include <WiFi.h>

// Replace with your network credentials
const char* ssid = "Inteli-COLLEGE";
const char* password = "QazWsx@123";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output10State = "desligado";
String output3State = "desligado";
String output15State = "desligado";
String output7State = "desligado";
String output6State = "desligado";
String output5State = "desligado";

// Assign output variables to GPIO pins
const int output10 = 10;
const int output3 = 3;
const int output15 = 15;
const int output7 = 7;
const int output6 = 6;
const int output5 = 5;

bool jogoTerminou = false;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup(){
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(output10, OUTPUT);
  pinMode(output3, OUTPUT);
  pinMode(output15, OUTPUT);
  pinMode(output7, OUTPUT);
  pinMode(output6, OUTPUT);
  pinMode(output5, OUTPUT);
  pinMode(18, OUTPUT);
  // Set outputs to LOW
  digitalWrite(output10, LOW);
  digitalWrite(output3, LOW);
  digitalWrite(output15, LOW);
  digitalWrite(output7, LOW);
  digitalWrite(output6, LOW);
  digitalWrite(output5, LOW);


  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n'){                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // Acendendo led vermelho 
            if (header.indexOf("GET /10/ligado ") >= 0) {
              Serial.println("vermelho 1 ligado ");
              output10State = "ligado ";
              digitalWrite(output10, HIGH);
            }
            // Apagando led vermelho
            else if(header.indexOf("GET /10/desligado") >= 0) {
              Serial.println("vermelho 1 desligado");
              output10State = "desligado";
              digitalWrite(output10, LOW);
            }

            // Acendendo led branco
            if (header.indexOf("GET /7/ligado") >= 0) {
              Serial.println("branco ligado");
              output7State = "ligado";
              digitalWrite(output7, HIGH);
            }
            // Apagando led branco
            else if(header.indexOf("GET /7/desligado") >= 0) {
              Serial.println("branco desligado");
              output7State = "desligado";
              digitalWrite(output7, LOW);
            }

            // Acendendo led azul
            if (header.indexOf("GET /3/ligado ") >= 0) {
              Serial.println("azul 1 ligado ");
              output3State = "ligado ";
              digitalWrite(output3, HIGH);
            }
            // Apagando led azul
            else if (header.indexOf("GET /3/desligado") >= 0) {
              Serial.println("azul 1 desligado");
              output3State = "desligado";
              digitalWrite(output3, LOW);
            }
            // Acendendo led azul 2
            if (header.indexOf("GET /15/ligado") >= 0) {
              Serial.println("azul 2 ligado");
              output15State = "ligado";
              digitalWrite(output15, HIGH);
            }
            // Apagando led azul 2
            else if (header.indexOf("GET /15/desligado") >= 0) {
              Serial.println("azul 2 desligado");
              output15State = "desligado";
              digitalWrite(output15, LOW);
            }

            // Acendendo led vermelho 2
            if (header.indexOf("GET /6/ligado") >= 0) {
              Serial.println("vermelho 2 ligado");
              output6State = "ligado";
              digitalWrite(output6, HIGH);
            }
            // Apagando led vermelho 2
            else if (header.indexOf("GET /6/desligado") >= 0) {
              Serial.println("vermelho 2 desligado");
              output6State = "desligado";
              digitalWrite(output6, LOW);
            }
            // Acendendo led verde
            if (header.indexOf("GET /5/ligado") >= 0) {
              Serial.println("verde ligado");
              output5State = "ligado";
              digitalWrite(output5, HIGH);
              delay(80);
              tone(18, 500, 200);
              delay(2000);
              digitalWrite(output5, LOW);
              delay(80);
            }
            // Apagando led verde
            else if (header.indexOf("GET /5/desligado") >= 0) {
              Serial.println("verde desligado");
              output5State = "desligado";
              digitalWrite(output5, LOW);
            }

            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/desligado buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>DESCUBRA QUAL E O LED VERDE</h1>");
            client.println("<body><h4>Clique no botao abaixo para descobrir se ele e da cor verde. Caso nao seja, o outro jogador deve ter a sua chance!!!</h4>");
      
            if (output10State=="desligado") {
              client.println("<p><a href=\"/10/ligado \"><button class=\"button\">PODE SER O VERDE</button></a></p>");
            }
            else {
              client.println("<p><a href=\"/10/desligado\"><button class=\"button button2\">IXII TA LONGE, OLHA NA PLACA E DEIXE QUEM SABE JOGAR.</button></a></p>");
              
              client.println("<p><a href=\"/10/desligado\"><button class=\"button button2\">Proximo jogador</button></a></p>");
            }

            if (output15State=="desligado") {
              client.println("<p><a href=\"/15/ligado \"><button class=\"button\">PODE SER O VERDE</button></a></p>");
            }
            else {
              client.println("<p><a href=\"/15/desligado\"><button class=\"button button2\">Nao foi dessa vez, mas continue</button></a></p>");

              client.println("<p><a href=\"/10/desligado\"><button class=\"button button2\">Proximo jogador</button></a></p>");
            } 
                  
            if (output3State=="desligado") {
              client.println("<p><a href=\"/3/ligado \"><button class=\"button\">PODE SER O VERDE</button></a></p>");
            } else {
              client.println("<p><a href=\"/3/desligado\"><button class=\"button button2\">Voce me surpreende com a sua habilidade!!!</button></a></p>");

              client.println("<p><a href=\"/10/desligado\"><button class=\"button button2\">Proximo jogador</button></a></p>");
            }


            if (output7State=="desligado") {
              client.println("<p><a href=\"/7/ligado \"><button class=\"button\">PODE SER O VERDE</button></a></p>");
            }
            else {
              client.println("<p><a href=\"/7/desligado\"><button class=\"button button2\">Eita, voce esta chegando perto</button></a></p>");

              client.println("<p><a href=\"/10/desligado\"><button class=\"button button2\">Proximo jogador</button></a></p>");
            }
      
            if (output6State=="desligado") {
              client.println("<p><a href=\"/6/ligado \"><button class=\"button\">PODE SER O VERDE</button></a></p>");
            }
            else{
              client.println("<p><a href=\"/6/desligado\"><button class=\"button button2\">Voce e bom, continue tentando!!!</button></a></p>");

              client.println("<p><a href=\"/10/desligado\"><button class=\"button button2\">Proximo jogador</button></a></p>");
            }
   
            if (output5State=="desligado") {
              client.println("<p><a href=\"/5/ligado \"><button class=\"button\">PODE SER O VERDE</button></a></p>");
            }
            
            else{
              client.println("<p><a href=\"/6/desligado\"><button class=\"button button2\">UHUUL, VOCE GANHOU</button></a></p>");

              jogoTerminou = true;

              delay(3000);


              client.println("<script>location.href = 'http://192.168.1.125';</script>");

              
            }


            client.println("</body></html>");
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            // break;
          }
          else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        }
        else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    // client.stop();

    Serial.println("Client disconnected.");
    Serial.println("");

    if(jogoTerminou) {

      delay(2000);
      ESP.restart();
              
    }

    
    
  }
}