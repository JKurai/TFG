void setup() {
  Serial.begin(115200);
  pinMode(35, INPUT);
  pinMode(34, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //int aux = digitalRead(35);
  int aux = analogRead(35);
  int aux2 = analogRead(34);
  Serial.print("AUX 1: ");
  Serial.println(aux);
  Serial.print("AUX 2: ");
  Serial.println(aux2);
  delay(500);
}
