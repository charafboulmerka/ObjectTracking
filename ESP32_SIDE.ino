#include <Servo.h>
#include<ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <math.h>

// WiFi Definitions
const char* ssid = "acer";
const char* password = "123456789"; // has to be longer than 7 chars
WiFiServer server(80);




#define ServoH_pin D1
#define ServoV_pin D2

#define phone_w 1080
#define phone_h 1705

#define center_vertical 500
#define center_horizontal 700
#define error_range 60
#define tita 3

Servo servoH;
Servo servoV;

//SoftwareSerial hmSerial(2, 3); // RX, TX


int errorV = 0;
int errorH = 0;
int v_angle = 70;
int h_angle = 20;
int xvalue;
int yvalue;
bool first=false;

void setup() {
  Serial.begin(115200);
  //Serial1.begin(9600);
  //Serial.swap();
  delay(10);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  server.begin();
  
   delay(1000);

  servoH.attach(ServoH_pin);
  servoV.attach(ServoV_pin);

  servoH.write(h_angle);
  servoV.write(v_angle);

 

}


void loop() {

  
  

//ReadStrFromEsp();
  WiFiClient client = server.available();
  client.setTimeout(20);
    String req = client.readStringUntil('\r');
    
    if(req != ""){  
//Serial.println(ReadStrFromEsp(req));
// Serial.println(ReadStrFromEsp(req));
String msgFromEsp = ReadStrFromEsp(req);
//Serial.println(msgFromEsp);
if(msgFromEsp!=""){
     ReadDataFromSerial(msgFromEsp);
     calculateError();
    while ((errorH > error_range || errorH < -error_range) || (errorV > error_range || errorV < -error_range)) {
      //Serial.println("WHILE");
       client = server.available();
       client.setTimeout(20);
       String req2 = client.readStringUntil('\r');
       //Serial.println(req2);
       String msgFromEsp2 = ReadStrFromEsp(req2);
      if (msgFromEsp2!="") {
        //CheckIfClear(msgFromEsp2);
        ReadDataFromSerial(msgFromEsp2);
        calculateError();
        control_servoV();
       control_servoH();
        PrintErrors();
      }
      delay(20);
      
    }
    
    

    }
    

    }
    


}

String ReadStrFromEsp(String req){
    String final_txt = "";
      String str = getValue(req,'/',1);
    final_txt = str.substring(0,str.length()-4);
  return final_txt;
}

void CheckIfClear(String req){
  if(req=="clear"){
  v_angle = 70;
  h_angle = 20;
 
  servoH.write(h_angle);
  servoV.write(v_angle);
  }
}

void ReadDataFromSerial(String req) {
  String x_y =  req;
  if(x_y.charAt(0)=='c'){
  v_angle = 70;
  h_angle = 20;
  servoV.write(v_angle);
  servoH.write(h_angle);
  Serial.println("clear");
  }else{
  String xval = getValue(x_y, ',', 0);
  String yval = getValue(x_y, ',', 1);
  if (xval != "" && yval != "") {
    xvalue = xval.toInt();
    yvalue = yval.toInt();
      //Serial.print("x:");
      //Serial.print(xvalue);
      //Serial.print("  || y:");
      //Serial.println(yvalue);

  }
  }

}

void calculateError() {
  errorV = xvalue - center_vertical;
  errorH = yvalue - center_horizontal;
  //Serial.print("ERROR V ");
  //Serial.print(errorV);
  //Serial.print("    || ERROR H ");
  //Serial.println(errorH);
}

void control_servoV() {
  if (errorV > error_range) {
    v_angle = v_angle - tita;
  }
  else if (errorV < -error_range) {
    v_angle = v_angle + tita;
  }
  servoV.write(v_angle);
}

void control_servoH() {
  if (errorH > error_range) {
    h_angle = h_angle + tita;
  }
  else if (errorH < -error_range) {
    h_angle = h_angle - tita;
  }
  servoH.write(h_angle);
}



String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}


void PrintErrors() {
  Serial.print("ErrorV:");
  Serial.print(errorV);
  Serial.print("  ||  ");
  Serial.print("AngleV:");
  Serial.print(v_angle);
  Serial.print("           ");
  Serial.print("ErrorH:");
  Serial.print(errorH);
  Serial.print("  ||  ");
  Serial.print("AngleH:");
  Serial.println(h_angle);
}
