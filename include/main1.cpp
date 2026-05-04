// #include <Arduino.h>
//
// // ================= CONFIGURATION =================
// const int PIN_VIBRATOR = 1;
// const int PIN_LED_BLUE = 6;
// const int PIN_LED_RED  = 8;
// const int PIN_BUZZER   = 10;
//
// const int VIB_PWM_FREQ = 5000;
// const int VIB_MAX_INTENSITY = 120;  // Safe for coin motors
// const int RAMP_MS = 3;
// const int BUZZ_TONE_HZ = 2500;
// const int VIB_CHANNEL = 0;
//
// int currentVibIntensity = 0;
//
// void setup() {
//   Serial.begin(115200);
//   delay(500);
//   Serial.println("ESP32-C3 Alert System Ready.");
//
//   pinMode(PIN_LED_BLUE, OUTPUT);
//   pinMode(PIN_LED_RED, OUTPUT);
//   digitalWrite(PIN_LED_BLUE, LOW);
//   digitalWrite(PIN_LED_RED, LOW);
//
//   pinMode(PIN_BUZZER, OUTPUT);
//   digitalWrite(PIN_BUZZER, LOW);
//
//   ledcSetup(VIB_CHANNEL, VIB_PWM_FREQ, 8);
//   ledcAttachPin(PIN_VIBRATOR, VIB_CHANNEL);
//   ledcWrite(VIB_CHANNEL, 0);
//
//   delay(1000);
// }
//
// // Smooth vibration ramp
// void setVibration(int target) {
//   if (target > currentVibIntensity) {
//     for (int i = currentVibIntensity; i <= target; i++) {
//       ledcWrite(VIB_CHANNEL, i);
//       currentVibIntensity = i;
//       delay(RAMP_MS);
//     }
//   } else if (target < currentVibIntensity) {
//     for (int i = currentVibIntensity; i >= target; i--) {
//       ledcWrite(VIB_CHANNEL, i);
//       currentVibIntensity = i;
//       delay(RAMP_MS);
//     }
//   }
// }
//
// // SHORT ALERT: Vibrate → Buzzer → LED stays ON throughout
// void alertShort() {
//   digitalWrite(PIN_LED_BLUE, HIGH);
//
//   // 1. Vibrate
//   setVibration(VIB_MAX_INTENSITY);
//   delay(300);
//   setVibration(0);
//   delay(50); // Brief pause to avoid mechanical/electrical overlap
//
//   // 2. Buzz
//   tone(PIN_BUZZER, BUZZ_TONE_HZ, 300);
//   delay(300);
//   noTone(PIN_BUZZER);
//
//   digitalWrite(PIN_LED_BLUE, LOW);
// }
//
// // LONG ALERT: Vibrate → Buzzer Pattern → LED stays ON throughout
// void alertLong() {
//   digitalWrite(PIN_LED_RED, HIGH);
//
//   // 1. Vibrate
//   setVibration(VIB_MAX_INTENSITY);
//   delay(600);
//   setVibration(0);
//   delay(50);
//
//   // 2. Buzz pattern (long + short)
//   tone(PIN_BUZZER, BUZZ_TONE_HZ, 800);
//   delay(800);
//   noTone(PIN_BUZZER);
//   delay(50);
//
//   tone(PIN_BUZZER, BUZZ_TONE_HZ, 400);
//   delay(400);
//   noTone(PIN_BUZZER);
//
//   digitalWrite(PIN_LED_RED, LOW);
// }
//
// void loop() {
//   alertShort();
//   delay(2000);
//   alertLong();
//   delay(2000);
// }