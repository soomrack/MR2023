void rotateByDegrees(int degrees, bool isRightTurn) {
  int millisecondsToTurn = TIME_REQUIRED_TO_TURN(degrees);
  unsigned long startTime = millis();
  if (isRightTurn) {
    move(1, 0, MAX_ROTATION_SPEED, MIN_ROTATION_SPEED);
  } else {
    move(0, 1, MIN_ROTATION_SPEED, MAX_ROTATION_SPEED);
  }
  while (millis() - startTime < millisecondsToTurn) {
    // ничего не делаем, ждем пока робот поворачивается
  }
  move(1, 1, 0, 0);  // остановка движения
