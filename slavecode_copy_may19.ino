// receiver code

//#include <StaticSerialCommands.h>
#include <Servo.h>
//#include <SoftwareSerial.h>
//const byte rxPin = 2;
//const byte txPin = 3;
//SoftwareSerial BTSerial (rxPin, txPin);

// for reading and parsing
const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];        // temporary array for use when parsing
      // variables to hold the parsed data
char messageFromPC[numChars] = {0};
int integer1FromPC = 0; // motor speed val
int integer2FromPC = 0; // brake on/off
//int SkateSpeed = 0;
//int EStop_pressed = 0;
boolean newData = false;


Servo myservo;

int yAxis;
int motorSpeedA = 0;
unsigned int y = 0;

String readString;
char incomingChar;
bool stringComplete = false;

void setup() {
//  readString.reserve(200); // Reserve memory for the string
  myservo.attach(9);

  Serial.begin(9600); // Default communication rate of the Bluetooth module
 // pinMode(rxPin, INPUT);
 // pinMode(txPin, OUTPUT);
//  BTSerial.begin(9600);
}

void loop() {
  // if serial data available, read each char and add to string
  recvWithStartEndMarkers();
  if (newData == true) {
      strcpy(tempChars, receivedChars);
          // this temporary copy is necessary to protect the original data
          //   because strtok() used in parseData() replaces the commas with \0
      parseData();
      showParsedData();
      newData = false;
  }
   if (0 == integer2FromPC) {
      myservo.write(90);
    }
    else if (1 == integer2FromPC) {
     
     
      myservo.write(integer1FromPC);
    }

}


void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;


    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();


        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }


        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}


//============


void parseData() {      // split the data into its parts


    char * strtokIndx; // this is used by strtok() as an index


    //strtokIndx = strtok(tempChars,",");      // get the first part - the string
    //strcpy(messageFromPC, strtokIndx); // copy it to messageFromPC
    // atoi = integer, atof = float, see example page at top for other types
 
    strtokIndx = strtok(tempChars, ","); // this continues where the previous call left off
    integer1FromPC = atoi(strtokIndx);     // convert this part to an integer
//    SkateSpeed = map(integer1FromPC, 0, 180, 70, 110);


    strtokIndx = strtok(NULL, ",");
    integer2FromPC = atoi(strtokIndx);     // convert this part to a float


}


//============


void showParsedData() {
  /*
    //Serial.print("Integer1 ");
    Serial.print(integer1FromPC);
    Serial.print(',');
    //Serial.print("Integer2 ");
    Serial.println(integer2FromPC); */
}
















  /*
  // if serial data available, read each char and add to string
  while (BTSerial.available() > 0) {
    incomingChar = BTSerial.read();
    if (incomingChar != '\n') { // Assuming '\n' is the end of the string
      readString += incomingChar;
    } else {
      stringComplete = true;
      break;
    }
  }

  if (stringComplete) {
    Serial.println(readString); // Print the received string
    // Process the string (e.g., parse data, trigger actions)
    readString = ""; // Clear the string for the next input
    stringComplete = false;
  }

  //break string data into  

}










    if (0 == integer2FromPC) {
      myservo.write(132);
    }
    else if (1 == integer2FromPC) {
      myservo.write(integer1FromPC);
    }
*/