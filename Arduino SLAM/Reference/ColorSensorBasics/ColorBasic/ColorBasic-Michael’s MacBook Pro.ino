

// COLOR SENSOR
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8


void setup(){

 //set pins S0-S3 to output and sensorOut to input
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  //Set frequency scaling to 100%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,HIGH);

//  //set frequency scaling to 20%
//  digitalWrite(S0,HIGH);
//  digitalWrite(S1,LOW);
//
//  //Set frequency scaling to 2%
//  digitalWrite(S0,LOW);
//  digitalWrite(S1,HIGH);
//
//  //turn off sensor:
//  digitalWrite(S0,LOW);
//  digitalWrite(S1,LOW);

  Serial.begin(115200);
  
}


void loop(){

  //read read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  int r = pulseIn(sensorOut,HIGH);

  //read green
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  int g = pulseIn(sensorOut,HIGH);

  //read blue
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  int b = pulseIn(sensorOut,HIGH);

  //read gray level
  digitalWrite(S2,HIGH);
  digitalWrite(S3,LOW);
  int k = pulseIn(sensorOut,HIGH);

  Serial.print(r);
  Serial.print(" ");
  Serial.print(g);
  Serial.print(" ");
  Serial.print(b);
  Serial.print(" ");
  Serial.println(k);
  delay(300);
  
}




