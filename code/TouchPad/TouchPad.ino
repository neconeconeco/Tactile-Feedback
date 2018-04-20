#include <SPI.h>
#include <Wire.h>
#include <MsTimer2.h>   //定时中断的头文件

#define pwmOut 4
#define freqPot 21
#define LED 13
#define SINE 0
#define SQUARE 1
#define SAW_DESC 2
#define SAW_ASC 3
#define NOISE 4

#define waveMax 4
#define waveMin 0

float minPhO = 0.016 * 1000.0; // 0.0125 is too low for some people to feel, trying 0.016 now
float maxPhO = 0.4 * 1000.0;
float phaseOffset = 10.0; //just an initial condition, this used to be 0.05

float minPhOStep = 0.02 * 1000.0;
float wavePhase = 0.01;
float twopi = 3.14159 * 2;

float minDuty = 0.3;
float maxDuty = 0.95;
float dutyCycle = 0.3;

float minAmpl = 0.0;
float maxAmpl = 2000.0;

float DACamplitude = 2000.0;
int waveType = 1; // sine, square (default), saw descending, saw ascending, noise

int countFrame = 0;  //统计每秒的帧数

void resetCountFrame(){
  onVariableChange();
  countFrame = 0;
}

void setup() {
  // 显示初始化
  initDisplay();
  displayVariables();

  // fps初始化 !!!注意!!!在中断的时候会影响DAC输出
//  MsTimer2::set(1000, resetCountFrame);        // 中断设置函数，每1000ms进入一次中断
//  MsTimer2::start();                //开始计时

  analogWriteResolution(12);
  analogWriteFrequency(pwmOut, 375000);
  pinMode(pwmOut, OUTPUT);
}

void loop() {
  
  analogWrite(pwmOut, int(4096 * dutyCycle));

  // count frame per second
  countFrame += 1;
  
  // change parameter according to freqPot voltage change
//  int freqVol = analogRead(freqPot);
//  float tempPhaseOffset = floatmap((float)freqVol, 0, 1023, minPhO, maxPhO);
//  float os = abs(tempPhaseOffset-phaseOffset);
//  if (os<minPhOStep) {
//    ;
//  }else {
//    phaseOffset = tempPhaseOffset;
//    onVariableChange();
//  }

  // generate wave
  float DACval = 0;
  wavePhase = wavePhase + (phaseOffset / 1000.0);
  if (wavePhase >= twopi) {
    wavePhase = 0;
  }

  switch (waveType) {
    case SINE:
      DACval = sin(wavePhase) * DACamplitude + 2050.0;
      // 2050.0 is DC offset?
      break;
    case SQUARE:
      // if phase > pi then 1 else 0
      (wavePhase > twopi / 2) ? (DACval = (DACamplitude / maxAmpl) * 4095.0) : (DACval = 0.0);
      break;
    case SAW_DESC:
      // phase itself is linearly ramping
      DACval = floatmap(wavePhase, 0, twopi, 0.0, 1.0) * (DACamplitude / maxAmpl) * 4095.0;
      break;
    case SAW_ASC:
      // phase itself is linearly ramping
      DACval = floatmap(wavePhase, 0, twopi, 1.0, 0.0) * (DACamplitude / maxAmpl) * 4095.0;
      break;
    case NOISE:
      (random(0, 9) > 4.5) ? (DACval = (DACamplitude / maxAmpl) * 4095.0) : (DACval = 0.0);
      break;
    default:
      DACval = sin(wavePhase) * DACamplitude + 2050.0;
      break;
  }

  DACval = 4095.0 - DACval;
  analogWrite(A14, (int)DACval);
}

// native map func uses int math
float floatmap(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
