#define DEBUG_ETHERNET_WEBSERVER_PORT Serial
#define _ETHERNET_WEBSERVER_LOGLEVEL_ 3
#include <WebServer_WT32_ETH01.h>
#define sensor1 2
#define sensor2 4
#define sensor3 35
#define sensor4 14
#define t1 39
#define t2 36
#define t3 15

WiFiServer server(80);

bool s1, s2, s3, s4, tp1, tp2, tp3;
int Time;
String color1, color2, color3, color4;

void setup() {
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);
  pinMode(t1, INPUT);
  pinMode(t2, INPUT);
  pinMode(t3, INPUT);
  Serial.begin(115200);
  while (!Serial)
    ;
  Serial.print("\nIniciando o WebServer em " + String(ARDUINO_BOARD));
  Serial.println(" com " + String(SHIELD_TYPE));
  Serial.println(WEBSERVER_WT32_ETH01_VERSION);
  WT32_ETH01_onEvent();
  ETH.begin(ETH_PHY_ADDR, ETH_PHY_POWER);
  WT32_ETH01_waitForConnect();
  server.begin();
}

void loop() {
  tp1 = digitalRead(t1);
  tp2 = digitalRead(t2);
  tp3 = digitalRead(t3);
  if (tp1 == LOW && tp2 == LOW && tp3 == LOW) { Time = 120; }
  if (tp1 == HIGH && tp2 == LOW && tp3 == LOW) { Time = 60; }
  if (tp1 == LOW && tp2 == HIGH && tp3 == LOW) { Time = 30; }
  if (tp1 == LOW && tp2 == LOW && tp3 == HIGH) { Time = 15; }
  if (tp1 == HIGH && tp2 == HIGH && tp3 == HIGH) { Time = 5; }
  s1 = digitalRead(sensor1);
  s2 = digitalRead(sensor2);
  s3 = digitalRead(sensor3);
  s4 = digitalRead(sensor4);
  if (s1 == LOW) {
    color1 = "green";
  } else {
    color1 = "red";
  }
  if (s2 == LOW) {
    color2 = "green";
  } else {
    color2 = "red";
  }
  if (s3 == LOW) {
    color3 = "green";
  } else {
    color3 = "red";
  }
  if (s4 == LOW) {
    color4 = "green";
  } else {
    color4 = "red";
  }
  WiFiClient client = server.available();
  if (client) {
    Serial.println(F("Novo cliente"));
    bool currentLineIsBlank = true;

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n' && currentLineIsBlank) {
          Serial.println(F("Enviando resposta"));
          client.print(
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "Connection: close\r\n");
          //client.print("Refresh: 10 \r\n");  //refresh pelo time
          client.print(String("Refresh:") + Time + "\r\n");  //refresh pelo time
          client.print("\r\n");
          client.print("<!DOCTYPE HTML>\r\n");
          client.print("<html lang='pt-BR'>");
          client.print("<head>");
          client.print("<meta charset='UTF-8'>");
          client.print("<meta name='viewport' content='width=device-width, initial-scale=1.0'>");
          client.print("<title> Door Sensor System </title>");
          //client.print("<style> body { text-align: center, font-family: Arial, sans-serif; } h5 { text-align:center}img { max-width: 80%; height: auto; margin: 20px auto; } table { width: auto; margin: 20px auto; border-collapse: collapse; } table, th, td { border: 1px solid #ddd; padding: 10px; text-align: center; font-size:10px;} th { background-color: #f2f2f2;  } caption{text-align:center;}</style>");
          client.print("<style> body { text-align: center, font-family: Arial, sans-serif; } table { width: 100%; margin: auto; border-collapse: collapse; } table, th, td { border: 1px solid #ddd; padding: 10px; text-align: center; font-size:10px;} th { background-color: #f2f2f2;  } </style>");
          client.print("</head>");
          client.print("<body>");
          /*client.println("<div style='display: flex; justify-content: center; align-items: center; height: 20vh;'>");
          //client.println("<img src='https://pacsafe.com.br/wp-content/uploads/2021/09/Logo-Pac-Safe-Portaria-Remota-1024x433.png' alt='Image' style='width:400px; height: 200px;'>");
          client.println("<img src='https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcRz1evY3ct-qw18LhXzYu7zKuAcTp25sQzhj6b27xQDMQ&s' alt='Image'style='width:auto; height: auto;'>");  //  text-align: center;'Substitua o URL com o link da imagem desejada
          client.println("</div>");*/
          client.print("<table>");
          // client.print("<caption>Leitura dos Sensores</caption>");

          client.print("<thead>");
          client.print("<tr>");
          client.print("<th>PORTÃO</th>");
          client.print("</tr>");
          client.print("</thead>");
          client.print("<tbody>");
          /*
          client.print(String("<tr><td> Pedestre </td> <td id = 'sensor1Value' style='background-color:") + color1 + ";'>" "Pedestre</td> </tr>");
          client.print(String("<tr><td> Eclusa </td> <td id = 'sensor2Value' style='background-color:") + color2 + ";'>" + s2 + "</td> </tr>");
          client.print(String("<tr><td> Veiculo Subsolo </td> <td id = 'sensor3Value' style='background-color:") + color3 + ";'>" + s3 + "</td> </tr>");
          client.print(String("<tr><td> Veiculo Pilotis </td> <td id = 'sensor4Value' style='background-color:") + color4 + ";'>" + s4 + "</td> </tr>");*/
          client.print(String("<tr><td id = 'sensor1Value' style='background-color:") + color1 + ";'>" "PEDESTRE</td> </tr>");
          client.print(String("<tr><td id = 'sensor2Value' style='background-color:") + color2 + ";'>" "ECLUSRA</td> </tr>");
          client.print(String("<tr><td id = 'sensor3Value' style='background-color:") + color3 + ";'>" "SUBSOLO</td> </tr>");
          client.print(String("<tr><td id = 'sensor4Value' style='background-color:") + color4 + ";'>" "PILOTIS</td> </tr>");
          client.print("</tbody>");
          client.print("</table>");
          client.print(String("<font size='1', text-align:center> Tempo de atualização: ") + Time + " S </font>");
          client.print("</body>");
          client.print("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(10);

    // close the connection:
    client.stop();
    Serial.println(F("Cliente desconectado"));
  }
}
