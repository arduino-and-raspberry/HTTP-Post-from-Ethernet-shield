#include <SPI.h>
#include <Ethernet.h>




int bstate = 0;         // This is the variable we will send, but it will be formated as String first.
String txData ="";      // This is the Data that will be sent to the PHP page. It will have variable names and data in it.

                        // Local Network Settings
                        // My mac 90-A2-DA-0D-83-9D Must be unique on local network
                        // (should be on the back of ethernet shield)
byte mac[]     = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

byte ip[]      = { 192, 168, 88, 231 };       // Must be unique on local network
byte gateway[] = { 192, 168,   1,  1 };         // I left these in for reference in case you need them
byte subnet[]  = { 255, 255, 255,   0 };        // I left these in for reference in case you need them
 byte server[]  = { 192, 168, 88, 242 };
// byte server[]  = { 88, 198, 88, 242 };

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
     
     
     
//     Ethernet.begin(mac, ip); // Mine works with just the mac and ip. Gateway and DNS may be needed.
                              //Depending on your router setup, you may need to
                              // reference http://arduino.cc/en/Reference/EthernetBegin


     
     delay(1000);
}

void loop()
{ 
     bstate++;               //  This just adds one to the variable "bstate" each time thru the loop. I just did this for testing
                             // I send the data as a String. I read about some having difficulties sending integers.
                             // 'txData' is a string that is sent to the PHP page. 

     txData = "{ \"id\": 2, \"testString\": \"547\" }"; 

                             

 //    EthernetClient client;

                                         //("yourwebsite.com",80) could also be, I think an IP, (xxx.xxx.xxx.xxx,80) or
                                         // you could define a variable 'server' like we did with 'ip' and 'mac'
                                         // like this, 'byte server[]  = { xxx, xxx, xxx, xxx }'  
                                         // then this line would look like  'if (client.connect(server,80))'

  
   if (client.connect(server,8080))
    {
         Serial.println("Connected to yourwebsite...");   // This isn't required, just for feedback
         Serial.println();

   
                                      
          client.print("POST /FirstSPRINGJDBC-2.0-SNAPSHOT/rest/api/add HTTP/1.1\n");
          client.print("Host: 192.168.88.242\n");                          
          client.print("Connection: close\n");
          client.print("Content-Type: application/json\n");
          client.print("Content-Length: ");
          client.print(txData.length());                                            
          client.print("\n\n");
          client.print(txData);         // after all of the required junk we send the data
    }    
    else
    {
         Serial.println("Connection Failed."); // Again the Serial is for feedback.   
         Serial.println();
    }
    delay(5000); //this delay was for my test to send a number every 5 sec
}
