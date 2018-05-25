#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

const char* ssid = "************";
const char* wifipass = "**************";
int baud = 115200;
String server = "http://*****************"; //server address.  Include http://
String loginapi = "/api/method/login";
String erpuser = "***************";  //username of user to be logged in
String erppass = "***************"; //password of user to be logged in
String loginaddress = server + loginapi;
String loginstr = "usr=" + erpuser + "&pwd=" + erppass;

void setup() {

  Serial.begin(baud);                                  //Serial connection
  WiFi.begin(ssid, wifipass);   //WiFi connection

  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion

    delay(500);
    Serial.println("Waiting for connection");

  }

}
void Authenticate() {
    HTTPClient http;
    const char * headerKeys[] = {"system_user", "user_image", "user_id", "full_name", "sid"} ;
    size_t headerKeysCount = sizeof(headerKeys)/sizeof(char*);
    http.collectHeaders(headerKeys, headerKeysCount);
    String PostData = loginstr;
  http.begin(loginaddress);
  http.addHeader("Content-type",   "application/x-www-form-urlencoded");
  int code = http.POST(PostData);
  Serial.printf("[HTTP] POST... code: %d\r\n", code);
  String res = http.getString(); 
  Serial.printf("Header count: %d\r\n", http.headers());
  for (int i=0; i < http.headers(); i++) {
    Serial.printf("%s = %s\r\n", http.headerName(i).c_str(),  http.header(i).c_str());
  }
  Serial.printf("Res 1 = %s\r\n", res.c_str());
}

void loop() {

  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    Authenticate();
    //delay(500);
    //getRequest();
    //delay(500);
  } else {

    Serial.println("Error in WiFi connection");

  }

  delay(5000);

}
