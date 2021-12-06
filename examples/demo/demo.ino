#include <OVS.h>

// увеличим разрядность на 2
// (AVR Arduino 10+2 = 12 бит)
OVS<2> ovs;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // прочитать с аналогового пина и преобразовать
  Serial.print(ovs.read(0));
  Serial.print(',');
  
  // после ovs.read() можно забирать последний результат из ovs.get()

  // выводим макс. значение при начальном разрешении (У нас АЦП 10 бит)
  Serial.println(ovs.getMax(10));
}
