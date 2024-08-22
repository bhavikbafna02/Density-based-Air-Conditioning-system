#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// OLED display dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

// Define the OLED reset pin (for some displays, this can be left as -1 if not used)
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// DHT11 sensor setup
#define DHTPIN 2     // Pin where the DHT11 is connected
#define DHTTYPE DHT11 // DHT 11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Initialize the serial communication
  Serial.begin(9600);

  // Initialize the DHT sensor
  dht.begin();

  // Initialize the OLED display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for most 128x32 displays
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Clear the buffer
  display.clearDisplay();
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
}

void loop() {
  // Read temperature as Celsius
  float temp = dht.readTemperature();
  // Read humidity as percentage
  float humidity = dht.readHumidity();

  // Check if any reads failed and exit early (to try again).
  if (isnan(temp) || isnan(humidity)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Print temperature and humidity to Serial Monitor
  Serial.print(F("Temperature: "));
  Serial.print(temp);
  Serial.print(F("°C "));
  Serial.print(F("Humidity: "));
  Serial.print(humidity);
  Serial.println(F("%"));

  // Clear the display
  display.clearDisplay();

  // Display temperature on the OLED
  display.setCursor(0,0);
  display.print(F("Temp: "));
  display.print(temp);
  display.print(F(" C"));

  // Display humidity on the OLED
  display.setCursor(0,16);
  display.print(F("Humidity: "));
  display.print(humidity);
  display.print(F(" %"));

  // Update the display with the new data
  display.display();

  // Wait a bit before updating again
  delay(2000); // Update every 2 seconds
}
