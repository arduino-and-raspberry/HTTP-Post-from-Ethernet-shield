#include <SPI.h>
#include <Ethernet.h>


int bstate = 0;         // This is the variable we will send, but it will be formated as String first.
String txData ="";      // This is the Data that will be sent to the PHP page. It will have variable names and data in it.
String jsonString ="";


byte mac[]     = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

byte ip[]      = { 192, 168, 88, 231 };       // Must be unique on local network
byte gateway[] = { 192, 168,   1,  1 };         
byte subnet[]  = { 255, 255, 255,   0 };        
byte server[]  = { 192, 168, 88, 242 };

EthernetClient client;

void setup()
{

Serial.begin(9600);      // Just for output so we can see if its working
 
     // запускаем Ethernet-соединение:
  if (Ethernet.begin(mac) == 0) {
    // если не удалось сконфигурировать Ethernet при помощи DHCP
    Serial.println("Failed to configure Ethernet using DHCP");
    // продолжать дальше смысла нет, поэтому вместо DHCP
    // попытаемся сделать это при помощи IP-адреса:
    Ethernet.begin(mac, ip);
  }

delay(1000);

  // получаем  и выводим локальный IP адрес
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());
  // даем Ethernet 1 секунду на инициализацию
  delay(1000);
  Serial.println("connecting...");      
  delay(1000);
  postData();
}

void loop()
{ 

 
}

void postData(){
  
txData = 157;
jsonString = "{ \"temp\": \""+txData+"\" }"; 

  
   if (client.connect(server,8080))
    {
         Serial.println("Connected to yourwebsite...");   // This isn't required, just for feedback
         Serial.println(); 
                                      
          client.print("POST /RCCT-2.0-SNAPSHOT/rest/users/add HTTP/1.1\n");
          client.print("Host: 192.168.88.242\n");                          
          client.print("Connection: close\n");
          client.print("Content-Type: application/json\n");
          client.print("Content-Length: ");
          client.print(txData.length());                                            
          client.print("\n\n");
          client.print(txData); 
    }    
    else
    {
         Serial.println("Connection Failed."); // Again the Serial is for feedback.   
         Serial.println();
    }
    delay(5000);

} 