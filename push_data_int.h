void ShowSerialData() {
  while (Serial2.available() > 0)
    Serial.write(Serial2.read());
  delay(1000);
}

String read_response_data() {
  String str = "";
  while (Serial2.available() > 0)
    str = str + char(Serial2.read());
  Serial.println(str);
  return str;
}

String sendCommand(String command) {
  Serial.println(command);
  Serial2.println(command);
  delay(1000);
  return read_response_data();
}

// void ShowSerialData() {
//   Serial.println("Show serial data:");
//   while (Serial2.available()) {
//     char c = Serial2.read();
//     Serial.write(c);
//   }
//   Serial.println("");
//   delay(1000);
// }


// void get_dta() {
//   Serial.begin(115200);
//   delay(200);

//   Serial.println(str);

//   // Split the string into substrings
//   while (str.length() > 0) {
//     int index = str.indexOf(' ');
//     if (index == -1)  // No space found
//     {
//       strs[StringCount++] = str;
//       break;
//     } else {
//       strs[StringCount++] = str.substring(0, index);
//       str = str.substring(index + 1);
//     }
//   }
// }

// char StrContains(String str, String sfind) {
//   char found = 0;
//   char index = 0;
//   char len;

//   len = str.length();

//   if (sfind.length() > len) {
//     return 0;
//   }
//   while (index < len) {
//     if (str[index] == sfaind[found]) {
//       found++;
//       if (sfind.length() == found) {
//         return 1;
//       }
//     } else {
//       found = 0;
//     }
//     index++;
//   }

//   return 0;
// }

String get_data() {
  String jk = "{}";
  while (true) {
    //Check if the module is responsive, expected value OK
    sendCommand("AT");
    //close or turn off network connection in case it was left open, expected value OK
    sendCommand("AT+CIPSHUT");
    // close GPRS context bearer in case it was left open, expected value OK
    sendCommand("AT+SAPBR=0,1");
    // open GPRS context establish GPRS connection
    sendCommand("AT+SAPBR=3,1,\"Contype\",\"GPRS\"");
    //Set the Access Point Name (APN) for the network provider
    //change this apn value for your SIM card
    sendCommand("AT+SAPBR=3,1,\"APN\",\"airtelgprs.com\"");
    //open GPRS context bearer
    sendCommand("AT+SAPBR=1,1");
    //initiate HTTP request
    sendCommand("AT+HTTPINIT");
    //set parameters for http session, HTTP context identifier
    sendCommand("AT+HTTPPARA=\"CID\",1");
    //Change the URL from google.com to the server you want to reach
   sendCommand("AT+HTTPPARA=\"URL\",\"http://13.233.93.242/projects/energy/api/get-max.php?mid=101\"");
    // sendCommand("AT+HTTPPARA=\"URL\",\"http://13.233.93.242/projects/energy/api/get-messaging-mobile-numbers.php?mid=101\"");

    //Initiate the HTTP GET request, send http request to specified URL
    // ;
    // Wait for the response (adjust the delay as needed)

    // Read the HTTP response, normally contains status code 200 if successful
    sendCommand("AT+HTTPACTION=0");
    delay(3000);
    String jk = String(sendCommand("AT+HTTPREAD"));
    // Serial.println(jk);
    if (jk.indexOf("+HTTPACTION:0,200") != -1) {
      jk = "{\"data\":[" + jk.substring(53, 65) + "]}";
      return jk;
    }

    sendCommand("AT+HTTPTERM");
    //close or turn off network connection
    sendCommand("AT+CIPSHUT");
    // close GPRS context bearer
    sendCommand("AT+SAPBR=0,1");
  }
}
////////////////////////////////////////////////////////////////
String get_num() {
  String jk = "{}";
  while (true) {
    //Check if the module is responsive, expected value OK
    sendCommand("AT");
    //close or turn off network connection in case it was left open, expected value OK
    sendCommand("AT+CIPSHUT");
    // close GPRS context bearer in case it was left open, expected value OK
    sendCommand("AT+SAPBR=0,1");
    // open GPRS context establish GPRS connection
    sendCommand("AT+SAPBR=3,1,\"Contype\",\"GPRS\"");
    //Set the Access Point Name (APN) for the network provider
    //change this apn value for your SIM card
    sendCommand("AT+SAPBR=3,1,\"APN\",\"airtelgprs.com\"");
    //open GPRS context bearer
    sendCommand("AT+SAPBR=1,1");
    //initiate HTTP request
    sendCommand("AT+HTTPINIT");
    //set parameters for http session, HTTP context identifier
    sendCommand("AT+HTTPPARA=\"CID\",1");
    //Change the URL from google.com to the server you want to reach
   // sendCommand("AT+HTTPPARA=\"URL\",\"http://13.233.93.242/projects/energy/api/get-max.php?mid=101\"");
    sendCommand("AT+HTTPPARA=\"URL\",\"http://13.233.93.242/projects/energy/api/get-messaging-mobile-numbers.php?mid=101\"");

    //Initiate the HTTP GET request, send http request to specified URL
    // ;
    // Wait for the response (adjust the delay as needed)

    // Read the HTTP response, normally contains status code 200 if successful
    sendCommand("AT+HTTPACTION=0");
    delay(3000);
    String jk = String(sendCommand("AT+HTTPREAD"));
    // Serial.println(jk);
    if (jk.indexOf("+HTTPACTION:0,200") != -1) {
      jk = "{\"data\":[" + jk.substring(53, 111) + "]}";
      return jk;
    }

    sendCommand("AT+HTTPTERM");
    //close or turn off network connection
    sendCommand("AT+CIPSHUT");
    // close GPRS context bearer
    sendCommand("AT+SAPBR=0,1");
  }
}

