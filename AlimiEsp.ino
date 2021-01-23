#include <WiFi.h>


const char* ssid     = ""; // 사용 중 인 와이파이 이름
const char* password = ""; // 와이파이 패스워드

int PIR = 21;
 
WiFiServer server(80);
 
void setup() {

  pinMode(PIR,INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);  // 시리얼 통신, 속도 115200
  delay(10);
  Serial.println();
 
  // Connect to WiFi network
  WiFi.mode(WIFI_STA);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.println(WiFi.localIP());

}
 
void loop() {
  
  delay(50);
  Serial.println(digitalRead(PIR));
  WiFiClient client = server.available();
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println("Refresh: 1");  // 자동으로 웹페이지 새로고침 (1초 설정)
  client.println();
  client.println("<!DOCTYPE html>");
  client.println("<html xmlns='http://www.w3.org/1999/xhtml'>");
  client.println("<head>\n<meta http-equiv='Content-Type' content='text/html; charset=utf-8' />");
  
  
  client.println("<title>교수님 계신가요?</title>"); // 웹 서버 페이지 제목 설정
  client.println("</head>\n<body>");
  client.println("<center>");
  client.println("<br>");
  client.println("<br>");
  client.println("<H1>지금 교수님은..</H1>"); // 페이지 내용 설정
  client.println("<br>");
 
 
  if (digitalRead(PIR) == HIGH) {                      
    client.print("<H1 style='color: blue'>재실중</H1> ");  
    client.println("<br>");
    
    digitalWrite(LED_BUILTIN, HIGH);                  // LED ON

  }
 
  else                                        
  {
    client.print("<H1 style='color: red'>부재중</H1>");       
    client.println("<br>");

    digitalWrite(LED_BUILTIN, LOW);                   // LED OFF                       
  }
 
  client.println("<H1> 입니다!! </H1>"); // 페이지 내용 설정
  client.println("<pre>");
  client.print("</body>\n</html>");

}
