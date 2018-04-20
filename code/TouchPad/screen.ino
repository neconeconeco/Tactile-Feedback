#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// If using software SPI (the default case):
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

void initDisplay(void){
  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC);
  // init done
  
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(2000);

  // Clear the buffer.
  display.clearDisplay();
}

void displayVariables(void){
  display.setTextSize(1);
  display.setTextColor(WHITE);
  // PHO
  display.setCursor(0,0);
  display.println("PHO:");
  display.setCursor(30,0);
  display.println(phaseOffset);
  // AMP
  display.setCursor(0,10);
  display.println("AMP:");
  display.setCursor(30,10);
  display.println(DACamplitude);
  // WAVE
  display.setCursor(0,20);
  display.println("WAVE:");
  display.setCursor(30,20);
  switch (waveType) {
    case SINE:
      display.println("SINE");
      break;
    case SQUARE:
      display.println("SQUARE");
      break;
    case SAW_DESC:
      display.println("SAW_DESC");
      break;
    case SAW_ASC:
      display.println("SAW_ASC");
      break;
    case NOISE:
      display.println("NOISE");
      break;
    default:
      display.println("SINE");
      break;
  }
  // DUTY
  display.setCursor(0,30);
  display.println("DUTY:");
  display.setCursor(30,30);
  display.println(dutyCycle);
  //FPS
  display.setCursor(0,40);
  display.println("FPS:");
  display.setCursor(30,40);
  display.println(countFrame);
  //FREQ
  display.setCursor(0,50);
  display.println("FREQ:");
  display.setCursor(30,50);
  display.println(countFrame*phaseOffset/twopi/1000);

  display.display();
}

void onVariableChange(void){
  display.clearDisplay();
  displayVariables();
}

