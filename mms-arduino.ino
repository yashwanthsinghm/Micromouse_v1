#include <StackArray.h>
#define n 16 // n*n grid

int r = n % 2; // odd or even numbered grid
int hx = 8, hy = 8, dev_x = 0, dev_y = 0; // hx, hy is the size of the 2nd quadrant of the maze; dev_x and dev_y are the deviation of the center from true center
int x, y, ff_count = 0;
short int cost[n][n]; // storing cost value of the maze.
short int wall_data[256][4];
unsigned int path[300], counter = 1;
short int path2[5], counter2 = 1; // No function; this is removing a bug somehow
unsigned int curr_x = 0, curr_y = 0, theta = 0; // the starting position is always cell 1,1 (0,0 in terms of array); theta can be 0 for North or 90 for East
bool first_cell = true;

//MOTOR
//MOTOR A
int PWMA = PB8; //Speed control 
int AIN1 = 9; //Direction
int AIN2 = 8; //Direction
//Motor B
int PWMB = PB9; //Speed control
int BIN1 = 11; //Direction
int BIN2 = 12; //Direction
//MOTOR

void setup() {
  Serial.begin(19200);
  pinMode(PC13, OUTPUT);
//  digitalWrite(PC13, LOW);
  set_cost();
  motor_setup();
  IR_setup();
  first_cell_wall();
  path[0] = 0;
  path2[0] = 0;
//  setColor(0, 0, 'G');
}

void loop() {
  //  log("Running...");
  update_wall();
  if (first_cell) {
    //    initial_movement();
    first_cell = false;
    moveForward();
    update_current_cell();
    pathChange(curr_x, curr_y);
  }
  else {
//    log("Entering main function loop");
    log("");
    decision();
  }
}
