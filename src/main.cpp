
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#include <Arduino.h>
#include <FastLED.h>
#include <Button2.h>

#define LED_PIN GPIO_NUM_26
#define LED_COUNT 60
#define MAX_BRIGHTNESS 254
#define BRIGHTNESS_INC 20
Button2 onOffBtn;

Button2 upBtn;

Button2 downBtn;

void click(Button2 &btn);

CRGB leds[LED_COUNT];
int brightness = MAX_BRIGHTNESS;
bool isOn = false;
const char *ssid = "zzb22-x";
const char *password = "";
const char *hostname = "readinglight.local";

byte capStateHandler1()
{
    return touchRead(GPIO_NUM_13) < onOffBtn.getDebounceTime() ? LOW : HIGH;
}
byte capStateHandler2()
{
    return touchRead(GPIO_NUM_12) < upBtn.getDebounceTime() ? LOW : HIGH;
}
byte capStateHandler3()
{
    return touchRead(GPIO_NUM_14) < downBtn.getDebounceTime() ? LOW : HIGH;
}

void click(Button2 &btn)
{
    Serial.println(String(btn.getID()) + " click\n");
}

void onOffBtnClick(Button2 &btn)
{
    Serial.println(String(btn.getID()) + " onOffBtnClick\n");
    isOn = !isOn;
    if (isOn)
    {
        for (int i = 0; i < LED_COUNT; i++)
        {
            leds[i] = CRGB::White;
        }
    }
    else
    {
        FastLED.clear();
    }
    FastLED.show();
}

void upBtnClick(Button2 &btn)
{
    Serial.println(String(btn.getID()) + " upBtnClick\n");
    if (brightness < MAX_BRIGHTNESS)
        brightness += BRIGHTNESS_INC;
    FastLED.setBrightness(brightness);
    FastLED.show();
}

void downBtnClick(Button2 &btn)
{
    Serial.println(String(btn.getID()) + " downBtnClick\n");
    if (brightness > 0)
        brightness -= BRIGHTNESS_INC;
    FastLED.setBrightness(brightness);
    FastLED.show();
}

void setup()
{

    Serial.begin(115200);
    Serial.println("Booting");
    WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);
    WiFi.setHostname(hostname);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
        Serial.println("Connection Failed! Rebooting...");
        delay(5000);
        ESP.restart();
    }
    while (!MDNS.begin(hostname))
    {
        Serial.println("Error starting MDNS");
        return ;
    }
    

    ArduinoOTA
        .onStart([]()
                 {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      Serial.println("Start updating " + type); })
        .onEnd([]()
               { Serial.println("\nEnd"); })
        .onProgress([](unsigned int progress, unsigned int total)
                    { Serial.printf("Progress: %u%%\r", (progress / (total / 100))); })
        .onError([](ota_error_t error)
                 {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed"); });

    ArduinoOTA.begin();

    Serial.println("Ready");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    delay(1000);
    Serial.println("Initialising ...");
    //FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, LED_COUNT);
    FastLED.setBrightness(brightness);

    // pinMode(BUTTON_PIN1, INPUT_PULLUP);
    // pinMode(BUTTON_PIN2, INPUT_PULLUP);
    // pinMode(BUTTON_PIN3, INPUT_PULLUP);
    onOffBtn.setDebounceTime(35);
    onOffBtn.setButtonStateFunction(capStateHandler1);
    onOffBtn.setPressedHandler(onOffBtnClick);
    onOffBtn.begin(GPIO_NUM_13);

    upBtn.setDebounceTime(35);
    upBtn.setButtonStateFunction(capStateHandler2);
    upBtn.setPressedHandler(upBtnClick);
    upBtn.begin(GPIO_NUM_12);

    downBtn.setDebounceTime(35);
    downBtn.setButtonStateFunction(capStateHandler3);
    downBtn.setPressedHandler(downBtnClick);
    downBtn.begin(GPIO_NUM_14);
}

void loop()
{
    ArduinoOTA.handle();

    onOffBtn.loop();
    upBtn.loop();
    downBtn.loop();
}