void put(String send_val) {

  //Check if the module is responsive, expected value OK
  sendCommand("AT");
  //close or turn off network connection in case it was left open, expected value OK
  sendCommand("AT+CIPSHUT");
  // close GPRS context bearer in case it was left open, expected value OK
  sendCommand("AT+SAPBR=0,1");
  // open GPRS context establish GPRS connection
  sendCommand("AT+SAPBR=3,1,\"Contype\",\"GPRS\"");
  //Set the Access Point Name (APN) for the network provider
  //change this apn value for your SIM card
  sendCommand("AT+SAPBR=3,1,\"APN\",\"airtelgprs.com\"");
  //open GPRS context bearer
  sendCommand("AT+SAPBR=1,1");
  //initiate HTTP request
  sendCommand("AT+HTTPINIT");
  //set parameters for http session, HTTP context identifier
  sendCommand("AT+HTTPPARA=\"CID\",1");
  //Change the URL from google.com to the server you want to reach
  String lnk = "http://13.233.93.242/projects/energy/api/log.php?mid=101&machine=$" + send_val;
  Serial.println(sendCommand("AT+HTTPPARA=\"URL\",\"" + lnk + "\""));
  //Initiate the HTTP GET request, send http request to specified URL
  // ;
  // Wait for the response (adjust the delay as needed)

  // Read the HTTP response, normally contains status code 200 if successful
  sendCommand("AT+HTTPACTION=0");
  delay(3000);
  sendCommand("AT+HTTPREAD");

  sendCommand("AT+HTTPTERM");
  //close or turn off network connection
  sendCommand("AT+CIPSHUT");
  // close GPRS context bearer
  sendCommand("AT+SAPBR=0,1");
}

void message(String number, String text) {
  //send sms
  // Serial.println(sendCommand("AT+CMGF=1"));
  // delay(100);
  // Serial.println(sendCommand("AT+CMGS=\""+number+"\"\r"));
  // delay(100);
  // Serial.println(sendCommand(text.c_str()));
  // delay(100);
  // Serial.println(sendCommand(String((char)26).c_str()));
  // delay(4000);
}

void gprs_init(byte rx_gprs, byte tx_gprs) {
  Serial2.begin(9600, SERIAL_8N1, rx_gprs, tx_gprs);
}
