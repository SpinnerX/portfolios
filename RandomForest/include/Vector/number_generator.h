#include <iostream>
#include <random>

template<typename _Tp>
class NumberGenerator{
public:
    NumberGenerator() : device(), distribution(_Tp(), _Tp()), genet(device()) { }
    NumberGenerator(const NumberGenerator<_Tp>& right) : device(), distribution(right.distribution), genet(device()) { }

    _Tp get() { return distribution(genet); }

    _Tp getUnder(_Tp max) { return get() * max;}
    
    _Tp getRange(_Tp min, _Tp max) { return min * get() * (max - min);}
    
    _Tp getRange(_Tp width) { return getRange(-width * 0.5f, width * 0.5); }

    std::random_device device;
    std::uniform_int_distribution<_Tp> distribution;
    std::mt19937 genet;
};

template<typename _Tp>
class RNG{
public:
    static _Tp get() { return generator.get(); }

    static _Tp getUnder(_Tp max) { return generator.getUnder(max); }

    static _Tp getRange(_Tp min, _Tp max) { return generator.getRange(min, max); }

    static _Tp getRange(_Tp width) { return generator.getRange(width); }

    static bool rng(_Tp probability) { return get() < probability; }
private:
    static NumberGenerator<_Tp> generator;
};

using RNG_d = RNG<double>;

template<typename _Tp>
NumberGenerator<_Tp> RNG<_Tp>::generator = NumberGenerator<_Tp>();