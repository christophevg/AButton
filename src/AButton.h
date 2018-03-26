// Generic Button Class
// detects clicks, double-clicks and press-and-hold
// inspired by https://github.com/mathertel/OneButton
// implemented using interrupts
// author: Christophe VG <contact@christophe.vg>

#ifndef __ABUTTON_H
#define __ABUTTON_H

#include "Arduino.h"

// generic callback handler for button events
typedef void (*button_event_handler)(void);

class AButton {
  public:
    AButton(int pin);

    AButton* is_active_low();

    AButton* on_up(button_event_handler handler);
    AButton* on_down(button_event_handler handler);
    AButton* on_click(button_event_handler handler);
    AButton* on_dbl_click(button_event_handler handler);

    // this needs to be public to allow the interrupt hack construction to work
    // don't use it - it won't hurt either - probably ;-)
    void change(void);

  private:
    // contructor-based configuration
    int  pin;

    bool active_low = false;
    int  button_state;
    int  get_button_state();
    bool is_active();

    // event handlers
    button_event_handler on_up_handler;
    button_event_handler on_down_handler;
    button_event_handler on_click_handler;
    button_event_handler on_dbl_click_handler;

    // internal state
    bool          interrupt_enabled;
    unsigned long last_interrupt = 0;
    unsigned long last_click     = 0;

    // counter into callback hack table of predefined callbacks
    static int next_handler;
    // function to setup the ISR when needed, registers this in callback hack
    void enable_interrupt();

  protected:
    // minimak number of millis between handled interrupts
    int  debounce   = 50;
    // maximal number of millis between clicks to be considered double clicks
    int  dbl_click  = 500; 
};

#endif
