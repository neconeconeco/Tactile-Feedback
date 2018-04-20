//利用DigitalWrite生成方波

// 可调参数
int output_port = 3;  //波形输出口
double frequency = 180;  //波频率

double time_lap; //波形周期

void setup() {
  // put your setup code here, to run once:
  pinMode(output_port, OUTPUT);
  
  time_lap = 1000/frequency;
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(output_port, HIGH);
  delay(time_lap/2);
  digitalWrite(output_port, LOW);
  delay(time_lap/2);
}
