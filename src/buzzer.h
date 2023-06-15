#include <esp32-hal-timer.h>

//needs change
//make sure to know the hardware timer pins
#define buzzerPin 99

hw_timer_t *buzzerTimer = NULL;

void buzzerCallback() {
  noTone(buzzerPin);
}

void buzzer() {
  tone(buzzerPin, 1000);
//interrupt hardware timer to stop buzzing without stoping code
//100% not chatgpt
  if (buzzerTimer == NULL) {
    buzzerTimer = timerBegin(0, 80, true); // Use timer 0 with prescaler 80 and counting up
    timerAttachInterrupt(buzzerTimer, &buzzerCallback, true); // Attach the callback function
    timerAlarmWrite(buzzerTimer, 100000, false); // Set the alarm for 100ms
    timerAlarmEnable(buzzerTimer); // Enable the timer alarm
  } else {
    timerRestart(buzzerTimer); // Restart the timer
  }
}
