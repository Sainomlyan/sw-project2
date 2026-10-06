
#define PIN_LED 9
#define PIN_TRIG 12
#define PIN_ECHO 13

#define SND_VEL 346.0     
#define INTERVAL 25       
#define PULSE_BYPASS 1    

unsigned long last_sampling_time = 0;

void setup() {
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  digitalWrite(PIN_TRIG, LOW);
  
  Serial.begin(57600);
}

void loop() {
  if (millis() - last_sampling_time < INTERVAL) {
    return;
  }
  last_sampling_time = millis();

  float distance = measure_distance();

  int pwm_value = 255;

  if (distance <= 100.0 || distance >= 300.0) {
    pwm_value = 255;
  } 
  else if (distance < 200.0) {
    pwm_value = (int)(255.0 - (distance - 100.0) * 2.55);
  } 
  else {
    pwm_value = (int)((distance - 200.0) * 2.55);
  }
  if (pwm_value < 0) pwm_value = 0;
  if (pwm_value > 255) pwm_value = 255;

  analogWrite(PIN_LED, pwm_value);
  Serial.print("Min:100,distance:");
  Serial.print(distance);
  Serial.print(",Max:300,PWM:");
  Serial.println(pwm_value);
}

float measure_distance() {
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
 
  float duration = pulseIn(PIN_ECHO, HIGH, 30000); 
  float distance = duration * 0.173;
  
  return distance;
}
