![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)
![author](https://img.shields.io/badge/author-AlexGyver-informational.svg)
# OVS
Библиотека для повышения разрядности измерений Arduino (оверсэмплинг)
- Повышение до +6 бит
- Ручной и автоматический режим работы
- Быстрая бинарная математика

### Совместимость
Совместима со всеми Arduino платформами (используются Arduino-функции)

## Содержание
- [Установка](#install)
- [Инициализация](#init)
- [Использование](#usage)
- [Пример](#example)
- [Версии](#versions)
- [Баги и обратная связь](#feedback)

<a id="install"></a>
## Установка
- Библиотеку можно найти по названию **OVS** и установить через менеджер библиотек в:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Скачать библиотеку](https://github.com/GyverLibs/OVS/archive/refs/heads/main.zip) .zip архивом для ручной установки:
    - Распаковать и положить в *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Распаковать и положить в *C:\Program Files\Arduino\libraries* (Windows x32)
    - Распаковать и положить в *Документы/Arduino/libraries/*
    - (Arduino IDE) автоматическая установка из .zip: *Скетч/Подключить библиотеку/Добавить .ZIP библиотеку…* и указать скачанный архив
- Читай более подробную инструкцию по установке библиотек [здесь](https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)

<a id="init"></a>
## Инициализация
```cpp
OVS<gain> ovs;
// gain - в <> указывается НА сколько бит нужно повысить разрешение. От 1 до 6 (включительно)
```

<a id="usage"></a>
## Использование
```cpp
void process(uint8_t pin);      // прочитать с аналогового пина и преобразовать
uint32_t get();                 // получить значение
uint32_t getMax(uint16_t bits); // получить максимальное значение при начальном разрешении
uint16_t samples();             // получить количество измерений, которое нужно сделать

void reset();                   // сбросить расчёт
void add(uint16_t val);         // добавить измерение
void compute();                 // преобразовать
```
Библиотеку можно использовать как для работы с бортовым АЦП, так и для обработки данных с других источников.  

### Бортовой АЦП
Достаточно вызвать `process(аналоговый пин)`, после чего можно забирать обработанное значение из `get()`.

### Ручной режим
В этом режиме можно скормить библиотеке значения с других источников:
- Перед новым измерением нужно вызвать `reset()`
- Далее нужно передавать новые значения в `add(val)` в количестве, равном `samples()`
- После передачи нужного количества значений вызвать `compute()`
- Забираем обработанное значение из `get()`

### Как работает
Оверсэмплинг фактически усредняет **N** измерений (в библиотеке это количество можно получить из `samples()`), 
подгоняя новый диапазон под указанное увеличение разрешения **Gain**. Необходимое количество измерений 
зависит от увеличения как `N = 2^(2*Gain)`, то есть для увеличения разрешения на 6 бит понадобится 4096 измерений!

Gain|N      |
----|-------|
+1  |4      |
+2  |16     |
+3  |64     |
+4  |256    |
+5  |1024   |
+6  |4096   |

<a id="example"></a>
## Пример
Остальные примеры смотри в **examples**!  
### Бортовой АЦП
```cpp
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

  // выводим макс. значение при начальном разрешении (У нас АЦП 10 бит)
  Serial.println(ovs.getMax(10));
}
```

### Ручной режим
```cpp
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

  // выводим макс. значение при начальном разрешении (У нас АЦП 10 бит)
  Serial.println(ovs.getMax(10));
}
```

<a id="versions"></a>
## Версии
- v1.0

<a id="feedback"></a>
## Баги и обратная связь
При нахождении багов создавайте **Issue**, а лучше сразу пишите на почту [alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
Библиотека открыта для доработки и ваших **Pull Request**'ов!