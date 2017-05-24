#define BAUD_RATE 9400

int aI1 = A0;
int aI2 = A2;
int led = 13;
float pos= 0;
float posState = 0;
float vol= 0;
float volState = 0;
float t = 0.001;

float a0;
float b0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(BAUD_RATE);
  
  a0 = exp(-1.0/(t * BAUD_RATE));
  b0 = 1 - a0;
}

void loop() {
  // put your main code here, to run repeatedly:
  pos = (1024-analogRead(aI1))/4;
  posState += b0 * (pos - posState);

  vol = (1024-analogRead(aI2))/4;
  volState += b0 * (vol - volState);

  Serial.write((unsigned char)posState);
  Serial.write((unsigned char)volState);
}
