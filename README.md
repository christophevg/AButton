# AButton

Yet Another Arduino Button library ;-)

> [!IMPORTANT]  
> This repo has been [archived](https://docs.github.com/en/repositories/archiving-a-github-repository/archiving-repositories#)

> [!WARNING]
> This is mostly a personal experiment. Use at your own risk ;-)

## Installation

This folder should go in your Sketchbook/libraries folder. You can do this
using a symbolic link. E.g. on a Mac:

```bash
$ git clone https://github.com/christophevg/AButon
$ ln -s `pwd`/AButton ~/Documents/Arduino/libraries/
```

## Example

```c
#include <AButton.h>

#define BUTTON_PIN 5

AButton button(BUTTON_PIN);

void setup() {
  Serial.begin(115200);
  button.on_click(&on_click);
}

void on_click() {
  Serial.println("click");
}

void loop() {
  delay(10);
}
```
