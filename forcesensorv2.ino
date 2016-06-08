/**
* By Martha Hipley
* Pressure Sensor Detection Code 
* Converted johnny-five/js
*/


int sensorPin = 0;  
int redPin = 11;  
int greenPin = 10;  
int bluePin = 9;  

int sensorValue = 0;  

int motor = 3;

void setup() {
  pinMode(motor,OUTPUT) ;
  Serial.begin(9600);
}

int sensorScaled = 0;

void loop() {
  // read the value from the sensor
  sensorValue = analogRead(sensorPin);
 
  sensorScaled = sensorValue / 1023.0 * 255.0; 
  float brightness=sensorScaled;
  brightness = map(sensorScaled, 0, 1023, 0, 255);
  
  //float hue =  sensorScaled * 1.5 / 200;
  float hue = -(1200 - sensorValue) * 1.5 / 2400;
  int rgb[3];
  hslToRgb(hue, 1.0, 0.5, rgb);

  Serial.println(sensorScaled);

int r = rgb[0];
   r = map(r, 0, 1023, 0, brightness);
int g = rgb[1];
   g = map(g, 0, 1023, 0, brightness);
int b = rgb[2];
   b = map(b, 0, 1023, 0, brightness);

  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);

  analogWrite(motor, sensorScaled) ;
}

void hslToRgb(float h, int s, float l, int* rgb){
  float r, g, b;
  
  
  if(s == 0.0){
      r = g = b = l; // achromatic
  }else{
      float q = l < 0.5 ? l * (1.0 + s) : l + s - l * s;
      float p = 2.0 * l - q;
      r = hue2rgb(p, q, h + 1.0/3.0);
      g = hue2rgb(p, q, h);
      b = hue2rgb(p, q, h - 1.0/3.0);
  }
  rgb[0] = (float)r * 255.0;
  rgb[1] = (float)g * 255.0;
  rgb[2] = (float)b * 255.0;
}

float hue2rgb(float p, float q, float t){
  if(t < 0.0) t += 1.0;
  if(t > 1.0) t -= 1;
  if(t < 1.0/6.0) return p + (q - p) * 6.0 * t;
  if(t < 1.0/2.0) return q;
  if(t < 2.0/3.0) return p + (q - p) * (2.0/3.0 - t) * 6.0;
  return p;
}

