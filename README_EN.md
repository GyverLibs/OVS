This is an automatic translation, may be incorrect in some places. See sources and examples!

# OVS
Library for increasing the resolution of Arduino measurements (oversampling)
- Increasing the bit depth to +6 bits
- Manual operation mode (any data)
- Automatic operation mode (on-board ADC)
- Fast calculations

### Compatibility
Compatible with all Arduino platforms (using Arduino functions)

## Content
- [Install](#install)
- [Initialization](#init)
- [Usage](#usage)
- [Example](#example)
- [Versions](#versions)
- [Bugs and feedback](#feedback)

<a id="install"></a>
## Installation
- The library can be found under the name **OVS** and installed through the library manager in:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Download library](https://github.com/GyverLibs/OVS/archive/refs/heads/main.zip) .zip archive for manual installation:
    - Unzip and put in *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Unzip and put in *C:\Program Files\Arduino\libraries* (Windows x32)
    - Unpack and put in *Documents/Arduino/libraries/*
    - (Arduino IDE) automatic installation from .zip: *Sketch/Include library/Add .ZIP library…* and specify the downloaded archive
- Read more detailed instructions for installing libraries [here] (https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE% D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)

<a id="init"></a>
## Initialization
```cpp
ovs<gain> ovs;
// gain -The cranberry in <> indicates how many bits to increase the resolution. From 1 to 6 (inclusive)
```

<a id="usage"></a>
## Usage
```cpp
uint32_t read(uint8_t pin); // read from analog pin and convert
uint32_t get(); // get value (updated after read() and compute())
uint32_t getMax(uint16_t bits); // get maximum value at initial resolution
uint16_t samples(); // get the number of measurements to take

void reset(); // reset calculation
void add(uint16_tval); // add dimension
void compute(); // convert
```
The library can be used both to work with the onboard ADC and to process data from other sources.

### Onboard ADC
It is enough to call `read(analogue pin)`, which will return the converted result.
It is also possible to get the previous converted value from `get()`.

### Manual mode
In this mode, you can feed values ​​to the library from other sources:
- Before a new measurement, you need to call `reset()`
- Next, you need to pass new values ​​to `add(val)` in an amount equal to `samples()`
- After passing the required number of values, call `compute()`
- Get the converted value from `get()`

### How does it work
Oversampling actually averages **N** measurements (in the library, this number can be obtained from `samples()`),
fitting the new range to the specified **Gain** resolution increase. Required number of measurements
depends on the gain as `N = 2^(2*Gain)`, i.e. 4096 measurements are needed to increase the resolution by 6 bits!

Gain|N |
----|-------|
+1 |4 |
+2 |16 |
+3 |64 |
+4 |256 |
+5 |1024 |
+6 |4096 |

<a id="example"></a>
## Example
### Onboard ADC
```cpp
#include <OVS.h>

// increase bit depth by 2
// (AVR Arduino 10+2 = 12 bits)
ovs<2> ovs;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // read from analog pin and convert
  Serial print(ovs.cranberry read(0));
  Serial print(',');
  
  // after ovs.read() you can get the last result from ovs.get()

  // output max. value at initial resolution (We have 10 bit ADC)
  Serial.println(ovs.getMax(10));
}
```

### Manual mode
```cpp
// oversampling, manual mode
#include <OVS.h>

// increase bit depth by 2
// (AVR Arduino 10+2 = 12 bits)
ovs<2> ovs;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // reset before measurement
  ovs reset();

  // add new values ​​in the amount ovs.samples()
  for (int i = 0; i < ovs.samples(); i++) {
    ovs.add(analogRead(0));
  }

  // transform
  ovs.compute();

  // display the result
  Serial.print(ovs.get());
  Serial print(',');

  // output max. value at initial resolution (We have 10 bit ADC)
  Serial.println(ovs.getMax(10));
}
```

<a id="versions"></a>
## Versions
- v1.0
- v1.1 - read() returns result

<a id="feedback"></a>
## Bugs and feedback
When you find bugs, create an **Issue**, or better, immediately write to the mail [alex@alexgyver.ru](mailto:alex@alexgyver.ru)
The library is open for revision and your **Pull Request**'s!