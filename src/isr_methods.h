#ifndef __ISR_METHODS_H
#define __ISR_METHODS_H

// interrupt handlers cannot provide arguments or return values
// we therefore can't have instance methods as interrupt handlers
// solution: predefine a set of available handlers for multiple button instances
// this limits the number of buttons this library can provide support for :-(
// TODO implement this using code generation to hide it, except for a COUNT var

#define MAX_ISR_METHODS 12

AButton* buttons[MAX_ISR_METHODS];

void handler_0()  { buttons[0]->change();  }
void handler_1()  { buttons[1]->change();  }
void handler_2()  { buttons[2]->change();  }

button_event_handler handlers[MAX_ISR_METHODS] = {
  handler_0,
  handler_1,
  handler_2
};

#endif
