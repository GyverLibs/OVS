#include <OVS.h>

// увеличим разрядность на 2
// (AVR Arduino 10+2 = 12 бит)
OVS<2> ovs;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // прочитать с аналогового пина и преобразовать
  ovs.process(0);

  // выводим результат
  Serial.print(ovs.get());
  Serial.print(',');

  // выводим макс. значение при заданной битности (У нас АЦП 10 бит)
  Serial.println(ovs.getMax(10));
}
