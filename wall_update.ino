void update_wall() {
//  WebSerial.printf("Front = %d,RightIR = %d,LeftIR = %d\n", analogRead(34), analogRead(35),analogRead(32));
  if (wallFront()) {
    wall_data[curr_x * 16 + curr_y][((theta % 360) / 90) % 4] = 1;
//    WebSerial.printf("Updated wall Front 1");
  }
  else {
    wall_data[curr_x * 16 + curr_y][((theta % 360) / 90) % 4] = 0;
//     WebSerial.printf("Updated wall Front 0");
  }
  if (wallRight()) {
    wall_data[curr_x * 16 + curr_y][((theta % 360) / 90 + 1) % 4] = 1;
//     WebSerial.printf("Updated wall Right 1");
  }
  else {
    wall_data[curr_x * 16 + curr_y][((theta % 360) / 90 + 1) % 4] = 0;
//     WebSerial.printf("Updated wall Right 0");
  }
  if (wallLeft()) {
    wall_data[curr_x * 16 + curr_y][((theta % 360) / 90 + 3) % 4] = 1;
//     WebSerial.printf("Updated wall Left 1");
  }
  else {
    wall_data[curr_x * 16 + curr_y][((theta % 360) / 90 + 3) % 4] = 0;
//     WebSerial.printf("Updated wall Left 0");
  }
}


void first_cell_wall() {
  wall_data[0][0] = 0;
  wall_data[0][1] = 1;
  wall_data[0][2] = 1;
  wall_data[0][3] = 1;
}

int front_cell_wall(int curr_x, int curr_y) {
  return wall_data[(curr_x * 16) + curr_y][(theta % 360) / 90];
}

int right_cell_wall(int curr_x, int curr_y) {
  return wall_data[(curr_x * 16) + curr_y][(((theta % 360) / 90) + 1) % 4];
}

int back_cell_wall(int curr_x, int curr_y) {
  return wall_data[(curr_x * 16) + curr_y][(((theta % 360) / 90) + 2) % 4];
}

int left_cell_wall(int curr_x, int curr_y) {
  return wall_data[(curr_x * 16) + curr_y][(((theta % 360) / 90) + 3) % 4];
}
