void update_current_cell() {
  if (theta % 360 == 0) {
    curr_y = curr_y + 1;
  }
  if (theta % 360 == 90) {
    curr_x = curr_x + 1;
  }
  if (theta % 360 == 180) {
    curr_y = curr_y - 1;
  }
  if (theta % 360 == 270) {
    curr_x = curr_x - 1;
  }
}

int front_cell_x(int curr_x, int curr_y) {
  if (theta % 360 == 0) {
    return curr_x;
  }
  if (theta % 360 == 90) {
    return curr_x + 1;
  }
  if (theta % 360 == 180) {
    return curr_x;
  }
  if (theta % 360 == 270) {
    return curr_x - 1;
  }
}

int front_cell_y(int curr_x, int curr_y) {
  if (theta % 360 == 0) {
    return curr_y + 1;
  }
  if (theta % 360 == 90) {
    return curr_y;
  }
  if (theta % 360 == 180) {
    return curr_y - 1;
  }
  if (theta % 360 == 270) {
    return curr_y;
  }
}

int right_cell_x(int curr_x, int curr_y) {
  if (theta % 360 == 0) {
    return curr_x + 1;
  }
  if (theta % 360 == 90) {
    return curr_x;
  }
  if (theta % 360 == 180) {
    return curr_x - 1;
  }
  if (theta % 360 == 270) {
    return curr_x;
  }
}

int right_cell_y(int curr_x, int curr_y) {
  if (theta % 360 == 0) {
    return curr_y;
  }
  if (theta % 360 == 90) {
    return curr_y - 1;
  }
  if (theta % 360 == 180) {
    return curr_y;
  }
  if (theta % 360 == 270) {
    return curr_y + 1;
  }
}

int back_cell_x(int curr_x, int curr_y) {
  if (theta % 360 == 0) {
    return curr_x;
  }
  if (theta % 360 == 90) {
    return curr_x - 1;
  }
  if (theta % 360 == 180) {
    return curr_x;
  }
  if (theta % 360 == 270) {
    return curr_x + 1;
  }
}

int back_cell_y(int curr_x, int curr_y) {
  if (theta % 360 == 0) {
    return curr_y - 1;
  }
  if (theta % 360 == 90) {
    return curr_y;
  }
  if (theta % 360 == 180) {
    return curr_y + 1;
  }
  if (theta % 360 == 270) {
    return curr_y;
  }
}


int left_cell_x(int curr_x, int curr_y) {
  if (theta % 360 == 0) {
    return curr_x - 1;
  }
  if (theta % 360 == 90) {
    return curr_x;
  }
  if (theta % 360 == 180) {
    return curr_x + 1;
  }
  if (theta % 360 == 270) {
    return curr_x;
  }
}

int left_cell_y(int curr_x, int curr_y) {
  if (theta % 360 == 0) {
    return curr_y;
  }
  if (theta % 360 == 90) {
    return curr_y + 1;
  }
  if (theta % 360 == 180) {
    return curr_y;
  }
  if (theta % 360 == 270) {
    return curr_y - 1;
  }
}
