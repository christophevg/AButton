// this example illustrates the basic usage of the library
// detected events are reported to the console
// two buttons are defined to show that the internal interrupt hack works ;-)

#include <AButton.h>

#define BUTTON_A_PIN  4
#define BUTTON_D_PIN  0

AButton button_a(BUTTON_A_PIN);
AButton button_d(BUTTON_D_PIN);

void setup() {
  Serial.begin(115200);
  
  button_a.on_click     (&on_click_a)
         ->on_dbl_click (&on_dbl_click_a);

  button_d.is_active_low()
         ->on_up        (&on_up_d)
         ->on_down      (&on_down_d)
         ->on_click     (&on_click_d)
         ->on_dbl_click (&on_dbl_click_d);
}

// NOTE: you shouldn't do a lot in these event handlers, just set a state and
//       handle the state change in your loop(), since you're in a ISR ;-)

void on_click_a() {
  Serial.println("A: click");
}

void on_dbl_click_a() {
  Serial.println("A: double click");
}

void on_up_d() {
  Serial.println("D: up");
}

void on_down_d() {
  Serial.println("D: down");
}

void on_click_d() {
  Serial.println("D: click");
}

void on_dbl_click_d() {
  Serial.println("D: double click");
}

void loop() {
  delay(50); // kill some time ;-)
}
