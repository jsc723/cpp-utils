#pragma once
#include <tuple>
#include <ostream>

namespace sj {

    template<typename T>
    T xgcd(T a, T b, T *px, T *py) {
        T prev_x = 1, prev_y = 0;
        T x = 0, y = 1;
        T q, next_x, next_y;
        while(b) {
            q = a/b;
            std::tie(x, prev_x) = std::make_tuple(prev_x - q*x, x);
            std::tie(y, prev_y) = std::make_tuple(prev_y - q*y, y);
            std::tie(a, b) = std::make_tuple(b, a%b);
        }
        if (px) *px = prev_x;
        if (py) *py = prev_y;
        return a;
    }

    template<typename T>
    T mod_inverse(T num, T mod) {
        T x;
        T g = xgcd<T>(num, mod, &x, nullptr);
        if (x < 0) x += mod;
        return x;
    }

/* Basic Mod Numbers -- for code competitions, easy to copy and paste */
    template<unsigned Mod, typename T = long long>
    class BasicModNumber {
    protected:
        T data;
    public:
        BasicModNumber(): data(0) {}
        template<typename Integral>
        BasicModNumber(Integral num):data(num % Mod) {}

        T get() const { return data % Mod; }
        
        friend BasicModNumber operator+(const BasicModNumber &lhs, const BasicModNumber &rhs) {
            return (lhs.get() + rhs.get())%Mod;
        }

        friend BasicModNumber operator-(const BasicModNumber &lhs, const BasicModNumber &rhs) {
            return (Mod + lhs.get() - rhs.get())%Mod;
        }

        friend BasicModNumber operator*(const BasicModNumber &lhs, const BasicModNumber &rhs) {
            return (lhs.get() * rhs.get())%Mod;
        }
    };

/* Full Mod Number -- for real projects */
    template<unsigned Mod, typename T = long long>
    class ModNumber: public BasicModNumber<Mod, T> {
        //make names in parent template class visible
        using BasicModNumber<Mod, T>::data;
        using BasicModNumber<Mod, T>::get;

    public:
        ModNumber(): BasicModNumber<Mod, T>() {}
        template<typename Integral>
        ModNumber(Integral num): BasicModNumber<Mod, T>(num) {}

        ModNumber inv() const { return mod_inverse<T>(this->get(), Mod); }

        friend ModNumber operator+(const ModNumber &lhs, const ModNumber &rhs) {
            return (lhs.get() + rhs.get())%Mod;
        }
        void operator+=(const ModNumber &rhs) {
            data = (data + rhs.get()) % Mod;
        }

        friend ModNumber operator-(const ModNumber &lhs, const ModNumber &rhs) {
            return (Mod + lhs.get() - rhs.get())%Mod;
        }
        void operator-=(const ModNumber &rhs) {
            data = (Mod + data - rhs.get()) % Mod;
        }

        friend ModNumber operator*(const ModNumber &lhs, const ModNumber &rhs) {
            return (lhs.get() * rhs.get())%Mod;
        }
        void operator*=(const ModNumber &rhs) {
            data = (data * rhs.get()) % Mod;
        }

        friend ModNumber operator/(const ModNumber &lhs, const ModNumber &rhs) {
            return lhs.get() * rhs.inv();
        }
        void operator/=(const ModNumber &rhs) {
            data = (data * rhs.inv()).get();
        }

        friend std::ostream& operator<<(std::ostream& os, const ModNumber &rhs) {
            return os << rhs.get() << " (mod " << Mod << ")";
        }
    };
    
}
