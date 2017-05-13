void teensy_led(boolean on) {
  analogWrite(LED, 0);
  if (on)
    digitalWrite(LED, HIGH);
}

int generate_direction(int bad1, int bad2, int bad3) {
  while (1) {
    int dir = random(20, 24);
    if (dir != bad1 && dir != bad2 && dir != bad3)
      return dir;
  }
}



