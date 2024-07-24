void update_wall() {
  if (wallFront()) {
    wall_data[curr_x * 16 + curr_y][((theta % 360) / 90) % 4] = 1;
    if (theta % 360 == 0) {
      setWall(curr_x, curr_y, 'n');
    }
    else if (theta % 360 == 90) {
      setWall(curr_x, curr_y, 'e');
    }
    else if (theta % 360 == 180) {
      setWall(curr_x, curr_y, 's');
    }
    else {
      setWall(curr_x, curr_y, 'w');
    }
  }
  else {
    wall_data[curr_x * 16 + curr_y][((theta % 360) / 90) % 4] = 0;
  }
  if (wallRight()) {
    wall_data[curr_x * 16 + curr_y][((theta % 360) / 90 + 1) % 4] = 1;
    if (theta % 360 == 0) {
      setWall(curr_x, curr_y, 'e');
    }
    else if (theta % 360 == 90) {
      setWall(curr_x, curr_y, 's');
    }
    else if (theta % 360 == 180) {
      setWall(curr_x, curr_y, 'w');
    }
    else {
      setWall(curr_x, curr_y, 'n');
    }
  }
  else {
    wall_data[curr_x * 16 + curr_y][((theta % 360) / 90 + 1) % 4] = 0;
  }
  if (wallLeft()) {
    wall_data[curr_x * 16 + curr_y][((theta % 360) / 90 + 3) % 4] = 1;
    if (theta % 360 == 0) {
      setWall(curr_x, curr_y, 'w');
    }
    else if (theta % 360 == 90) {
      setWall(curr_x, curr_y, 'n');
    }
    else if (theta % 360 == 180) {
      setWall(curr_x, curr_y, 'e');
    }
    else {
      setWall(curr_x, curr_y, 's');
    }
  }
  else {
    wall_data[curr_x * 16 + curr_y][((theta % 360) / 90 + 3) % 4] = 0;
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
