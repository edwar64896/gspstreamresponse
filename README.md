# gspstreamresponse

## Introduction

gspstreamresponse is a simple call-back based system for managing serial or stream based events and responding to them.

## How to Use it.

To use gspstreamresponse, you first declare one or more instances of gspstreamrepsonse with the required parameters:

1. "Header" string of two characters. If the incoming stream matches these two characters identically, it will proceed. Otherwise, they will be ignored.
2. Number of characters to grab. If the "header" string has been matched, then this amount of characters will be grabbed from the stream and passed on to the callback function
3. Callback function name, which must conform to the following pattern:
```
void szCallback(const char * szInput) {
   \\ do something with szInput
}
```

You can also do the "lambda" thing:

```
gspStreamResponse sr2_b("=b",4,[](const char * szInput){
  Serial.print("as a lambda function");
  Serial.println(szInput);
});
```

## example
```
#include <Arduino.h>
#include <gspstreamresponse.h>

void doSomethingWithA(const char* szInput) {
  Serial.print("Got something:");
  Serial.println(szInput);
}

gspStreamResponse sr1_a("=a",4,doSomethingWithA);

gspStreamResponse sr2_b("=b",4,[](const char * szInput){
  Serial.print("as a lambda function");
  Serial.println(szInput);
});

void setup() {
  Serial.begin(115200);
  
  // one of these for each gspStreamResponse you use.
  gspGrouped::register_instance(&sr1_a);
  gspGrouped::register_instance(&sr2_b);
  
  // once only, in setup.
  gspStreamResponse::setup();
}

void loop() {

  // once only in loop.
  gspStreamResponse::checkAll();
}
```
### Using it with platformio

add the following lines to your lib_deps in platformio.ini
 - https://github.com/edwar64896/gspstreamresponse
 - https://github.com/edwar64896/functional-avr
 - https://github.com/edwar64896/gspgrouped
