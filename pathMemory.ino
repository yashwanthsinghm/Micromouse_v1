void pathChange(int curr_x, int curr_y) {
  if (existInPath(curr_y * 16 + curr_x)) {
    int temp = checkCounter(curr_y * 16 + curr_x);
    counter = temp + 1;
  }
  else {
    path[counter] = curr_y * 16 + curr_x;
    counter++;
  }
}

bool existInPath(int num) {
  for (int i = 0; i < counter; i++) {
    if (path[i] == num ) {
      return true;
    }
  }
  return false;
}

int checkCounter(int num) {
  for (int i = 0; i < counter; i++) {
    if (path[i] == num) {
      return i;
    }
  }
}

void colorPath() {
  for (int i = 0; i < counter; i++) {
    setColor(path[i] % 16, path[i] / 16, 'G');
  }
}
