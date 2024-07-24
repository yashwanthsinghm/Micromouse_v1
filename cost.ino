void set_cost() {

  for (x = 1; x <= n; x++) {
    for (y = 1; y <= n; y++) {
      if (((x - hx) <= 0) && ((y - hy) <= 0)) {
        cost[x - 1][y - 1] = (n - x - y + r - dev_y + dev_x);
      }
      else if (((x - hx) <= 0) && ((y - hy) > 0)) {
        cost[x - 1][y - 1] = (y - x - 1 + r - dev_x - dev_y);
      }
      else if (((x - hx) > 0) && ((y - hy) <= 0)) {
        cost[x - 1][y - 1] = (x - y - 1 + r + dev_x + dev_y);
      }
      else {
        cost[x - 1][y - 1] = (x + y - n - 2 + r - dev_x + dev_y);
      }
      setText(x - 1, y - 1, String(cost[x - 1][y - 1]));
    }
  }
}

int front_cell_cost(int curr_x, int curr_y) {
  if (theta % 360 == 0) {
    return cost[curr_x][curr_y + 1];
  }
  if (theta % 360 == 90) {
    return cost[curr_x + 1][curr_y];
  }
  if (theta % 360 == 180) {
    return cost[curr_x][curr_y - 1];
  }
  if (theta % 360 == 270) {
    return cost[curr_x - 1][curr_y];
  }
}

int back_cell_cost(int curr_x, int curr_y) {
  if (theta % 360 == 0) {
    return cost[curr_x][curr_y - 1];
  }
  if (theta % 360 == 90) {
    return cost[curr_x - 1][curr_y];
  }
  if (theta % 360 == 180) {
    return cost[curr_x][curr_y + 1];
  }
  if (theta % 360 == 270) {
    return cost[curr_x + 1][curr_y];
  }
}

int right_cell_cost(int curr_x, int curr_y) {
  if (theta % 360 == 0) {
    return cost[curr_x + 1][curr_y];
  }
  if (theta % 360 == 90) {
    return cost[curr_x][curr_y - 1];
  }
  if (theta % 360 == 180) {
    return cost[curr_x - 1][curr_y];
  }
  if (theta % 360 == 270) {
    return cost[curr_x][curr_y + 1];
  }
}

int left_cell_cost(int curr_x, int curr_y) {
  if (theta % 360 == 0) {
    return cost[curr_x - 1][curr_y];
  }
  if (theta % 360 == 90) {
    return cost[curr_x][curr_y + 1];
  }
  if (theta % 360 == 180) {
    return cost[curr_x + 1][curr_y];
  }
  if (theta % 360 == 270) {
    return cost[curr_x][curr_y - 1];
  }
}
