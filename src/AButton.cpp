// Generic Button Class
// detects up/down, clicks and double-click events
// author: Christophe VG <contact@christophe.vg>

#include "AButton.h"

#include "isr_methods.h"

int AButton::next_handler = 0;

AButton::AButton(int pin) {
  this->pin                             = pin;
  this->active_low                      = false;
  this->interrupt_enabled               = false;
  this->on_up_handler                   = NULL;
  this->on_down_handler                 = NULL;
  this->on_click_handler                = NULL;
  this->on_dbl_click_handler            = NULL;
  this->button_state                    = LOW; // default active high
}

// private function to register this object and instantiate a handler
void AButton::enable_interrupt() {
  if(this->interrupt_enabled) { return; }
  this->interrupt_enabled = true;

  if(this->next_handler > MAX_ISR_METHODS-1) { return; } // TODO error reporting
  // register this
  buttons[this->next_handler] = this;

  // and register the corresponding callback wrapper
  attachInterrupt(digitalPinToInterrupt(this->pin), handlers[this->next_handler], CHANGE);

  // prepare for next handler registration
  this->next_handler++;  
}

AButton* AButton::is_active_low() {
  this->active_low = true;
  this->button_state = HIGH; // TODO assumption this is done before pressing
  return this;
}

AButton* AButton::on_up(button_event_handler handler) {
  this->on_up_handler = handler;
  this->enable_interrupt();
  return this;
}

AButton* AButton::on_down(button_event_handler handler) {
  this->on_down_handler = handler;
  this->enable_interrupt();
  return this;
}

AButton* AButton::on_click(button_event_handler handler) {
  this->on_click_handler = handler;
  this->enable_interrupt();
  return this;
}

AButton* AButton::on_dbl_click(button_event_handler handler) {
  this->on_dbl_click_handler = handler;
  this->enable_interrupt();
  return this;
}

int AButton::get_button_state() {
  this->button_state = digitalRead(this->pin);
  return this->button_state;
}

bool AButton::is_active() {
  return this->active_low && this->button_state == LOW
    || ! this->active_low && this->button_state == HIGH;
}

void AButton::change(void) {
  unsigned long now = millis();
  if( now - this->last_interrupt > this->debounce ) {
    int prev = this->button_state;
    if(prev != this->get_button_state()) {
      // state changed, determine events to trigger
      if( this->button_state == HIGH && ! this->active_low 
        || this->button_state == LOW && this->active_low ) {
        if( this->on_down_handler ) { this->on_down_handler(); }
      } else {
        if( this->on_up_handler ) { this->on_up_handler(); }
        if( this->on_click_handler ) { this->on_click_handler(); }
        if( now - this->last_click < this->dbl_click ) {
          if( this->on_dbl_click_handler ) { this->on_dbl_click_handler(); }          
        }
        this->last_click = now;        
      }
    }
  }
  this->last_interrupt = now;
}
