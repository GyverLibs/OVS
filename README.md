[![latest](https://img.shields.io/github/v/release/GyverLibs/OVS.svg?color=brightgreen)](https://github.com/GyverLibs/OVS/releases/latest/download/OVS.zip)
[![Foo](https://img.shields.io/badge/Website-AlexGyver.ru-blue.svg?style=flat-square)](https://alexgyver.ru/)
[![Foo](https://img.shields.io/badge/%E2%82%BD$%E2%82%AC%20%D0%9D%D0%B0%20%D0%BF%D0%B8%D0%B2%D0%BE-%D1%81%20%D1%80%D1%8B%D0%B1%D0%BA%D0%BE%D0%B9-orange.svg?style=flat-square)](https://alexgyver.ru/support_alex/)
[![Foo](https://img.shields.io/badge/README-ENGLISH-blueviolet.svg?style=flat-square)](https://github-com.translate.goog/GyverLibs/OVS?_x_tr_sl=ru&_x_tr_tl=en)  

[![Foo](https://img.shields.io/badge/ПОДПИСАТЬСЯ-НА%20ОБНОВЛЕНИЯ-brightgreen.svg?style=social&logo=telegram&color=blue)](https://t.me/GyverLibs)

# OVS
Библиотека для повышения разрешения измерений Arduino (оверсэмплинг)
- Повышение разрядности до +6 бит
- Ручной режим работы (любые данные)
- Автоматический режим работы (бортовой АЦП)
- Быстрые вычисления

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
### Обновление
- Рекомендую всегда обновлять библиотеку: в новых версиях исправляются ошибки и баги, а также проводится оптимизация и добавляются новые фичи
- Через менеджер библиотек IDE: найти библиотеку как при установке и нажать "Обновить"
- Вручную: **удалить папку со старой версией**, а затем положить на её место новую. "Замену" делать нельзя: иногда в новых версиях удаляются файлы, которые останутся при замене и могут привести к ошибкам!


<a id="init"></a>
## Инициализация
```cpp
OVS<gain> ovs;
// gain - в <> указывается НА сколько бит нужно повысить разрешение. От 1 до 6 (включительно)
```

<a id="usage"></a>
## Использование
```cpp
uint32_t read(uint8_t pin);     // прочитать с аналогового пина и преобразовать
uint32_t get();                 // получить значение (обновляется после read() и compute())
uint32_t getMax(uint16_t bits); // получить максимальное значение при начальном разрешении
uint16_t samples();             // получить количество измерений, которое нужно сделать

void reset();                   // сбросить расчёт
void add(uint16_t val);         // добавить измерение
void compute();                 // преобразовать
```
Библиотеку можно использовать как для работы с бортовым АЦП, так и для обработки данных с других источников.  

### Бортовой АЦП
Достаточно вызвать `read(аналоговый пин)`, которая вернёт преобразованный результат. 
Также можно можно забирать предыдущее преобразованное значение из `get()`.

### Ручной режим
В этом режиме можно скормить библиотеке значения с других источников:
- Перед новым измерением нужно вызвать `reset()`
- Далее нужно передавать новые значения в `add(val)` в количестве, равном `samples()`
- После передачи нужного количества значений вызвать `compute()`
- Забираем преобразованное значение из `get()`

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
  Serial.print(ovs.read(0));
  Serial.print(',');
  
  // после ovs.read() можно забирать последний результат из ovs.get()

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
- v1.1 - read() возвращает результат

<a id="feedback"></a>
## Баги и обратная связь
При нахождении багов создавайте **Issue**, а лучше сразу пишите на почту [alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
Библиотека открыта для доработки и ваших **Pull Request**'ов!


При сообщении о багах или некорректной работе библиотеки нужно обязательно указывать:
- Версия библиотеки
- Какой используется МК
- Версия SDK (для ESP)
- Версия Arduino IDE
- Корректно ли работают ли встроенные примеры, в которых используются функции и конструкции, приводящие к багу в вашем коде
- Какой код загружался, какая работа от него ожидалась и как он работает в реальности
- В идеале приложить минимальный код, в котором наблюдается баг. Не полотно из тысячи строк, а минимальный код
