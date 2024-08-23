void toGoal() {
  int distance = 0, dir = 1; // dir = 1 - (+)ve y; dir = 2 - (+)ve x; dir = 3 - (-)ve y; dir = 4 - (-)ve x;
  for (int i = 1; i <= counter; i++) {
    if (dir == 1) {
      if (path[i] % 16 == path[i - 1] % 16) {
        distance += 1;
      }
      else {
        forward(distance);
        distance = 1;
        if (path[i] == path[i - 1] + 1) {
          dir = 2;
          turnRightM();
        }
        else {
          dir = 4;
          turnLeftM();
        }
      }
    }
    else if (dir == 2) {
      if (path[i] == path[i - 1] + 1) {
        distance += 1;
      }
      else {
        forward(distance);
        distance = 1;
        if (path[i] == path[i - 1] + 16) {
          dir = 1;
          turnLeftM();
        }
        else {
          dir = 3;
          turnRightM();
        }
      }
    }
    else if (dir == 3) {
      if (path[i] % 16 == path[i - 1] % 16) {
        distance += 1;
      }
      else {
        forward(distance);
        distance = 1;
        if (path[i] == path[i - 1] + 1) {
          dir = 2;
          turnLeftM();
        }
        else {
          dir = 4;
          turnRightM();
        }
      }
    }
    else {
      if (path[i] == path[i - 1] - 1) {
        distance += 1;
      }
      else {
        forward(distance);
        distance = 1;
        if (path[i] == path[i - 1] + 16) {
          dir = 1;
          turnRightM();
        }
        else {
          dir = 3;
          turnLeftM();
        }
      }
    }
  }
}

void toStart() {
  turn180M();
  theta += 180;
  int distance = 0, dir = ((theta % 360) / 90 + 1); // dir = 1 - (+)ve y; dir = 2 - (+)ve x; dir = 3 - (-)ve y; dir = 4 - (-)ve x;
  for (int i = counter - 2; i >= 0; i--) {
    if (dir == 1) {
      if (path[i] % 16 == path[i + 1] % 16) {
        distance += 1;
      }
      else {
        forward(distance);
        distance = 1;
        if (path[i] == path[i + 1] + 1) {
          dir = 2;
          turnRightM();
        }
        else {
          dir = 4;
          turnLeftM();
        }
      }
    }
    else if (dir == 2) {
      if (path[i] == path[i + 1] + 1) {
        distance += 1;
      }
      else {
        forward(distance);
        distance = 1;
        if (path[i] == path[i + 1] + 16) {
          dir = 1;
          turnLeftM();
        }
        else {
          dir = 3;
          turnRightM();
        }
      }
    }
    else if (dir == 3) {
      if (path[i] % 16 == path[i + 1] % 16) {
        distance += 1;
      }
      else {
        forward(distance);
        distance = 1;
        if (path[i] == path[i + 1] + 1) {
          dir = 2;
          turnLeftM();
        }
        else {
          dir = 4;
          turnRightM();
        }
      }
    }
    else {
      if (path[i] == path[i + 1] - 1) {
        distance += 1;
      }
      else {
        forward(distance);
        distance = 1;
        if (path[i] == path[i + 1] + 16) {
          dir = 1;
          turnRightM();
        }
        else {
          dir = 3;
          turnLeftM();
        }
      }
    }
  }
  forward(distance);
  turn180M();
  theta += 180;
}

void forward( int distance) {
  moveForwardM(distance);
}
