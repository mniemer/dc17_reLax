void teensy_led(boolean on) {
  analogWrite(LED, 0);
  if (on)
    digitalWrite(LED, HIGH);
  else
    digitalWrite(LED, LOW);
}

