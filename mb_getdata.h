#include <ModbusMaster.h>

#define MAX485_DE 5
#define MAX485_RE_NEG 4
#define RX_PIN 16
#define TX_PIN 17

bool flag = 0;

void init_whole() {
  Serial1.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);
  pinMode(MAX485_RE_NEG, OUTPUT);
  pinMode(MAX485_DE, OUTPUT);
  digitalWrite(MAX485_RE_NEG, 0);
  digitalWrite(MAX485_DE, 0);
  flag = 1;
}

class modb {
public:
  modb(int id_, String endpoint_) {
    id = id_;
    endpoint = endpoint_;
    if (!flag) {
      init_whole();
    }
    node.begin(id, Serial1);
    node.preTransmission(preTransmission);
    node.postTransmission(postTransmission);
  }
  void load_data() {
    
    //float error = modbus_read((4096), 1);
    //Serial.print("Running Frequency: ");
    float runningfreq = modbus_read((4097), 1);
    //Serial.print("Bus Voltage: ");
    float busvoltage = modbus_read((4098),1);
    //Serial.print("Output Voltage: ");
    float outputvoltage= modbus_read((4099), 1);
    //Serial.print("Output Current: ");
    float outputcurrent = modbus_read(4100, 1);
    //Serial.print("Output Power: ");
    float outpower = modbus_read((4101), 1);
    //Serial.print("Out Torque: ");
    float outtorque = modbus_read((4102), 1);
    //Serial.print("Running Speed: ");
    float runningspeed = modbus_read((4103), 1);
    //Serial.print("Input Mark: ");
    float inputmark = modbus_read((4104), 1);
    //Serial.print("Output Mark: ");
    float outputmark = modbus_read((4105), 1);
    //Serial.print("AI1: ");
    float ai1value = modbus_read((4106), 1);
    //Serial.print("AI2: ");
    float ai2value = modbus_read((4107), 1);
    //Serial.print("Cummulative Power On: ");
    float cumpoweron = modbus_read((4108), 1);
   // Serial.print("Cummulative Running: ");
    float cumrunning = modbus_read((4109), 1);
    //Serial.print("Cummulative Consumption: ");
    float cumconsumption = modbus_read((4110), 1);
    //Serial.print("Target Pressure: ");
    float targetpressure = modbus_read((4111), 1);
    //Serial.print("*********************************************************");
    float settingpressure = modbus_read((4112), 1);

    data=String(runningfreq)+","+String(runningspeed)+","+String(outtorque)+","+String(busvoltage)+","+String(outputvoltage)+","+String(outputcurrent)+","+String(outpower)+","+String(cumpoweron)+","+String(cumrunning)+","+String(cumconsumption)+","+String(settingpressure)+","+String(targetpressure)+","+String(inputmark)+","+String(outputmark)+","+String(ai1value)+","+String(ai2value);
  }
  bool push_data() {
    //connect to internet before calling
    String lnk = endpoint + data;
    HTTPClient http;
    http.begin(lnk);
    int httpCode = http.GET();
    if (httpCode > 0) {
      String res = http.getString();
      Serial.println(res);
      return true;
    } else {
      Serial.print("GET err: ");
      Serial.println(httpCode);
      return false;
    }
  }
private:
  ModbusMaster node;
  int id;
  String data = "";
  String endpoint = "";

  float modbus_read(int addr, int sm) {
    delay(100);
    int result = node.readHoldingRegisters(addr, sm);
    uint data;
    float flt = 0;
    if (result == node.ku8MBSuccess) {
    
        data = node.getResponseBuffer(0);
      
    
      Serial.print(id);
      Serial.print(": ");
      Serial.println("response: " + String(data));
      delay(100);
    } else {
      Serial.print(id);
      Serial.print(": ");
      Serial.print("Failed, Response Code: ");
      Serial.print(result, HEX);
      Serial.println(" ");
      delay(100);
    }
    return flt;
  }
  static void preTransmission() {
    digitalWrite(MAX485_RE_NEG, 1);
    digitalWrite(MAX485_DE, 1);
  }

  static void postTransmission() {
    digitalWrite(MAX485_RE_NEG, 0);
    digitalWrite(MAX485_DE, 0);
  }
};