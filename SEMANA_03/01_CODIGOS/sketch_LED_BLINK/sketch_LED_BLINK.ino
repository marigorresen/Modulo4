// C++ code
// Pisca Pisca duplo
void setup()
{
  pinMode(32, OUTPUT);
}

void loop()
{
  digitalWrite(32, 1);
  delay(500); 
  digitalWrite(32, 0);
  delay(500); 
}