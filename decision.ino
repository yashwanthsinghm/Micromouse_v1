void decision() {
//  String text = "Entering decision making for " + String(curr_x) + ", " + String(curr_y) + "; The cell cost and theta is " + String(cost[curr_x][curr_y]) + "; " + String(theta);
//  log(text);
  int curr_cell_cost = cost[curr_x][curr_y];
  if (curr_cell_cost == 0) {
    colorPath();
    setColor(curr_x, curr_y, 'b');
    String text = "Number of cells in the path is "+String(counter);
    log(text);
    for(int i=0; i<counter; i++){
      String text = String(path[i])+" = "+String(path[i]%16)+", "+String(path[i]/16);
      log(text);
    }
    log("");
    for(int i=0; i<counter2; i++){
      String text = String(path2[i])+" = "+String(path2[i]%16)+", "+String(path2[i]/16);
      log(text);
    }
    delay(3000);
//    clearAllText();
//    delay(1000);
//    clearAllColor();
//    delay(1000);
    toStart();
    delay(2000);
    toGoal();
//    digitalWrite(PC13, HIGH);
    delay(1000000);
  }
  else if (front_cell_wall(curr_x, curr_y) == 0 && front_cell_cost(curr_x, curr_y) == curr_cell_cost - 1) {
    ff_count = 0;
//    log("No front wall, cost is 1-current cost; moving forward");
    moveForward();
    update_current_cell();
    pathChange(curr_x, curr_y);
//    log("Done moving forward, exiting");
  }
  else if (right_cell_wall(curr_x, curr_y) == 0 && right_cell_cost(curr_x, curr_y) == curr_cell_cost - 1) {
    ff_count = 0;
//    log("No right wall, cost is 1-current cost; turning right and moving forward");
    turnRight();
    theta += 90;
    moveForward();
    update_current_cell();
    pathChange(curr_x, curr_y);
  }
  else if (left_cell_wall(curr_x, curr_y) == 0 && left_cell_cost(curr_x, curr_y) == curr_cell_cost - 1) {
    ff_count = 0;
//    log("No left wall, cost is 1-current cost; turning left and moving forward");
    turnLeft();
    theta += 270;
    moveForward();
    update_current_cell();
    pathChange(curr_x, curr_y);
  }
  else if (left_cell_wall(curr_x, curr_y) != 0 && right_cell_wall(curr_x, curr_y) != 0 && front_cell_wall(curr_x, curr_y) != 0) {
    ff_count = 0;
//    log("Dead end; Taking U-turn");
    turnRight();
    turnRight();
    theta += 180;
    clearColor(curr_x, curr_y);
    counter--;
    flood_fill();
  }
  else {
    if (ff_count == 0) {
      flood_fill();
    }
    else {
      turnRight();
      turnRight();
      theta += 180;
      flood_fill();
    }
  }
//  log("Exiting decision function");
}

void flood_fill() {
  ff_count = 1;
//  String text = "Entering floodfill for cell " + String(curr_x) + ", " + String(curr_y);
//  log(text);
  StackArray <int> stack_x, stack_y;
  int left_c_cost, right_c_cost, front_c_cost, back_c_cost, smallest ;
  stack_x.push(curr_x);
  stack_y.push(curr_y);
  while (!stack_x.isEmpty()) {
    int x = stack_x.pop();
    int y = stack_y.pop();
    if (right_cell_wall(x, y) == 0) {
      right_c_cost =  right_cell_cost(x, y);
      stack_x.push(right_cell_x(x, y));
      stack_y.push(right_cell_y(x, y));
    }
    else {
      right_c_cost = 1000;
    }
    if (back_cell_wall(x, y) == 0) {
      back_c_cost =  back_cell_cost(x, y);
      stack_x.push(back_cell_x(x, y));
      stack_y.push(back_cell_y(x, y));
    }
    else {
      back_c_cost = 1000;
    }
    if (left_cell_wall(x, y) == 0) {
      left_c_cost = left_cell_cost(x, y);
      stack_x.push(left_cell_x(x, y));
      stack_y.push(left_cell_y(x, y));
    }
    else {
      left_c_cost = 1000;
    }
    if (front_cell_wall(x, y) == 0) {
      front_c_cost =  front_cell_cost(x, y);
      stack_x.push(front_cell_x(x, y));
      stack_y.push(front_cell_y(x, y));
    }
    else {
      front_c_cost = 1000;
    }
    smallest = findSmallest(left_c_cost, right_c_cost, front_c_cost, back_c_cost);
    cost[x][y] = smallest + 1;
    setText(x, y, String(cost[x][y]));
    int stackCount = stack_x.count();
    for (int i = 1; i <= stackCount; i++) {
      if (possible_neighbour(stack_x.peek(), stack_y.peek())) {
        stack_x.pop();
        stack_y.pop();
      }
      else {
        break;
      }
    }
  }
  //  log("Exiting floodfill");
  decision();
}

int findSmallest(int a, int b, int c, int d) {
  int smallest = a;
  if (b < smallest) {
    smallest = b;
  }
  if (c < smallest) {
    smallest = c;
  }
  if (d < smallest) {
    smallest = d;
  }
  return smallest;
}

bool possible_neighbour(int x , int y) {
  if (front_cell_wall(x, y) == 0 && cost[x][y] > front_cell_cost(x, y)) {
    return true;
  }
  else if (right_cell_wall(x, y) == 0 && cost[x][y] > right_cell_cost(x, y)) {
    return true;
  }
  else if (back_cell_wall(x, y) == 0 && cost[x][y] > back_cell_cost(x, y)) {
    return true;
  }
  else if (left_cell_wall(x, y) == 0 && cost[x][y] > left_cell_cost(x, y)) {
    return true;
  }
  else {
    return false;
  }
}
