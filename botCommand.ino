void toGoal() {
  int distance = 0, dir = 1; // dir = 1 - (+)ve y; dir = 2 - (+)ve x; dir = 3 - (-)ve y; dir = 4 - (-)ve x;
  for (int i = 1; i <= counter; i++) {
    if (dir == 1) {
      if (path[i] % 16 == path[i - 1] % 16) {
        distance += 1;
      }
      else {
        //        String text = "Move forward by " + String(distance) + " units.";
        //        log(text);
        forward(distance);
        distance = 1;
        if (path[i] == path[i - 1] + 1) {
          dir = 2;
          //          log("Turn right");
          turnRight();
        }
        else {
          dir = 4;
          //          log("Turn left");
          turnLeft();
        }
      }
    }
    else if (dir == 2) {
      if (path[i] == path[i - 1] + 1) {
        distance += 1;
      }
      else {
        //        String text = "Move forward by " + String(distance) + " units.";
        //        log(text);
        forward(distance);
        distance = 1;
        if (path[i] == path[i - 1] + 16) {
          dir = 1;
          //          log("Turn left");
          turnLeft();
        }
        else {
          dir = 3;
          //          log("Turn right");
          turnRight();
        }
      }
    }
    else if (dir == 3) {
      if (path[i] % 16 == path[i - 1] % 16) {
        distance += 1;
      }
      else {
        //        String text = "Move forward by " + String(distance) + " units.";
        //        log(text);
        forward(distance);
        distance = 1;
        if (path[i] == path[i - 1] + 1) {
          dir = 2;
          //          log("Turn left");
          turnLeft();
        }
        else {
          dir = 4;
          //          log("Turn right");
          turnRight();
        }
      }
    }
    else {
      if (path[i] == path[i - 1] - 1) {
        distance += 1;
      }
      else {
        //        String text = "Move forward by " + String(distance) + " units.";
        //        log(text);
        forward(distance);
        distance = 1;
        if (path[i] == path[i - 1] + 16) {
          dir = 1;
          //          log("Turn right");
          turnRight();
        }
        else {
          dir = 3;
          //          log("Turn left");
          turnLeft();
        }
      }
    }
  }
}

void toStart() {
  turnRight();
  turnRight();
  theta += 180;
  int distance = 0, dir = ((theta % 360) / 90 + 1); // dir = 1 - (+)ve y; dir = 2 - (+)ve x; dir = 3 - (-)ve y; dir = 4 - (-)ve x;
  for (int i = counter - 2; i >= 0; i--) {
    if (dir == 1) {
      if (path[i] % 16 == path[i + 1] % 16) {
        distance += 1;
      }
      else {
        //        String text = "Move forward by " + String(distance) + " units.";
        //        log(text);
        forward(distance);
        distance = 1;
        if (path[i] == path[i + 1] + 1) {
          dir = 2;
          //          log("Turn right");
          turnRight();
        }
        else {
          dir = 4;
          //          log("Turn left");
          turnLeft();
        }
      }
    }
    else if (dir == 2) {
      if (path[i] == path[i + 1] + 1) {
        distance += 1;
      }
      else {
        //        String text = "Move forward by " + String(distance) + " units.";
        //        log(text);
        forward(distance);
        distance = 1;
        if (path[i] == path[i + 1] + 16) {
          dir = 1;
          //          log("Turn left");
          turnLeft();
        }
        else {
          dir = 3;
          //          log("Turn right");
          turnRight();
        }
      }
    }
    else if (dir == 3) {
      if (path[i] % 16 == path[i + 1] % 16) {
        distance += 1;
      }
      else {
        //        String text = "Move forward by " + String(distance) + " units.";
        //        log(text);
        forward(distance);
        distance = 1;
        if (path[i] == path[i + 1] + 1) {
          dir = 2;
          //          log("Turn left");
          turnLeft();
        }
        else {
          dir = 4;
          //          log("Turn right");
          turnRight();
        }
      }
    }
    else {
      if (path[i] == path[i + 1] - 1) {
        distance += 1;
      }
      else {
        //        String text = "Move forward by " + String(distance) + " units.";
        //        log(text);
        forward(distance);
        distance = 1;
        if (path[i] == path[i + 1] + 16) {
          dir = 1;
          //          log("Turn right");
          turnRight();
        }
        else {
          dir = 3;
          //          log("Turn left");
          turnLeft();
        }
      }
    }
  }
  //  String text = "Move forward by " + String(distance) + " units.";
  //  log(text);
  forward(distance);
  turnRight();
  turnRight();
  theta += 180;
}

void forward( int distance) {
  for (int i = 1; i <= distance; i++) {
    moveForward();
  }
}
