// оверсэмплинг, ручной режим
#include <OVS.h>

// увеличим разрядность на 2
// (AVR Arduino 10+2 = 12 бит)
OVS<2> ovs;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // сбрасываем перед измерением
  ovs.reset();

  // добавляем новые значения в количестве ovs.samples()
  for (int i = 0; i < ovs.samples(); i++) {
    ovs.add(analogRead(0));
  }

  // преобразовываем
  ovs.compute();

  // выводим результат
  Serial.print(ovs.get());
  Serial.print(',');

  // выводим макс. значение при заданной битности (У нас АЦП 10 бит)
  Serial.println(ovs.getMax(10));
}
