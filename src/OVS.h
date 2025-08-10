#pragma once
#include <Arduino.h>

// количество измерений, которое нужно сделать
constexpr uint16_t OVS_SAMPLES(uint8_t gain) {
    return 1ul << (gain << 1);
}

// максимальное значение при начальном разрешении
constexpr uint16_t OVS_MAX(uint8_t base, uint8_t gain) {
    return (1ul << (gain + base)) - (1 << gain);
}

// число, на которое нужно сдвинуть сумму
constexpr uint32_t OVS_SHIFT(uint8_t gain) {
    return gain;
}

template <uint8_t _GAIN>
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
        _sum >>= OVS_SHIFT(_GAIN);
    }

    // получить значение
    uint32_t get() const {
        return _sum;
    }

    // получить максимальное значение при начальном разрешении
    constexpr uint32_t getMax(uint16_t base) const {
        return OVS_MAX(base, _GAIN);
    }

    // получить количество измерений, которое нужно сделать
    constexpr uint16_t samples() const {
        return OVS_SAMPLES(_GAIN);
    }

   private:
    uint32_t _sum = 0;
};