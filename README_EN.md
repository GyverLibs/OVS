This is an automatic translation, may be incorrect in some places. See sources and examples!

# OVS
Library for increasing the measurements of Arduino measurements (overshabeling)
- increasing discharge to +6 bits
- manual mode of operation (any data)
- automatic mode of operation (on -board ADC)
- Fast calculations

## compatibility
Compatible with all arduino platforms (used arduino functions)

## Content
- [installation] (# Install)
- [initialization] (#init)
- [use] (#usage)
- [Example] (# Example)
- [versions] (#varsions)
- [bugs and feedback] (#fedback)

<a id="install"> </a>
## Installation
- The library can be found by the name ** ovs ** and installed through the library manager in:
    - Arduino ide
    - Arduino ide v2
    - Platformio
- [download library] (https://github.com/gyverlibs/ovs/archive/refs/heads/main.zip). Zip archive for manual installation:
    - unpack and put in * C: \ Program Files (X86) \ Arduino \ Libraries * (Windows X64)
    - unpack and put in * C: \ Program Files \ Arduino \ Libraries * (Windows X32)
    - unpack and put in *documents/arduino/libraries/ *
    - (Arduino id) Automatic installation from. Zip: * sketch/connect the library/add .Zip library ... * and specify downloaded archive
- Read more detailed instructions for installing libraries [here] (https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%BD%D0%BE%BE%BE%BED0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Update
- I recommend always updating the library: errors and bugs are corrected in the new versions, as well as optimization and new features are added
- through the IDE library manager: find the library how to install and click "update"
- Manually: ** remove the folder with the old version **, and then put a new one in its place.“Replacement” cannot be done: sometimes in new versions, files that remain when replacing are deleted and can lead to errors!


<a id="init"> </a>
## initialization
`` `CPP
Ovs <gain> ovs;
// gain - in <> it is indicated how much bit you need to increase the resolution.From 1 to 6 (inclusive)
`` `

<a id="usage"> </a>
## Usage
`` `CPP
uint32_t Read (uint8_t pin);// read from analogue pin and transform
uint32_t get ();// get a value (updated after Read () and Compute ())
uint32_t getmax (uint16_t bits);// get the maximum value with the initial resolution
uint16_t samples ();// get the number of measurements that need to be done

VOID Reset ();// Reset the calculation
VOID Add (Uint16_t Val);// Add measurement
VOID Compute ();// Transform
`` `
The library can be used both for working with the on -board ADC, and for processing data from other sources.

## board ADC
It is enough to call `Read (analog PIN)`, which will return the transformed result.
You can also take the previous transformed value from `get ()`.

### Manual mode
In this mode, you can feed the library values from other sources:
- Before the new dimension, you need to call `reset ()`
- Next, you need to transmit new values to `Add (val)` in an amount equal to `samples ()`
- after transmitting the right number of values, call `compute ()`
- Take the transformed value from `get ()`

### How does it work
Overcupling actually averages ** n ** dimensions (to the libraryEKE this amount can be obtained from `samples ()`),
Turning a new range for the specified increase in the resolution ** gain **.The required number of measurements
Depends on the increase as `n = 2^(2*gain)`, that is, to increase the resolution by 6 bits, 4096 measurements will be needed!

Gain | N |
---- | ------ |
+1 | 4 |
+2 | 16 |
+3 | 64 |
+4 | 256 |
+5 | 1024 |
+6 | 4096 |

<a id="EXAMPLE"> </a>
## Example
## board ADC
`` `CPP
#include <OVS.H>

// increase the discharge by 2
// (AVR arduino 10+2 = 12 bits)
Ovs <2> ovs;

VOID setup () {
  Serial.Begin (9600);
}

VOID loop () {
  // read from analogue pin and transform
  Serial.print (OVS.Read (0));
  Serial.print (',');
  
  // After OVS.Read () you can take the last result from OVS.GET ()

  // We display Max.value at the initial resolution (we have ACP 10 bits)
  Serial.println (OVS.getmax (10));
}
`` `

### Manual mode
`` `CPP
// overcupling, manual mode
#include <OVS.H>

// increase the discharge by 2
// (AVR arduino 10+2 = 12 bits)
Ovs <2> ovs;

VOID setup () {
  Serial.Begin (9600);
}

VOID loop () {
  // drop before measurement
  OVS.Reset ();

  // Add new values in the amount of ovs.samples ()
  for (int i = 0; i <ovs.samples (); i ++) {
    OVS.Add (analogread (0));
  }

  // Transforming
  ovs.compute ();

  // We display the result
  Serial.print (OVS.GET ());
  Serial.print (',');

  // We display Max.value at the initial resolution (we have ACP 10 bits)
  Serial.println (OVS.getmax (10));
}
`` `

<a id="versions"> </a>
## versions
- V1.0
- V1.1 - Read () returns the result

<a id="feedback"> </a>
## bugs and feedback
Create ** Issue ** when you find the bugs, and better immediately write to the mail [alex@alexgyver.ru] (mailto: alex@alexgyver.ru)
The library is open for refinement and your ** pull Request ** 'ow!


When reporting about bugs or incorrect work of the library, it is necessary to indicate:
- The version of the library
- What is MK used
- SDK version (for ESP)
- version of Arduino ide
- whether the built -in examples work correctly, in which the functions and designs are used, leading to a bug in your code
- what code has been loaded, what work was expected from it and how it works in reality
- Ideally, attach the minimum code in which the bug is observed.Not a canvas of a thousand lines, but a minimum code