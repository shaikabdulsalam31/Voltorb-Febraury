#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(D0, D1, D2, D3, D4, D5);

AsyncWebServer server(80);

const char* ssid = "Net 2.0"; 
const char* password = "Error1234asdf#";

const char* PARAM_INPUT_1 = "input1";

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>Valentine's day</title>
  <meta name="viewport" content="width=device-width, initial-scale=5">
<p> <font size="9" face="sans-serif"> <marquee> Today is Feb 14 </marquee> </font> </p>
  </head><body><center>
  <form action="/get">
    Enter Secret code: <input type="text" name="input1">
    <input type="submit" value="Send">
  </form><br>
 
</center></body></html>)rawliteral";

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void setup() {
  Serial.begin(115200);
   lcd.begin(16, 2);
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("Hello!,I'm Shaik Abdul Salam");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Failed!");
    return;
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String message;
    String inputParam;
    String msg;
    if (request->hasParam(PARAM_INPUT_1)) {
      message = request->getParam(PARAM_INPUT_1)->value();
      inputParam = PARAM_INPUT_1;
      if(message=="UVCE"){
        msg=" I Love You";
       lcd.clear();
       lcd.setCursor(0,0);
      
      lcd.print(msg);
      }
      else {
      message = "Your Class is in Right ";
      inputParam = "none";
      lcd.clear();
       lcd.setCursor(0,0);
      
      lcd.print(message);
    }
    }
    else {
      message = "Your Class is in Right ";
      inputParam = "none";
      lcd.clear();
       lcd.setCursor(0,0);
      
      lcd.print(message);
    }
    Serial.println(message);
   
  request->send(200, "text/html", index_html);
  });
  server.onNotFound(notFound);
  server.begin();
}

void loop() {
    for (int positionCounter = 0; positionCounter < 29; positionCounter++) {
    lcd.scrollDisplayLeft();
    delay(500);
  }
}
