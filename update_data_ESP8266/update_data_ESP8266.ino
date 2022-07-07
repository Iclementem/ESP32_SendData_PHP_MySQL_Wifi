#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

//-------------------VARIABLES GLOBALES--------------------------
const char* ssid = "movistar_5BC4"; // Nombre de la red wifi.      
const char* password = "eFtsdasd656A"; // Clave de la red wifi.
const char *host = "192.168.1.3"; // IP host

int ldrvalue=0; 
byte cont = 0;
byte max_intentos = 50;

void setup() {
  // Inicia Serial
  Serial.begin(115200);
  Serial.println("\n");

  // Conexión WIFI
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED and cont < max_intentos) { //Cuenta hasta 50 si no se puede conectar lo cancela
    cont++;
    delay(500);
    Serial.print(".");
  }

Serial.println("");

  if (cont < max_intentos) {  //Si se conectó      
      Serial.println("********************************************");
      Serial.print("Conectado a la red WiFi: ");
      Serial.println(WiFi.SSID());
      Serial.print("IP: ");
      Serial.println(WiFi.localIP());
      Serial.print("macAdress: ");
      Serial.println(WiFi.macAddress());
      Serial.println("*********************************************");
  }
  else { //No se conectó
      Serial.println("------------------------------------");
      Serial.println("Error de conexion");
      Serial.println("------------------------------------");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  HTTPClient http;    //Declare object of class HTTPClient
  WiFiClient client;
 
  String LdrValueSend, postData;
  
  LdrValueSend = String(ldrvalue);   //Coversión de String a Integer
 
  //Post Data
  postData = "ldrvalue=" + LdrValueSend;

  Serial.println("Mandando información a la base de datos...");
  http.begin(client, "http://192.168.1.3:8080/iclementem/InsertDB.php");              //Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");                //Specify content-type header

  
  int httpCode = http.POST(postData);   //Send the request
  String payload = http.getString();    //Get the response payload

  //Serial.println("LDR Value=" + ldrvalue);
  Serial.println("Valor escrito=" + LdrValueSend);
  ldrvalue++;
  http.end();  //Close connection

  delay(5000);  //Here there is 4 seconds delay plus 1 second delay below, so Post Data at every 5 seconds
}
