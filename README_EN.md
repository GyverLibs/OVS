This is an automatic translation and may be incorrect in some places. See the source README and examples for authoritative information.

[![latest](https://img.shields.io/github/v/release/GyverLibs/OVS.svg?color=brightgreen)](https://github.com/GyverLibs/OVS/releases/latest/download/OVS.zip)
[![PIO](https://badges.registry.platformio.org/packages/gyverlibs/library/OVS.svg)](https://registry.platformio.org/libraries/gyverlibs/OVS)
[![Foo](https://img.shields.io/badge/Website-AlexGyver.ru-blue.svg?style=flat-square)](https://alexgyver.ru/)
[![Foo](https://img.shields.io/badge/%E2%82%BD%24%E2%82%AC%20%D0%9F%D0%BE%D0%B4%D0%B4%D0%B5%D1%80%D0%B6%D0%B0%D1%82%D1%8C-%D0%B0%D0%B2%D1%82%D0%BE%D1%80%D0%B0-orange.svg?style=flat-square)](https://alexgyver.ru/support_alex/)
[![Foo](https://img.shields.io/badge/README-ENGLISH-blueviolet.svg?style=flat-square)](https://github-com.translate.goog/GyverLibs/OVS?_x_tr_sl=ru&_x_tr_tl=en)  

[![Foo](https://img.shields.io/badge/ПОДПИСАТЬСЯ-НА%20ОБНОВЛЕНИЯ-brightgreen.svg?style=social&logo=telegram&color=blue)](https://t.me/GyverLibs)

# OVS
Library for increasing the resolution of measurements Arduino (oversampling)
- Increased bit size to +6 bits
- Manual mode of operation (any data)
- Automatic operating mode (on-board ADC)
- Fast computing

### Compatibility
Compatible with all Arduino platforms (Arduino features are used)

## Contents
- [Installation](#install)
- [Initialization](#init)
- [Use of use](#usage)
- [Example](#example)
- [Versions](#versions)
- [Bugs and feedback](#feedback)

<a id="init"></a>

## Initialization
```cpp
OVS<gain> ovs;
// gain: <> indicates how many bits you need to increase the resolution. 1 to 6 (inclusive)
```

<a id="usage"></a>

## Use of use
```cpp
uint32_t read(uint8_t pin);     // Read from analog pin and convert
uint32_t get();                 // Receive value (updated after read() and compute())
uint32_t getMax(uint16_t bits); // maximum value at the initial resolution
uint16_t samples();             // The number of measurements that need to be taken

void reset();                   // discharge
void add(uint16_t val);         // add
void compute();                 // transform
```The library can be used both for working with the onboard ADC, and for processing data from other sources.

### Airborne ADC
Enough to call.`read(аналоговый пин)`which will return the converted result.
You can also take the previous converted value from`get()`.

### Manual mode
In this mode, you can feed the library values from other sources:
- Before a new dimension must be called`reset()`
- You need to transfer new values to`add(val)`equal`samples()`
- After transferring the required number of values, call`compute()`
- Take the converted value from`get()`

### No class.
```cpp
// The number of measurements that need to be made
constexpr uint16_t OVS_SAMPLES(uint8_t gain);

// maximum value at the initial resolution
constexpr uint16_t OVS_MAX(uint8_t base, uint8_t gain);

// number by which the amount must be moved
constexpr uint32_t OVS_SHIFT(uint8_t gain);
```
```cpp
const uint8_t gain = 2;
uint32_t sum = 0;
for (uint16_t i = 0; i < OVS_SAMPLES(gain); i++) {
  sum += analogRead(0);
}
sum >>= OVS_SHIFT(gain);
```

### How does it work?
Oversampling actually averages **N** measurements (in the library, this amount can be obtained from the`samples()`), 
adjusting the new range to the specified increase in the resolution **Gain**. Number of measurements required
depends on the increase as`N = 2^(2*Gain)`That is, to increase the resolution by 6 bits will need 4096 measurements!

Gain|N      |
----|-------|
+1  |4      |
+2  |16     |
+3  |64     |
+4  |256    |
+5  |1024   |
+6  |4096   |

<a id="example"></a>

## Example
### Airborne ADC
```cpp
#include <OVS.h>

// increase the digits by 2
// (AVR Arduino 10+2 = 12 bits)
OVS<2> ovs;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Read from analog pin and convert
  Serial.print(ovs.read(0));
  Serial.print(',');
  
  // After ovs.read() you can pick up the last result from ovs.get()

  // We output the maximum value at the initial resolution (we have an ADC of 10 bits)
  Serial.println(ovs.getMax(10));
}
```

### Manual mode
```cpp
// oversampling, manual mode
#include <OVS.h>

// increase the digits by 2
// (AVR Arduino 10+2 = 12 bits)
OVS<2> ovs;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // drop off before measurement
  ovs.reset();

  // Add new values in the number of ovs.samples()
  for (int i = 0; i < ovs.samples(); i++) {
    ovs.add(analogRead(0));
  }

  // transformable
  ovs.compute();

  // output
  Serial.print(ovs.get());
  Serial.print(',');

  // We output the maximum value at the initial resolution (we have an ADC of 10 bits)
  Serial.println(ovs.getMax(10));
}
```

<a id="versions"></a>

## Versions
- v1.0
- v1.1 - read() returns the result

<a id="install"></a>

## Installation
- The library can be found by the name **OVS** and installed through the library manager in:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Download the library](https://github.com/GyverLibs/OVS/archive/refs/heads/main.zip).zip archive for manual installation:
    - Unpack and put in *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Unpack and put in *C:\Program Files\Arduino\libraries* (Windows x32)
    - Unpack and put in *Documents/Arduino/libraries/ *
    - (Arduino IDE) Automatic installation from .zip: *Sketch/Connect library/Add .ZIP library...* and specify downloaded archive
- Read more detailed instructions for installing libraries[here](https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Update
- I recommend always updating the library: new versions fix errors and bugs, as well as optimize and add new features.
- Through the library manager IDE: find the library as when installing and click "Update"
- Manually: **Delete the folder with the old version** and then put the new one in its place. “Replacement” can not be done: sometimes new versions delete files that will remain when replaced and can lead to errors!

<a id="feedback"></a>

## Bugs and feedback
If you find bugs, create **Issue**, or better write to the mail immediately.[alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
The library is open for revision and your **Pull Requests*!

When reporting bugs or incorrect work of the library, it is necessary to specify:
- Library version
- What is used by the IC
- SDK version (for ESP)
- Arduino IDE version
- Are embedded examples that use features and designs that cause bugs in your code working correctly?
- What code was downloaded, what work was expected from it and how it works in reality
- Ideally, attach the minimum code in which the bug is observed. Not a canvas of a thousand lines, but a minimum code.
