#ifndef ButtonHelper_h
#define ButtonHelper_h

#include <Arduino.h>
#include <driver/rtc_io.h>

#include "types/Action.h"
#include "types/Device.h"

class ButtonHelper {
   private:
   public:
    ButtonHelper(gpio_num_t gpin);
    gpio_num_t gpin;  // gpio pin
    uint8_t ipin;     // digital interrupt pin
    button_action_t buttonAction;
    void begin();
    void prepareSleep(wakeup_action_e wakeupType);
    bool isPressed();
};

#endif