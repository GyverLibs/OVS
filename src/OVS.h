/*
    Библиотека для повышения разрядности измерений (оверсэмплинг)
    GitHub: https://github.com/GyverLibs/OVS
    Возможности:
    - Повышение разрядности до +6 бит
    - Ручной режим работы (любые данные)
    - Автоматический режим работы (бортовой АЦП)
    - Быстрые вычисления

    AlexGyver, alex@alexgyver.ru
    https://alexgyver.ru/
    MIT License

    Версии:
    v1.0 - релиз
    v1.1 - read() возвращает результат
*/

#ifndef _OVS_h
#define _OVS_h
#include <Arduino.h>

template < uint8_t _GAIN >
class OVS {
public:
    // прочитать с аналогового пина и преобразовать
    uint32_t read(uint8_t pin) {
        reset();
        for (int i = 0; i < samples(); i++) add(analogRead(pin));
        compute();
        return _sum;
    }
    
    // сбросить расчёт
    void reset() {
        _sum = 0;
    }
    
    // добавить измерение
    void add(uint16_t val) {
        _sum += val;
    }
    
    // преобразовать значение
    void compute() {
        _sum >>= _GAIN;
    }
    
    // получить значение
    uint32_t get() {
        return _sum;
    }
    
    // получить максимальное значение при начальном разрешении
    uint32_t getMax(uint16_t bits) {
        return (1ul << (_GAIN + bits)) - (1 << _GAIN);
    }

    // получить количество измерений, которое нужно сделать
    uint16_t samples() {
        return (1ul << (_GAIN << 1));
    }
    
private:
    uint32_t _sum = 0;
};
#endif