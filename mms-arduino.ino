//wifi
#include <Arduino.h>
#if defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#elif defined(ESP32)
#include <WiFi.h>
#include <AsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>
#include <WebSerial.h>

#include "EEPROM.h"

int pos_addr = 0;
#define EEPROM_SIZE 201

AsyncWebServer server(80);
const char* ssid = "Eshwar_HS";          // Your WiFi SSID
const char* password = "Home@123";


// wifi
class SimplePID {
  private:
    float kp, kd, ki, umax; // Parameters
    float eprev, eintegral, prevpwr = 1; // Storage

  public:
    // Constructor
    SimplePID() : kp(1), kd(0), ki(0), umax(255), eprev(0.0), eintegral(0.0) {}

    // A function to set the parameters
    void setParams(float kpIn, float kdIn, float kiIn, float umaxIn) {
      kp = kpIn; kd = kdIn; ki = kiIn; umax = umaxIn;
    }

    // A function to compute the control signal
    void evalu(int value, int target, float deltaT, int &pwr, int &dir) {
      // error
      int e = target - value;

      // derivative
      float dedt = (e - eprev) / (deltaT);

      // integral
      eintegral = eintegral + e * deltaT;

      // control signal
      float u = kp * e + kd * dedt + ki * eintegral;


      // motor power
      pwr = (int) fabs(u);

      //Initial jerk control
      if ( pwr - prevpwr > 1) {
        pwr = prevpwr;
        prevpwr += 1 ;
      }
      //Initial jerk control

      if ( pwr > umax ) {
        pwr = umax;
      }

      // motor direction
      dir = 1;
      if (u < 0) {
        dir = -1;
      }

      // store previous error
      eprev = e;
    }
};

#include <StackArray.h>
#define n 16 // n*n grid
#define NMOTORS 2

int r = n % 2; // odd or even numbered grid
int hx = 8, hy = 8, dev_x = 0, dev_y = 0; // hx, hy is the size of the 2nd quadrant of the maze; dev_x and dev_y are the deviation of the center from true center
int x, y, ff_count = 0;
short int cost[n][n]; // storing cost value of the maze.
short int wall_data[256][4];
short path[200], counter = 1;
short int path2[50], counter2 = 1; // No function; this is removing a bug somehow
unsigned int curr_x = 0, curr_y = 0, theta = 0; // the starting position is always cell 1,1 (0,0 in terms of array); theta can be 0 for North or 90 for East
bool first_cell = true;

// Pins
const int encb[] = {15, 4};
const int enca[] = {2, 16};
const int pwm[] = {33, 13};
const int in1[] = {26, 14};
const int in2[] = {25, 12};
const int sty = 27;
const int motCh[] = {0, 1};
short expMode = 17;
short expLED = 23;
//short speedButton = 5;
//short speedLED = 19; // led4 19
//bool chSpeed = 0;
short exploration = 1; // 1 is for exploration. 0 is for fast run

const int freq = 5000;
const int resolution = 8;

volatile int posi[] = {0, 0};
volatile int lastEncoded[] = {0, 0};

int pwr[] = {0, 0};
int dir[] = {0, 0};

long prevT = 0;
int target[NMOTORS];

const int frontIRPin = 34 ;
const int rightIRPin = 35 ;
const int leftIRPin = 32 ;
int botSpeed = 175;

// PID class instances
SimplePID pid[NMOTORS];

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
  //wifi_init();
  EEPROM_init();
  set_cost();
  motor_setup();
  pcb_setup();
  first_cell_wall();
  path[0] = 0;
  path2[0] = 0;
  delay(5000);
  //moveBackwardM();
  moveX(481);

  // moveForwardM(-1);
}

void loop() {
  if (exploration) {
    update_wall();
    if (first_cell) {
      //      update_current_cell();
      first_cell = false;
      moveForwardM(1);
      update_current_cell();
      pathChange(curr_x, curr_y);
    }
    else {
      decision();
    }
  }
  else {
    Serial.println("inside else");
    counter =0;
    copyFromEEPROM();
    for (int i=0;i<145;i++){
      Serial.printf("path[%d] =%d \n",i,path[i]);
      if((path[i]==0) && (path[i+1]==0) && (path[i+2]==0) && (path[i+3]==0) && (path[i+4]==0)) break;
      counter++;
    }
    delay(1000);
    Serial.printf("counter =%d \n",counter);
     delay(5000);
    //counter =124;
    botSpeed = 225;
    toGoal();
    delay(10000);
  }
  //Serial.println("F = "+String(analogRead(34))+" R = "+String(analogRead(35))+" L = "+String(analogRead(32)));
  //delay(100);
}


void wifi_init()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.printf("WiFi Failed!\n");
    return;
  }
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  // WebSerial is accessible at "<IP Address>/webserial" in browser
  WebSerial.begin(&server);
  /* Attach Message Callback */
  // WebSerial.msgCallback(recvMsg);
  server.begin();
  // WIFI
  WebSerial.printf("hello from mouse");
}

void EEPROM_init()
{
  if (!EEPROM.begin(EEPROM_SIZE))
  {
    Serial.println("failed to initialise EEPROM"); delay(1000000);
  }
}
