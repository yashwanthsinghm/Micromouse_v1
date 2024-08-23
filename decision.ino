void decision() {
  int curr_cell_cost = cost[curr_x][curr_y];
  if (curr_cell_cost == 0) {
    delay(3000);
 
    copyToEEPROM();
    botSpeed = 225;
    for (int i = 0; i < counter; i++) {
      delay(100);
      //WebSerial.printf("%d\n", path[i]);
    }

  }
  else if (front_cell_wall(curr_x, curr_y) == 0 && front_cell_cost(curr_x, curr_y) == curr_cell_cost - 1) {
//    WebSerial.printf("In front move decision\n");
    ff_count = 0;
    moveForwardM(1);
    update_current_cell();
    pathChange(curr_x, curr_y);
  }
  else if (right_cell_wall(curr_x, curr_y) == 0 && right_cell_cost(curr_x, curr_y) == curr_cell_cost - 1) {
   // WebSerial.printf("In right turn decision\n");
    ff_count = 0;
    turnRightM();
    theta += 90;
    moveForwardM(1);
    update_current_cell();
    pathChange(curr_x, curr_y);
  }
  else if (left_cell_wall(curr_x, curr_y) == 0 && left_cell_cost(curr_x, curr_y) == curr_cell_cost - 1) {
//    WebSerial.printf("In left turn decision\n");
    ff_count = 0;
    turnLeftM();
    theta += 270;
    moveForwardM(1);
    update_current_cell();
    pathChange(curr_x, curr_y);
  }
  else if (left_cell_wall(curr_x, curr_y) != 0 && right_cell_wall(curr_x, curr_y) != 0 && front_cell_wall(curr_x, curr_y) != 0) {
//    WebSerial.printf("In 180 turn decision\n");
    ff_count = 0;
    turn180M();
    theta += 180;
    //delay(300);
    counter--;
    flood_fill();
  }
  else {
    if (ff_count == 0) {
      flood_fill();
    }
    else {
      turn180M();
      theta += 180;
      //delay(300);
      flood_fill();
    }
  }
}

void flood_fill() {
  ff_count = 1;
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
