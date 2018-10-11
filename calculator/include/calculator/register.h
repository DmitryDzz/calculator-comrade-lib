//
// Created by dmitrydzz on 09.10.18.
//

#ifndef CALCULATORCOMRADE_REGISTER_H
#define CALCULATORCOMRADE_REGISTER_H

#include <array>
#include <cstdint>

namespace calculatorcomrade {
    class Register {
    public:
        std::array<uint8_t, 16> data{};
        uint8_t inputPos = 0;
        uint8_t pointPos = 0;
        bool negative = false;
        bool overflow = false;

        bool operator==(const Register& other) {
            return *this == other;
        }

        bool static isEqual(const Register& lhs, const Register& rhs) {
            bool result = lhs.data == rhs.data &&
                          lhs.inputPos == rhs.inputPos &&
                          lhs.pointPos == rhs.pointPos &&
                          lhs.negative == rhs.negative &&
                          lhs.overflow == rhs.overflow;
            return result;
        }
    };

    bool operator==(const Register& lhs, const Register& rhs) {
        return Register::isEqual(lhs, rhs);
    }

    bool operator!=(const Register& lhs, const Register& rhs) {
        return !Register::isEqual(lhs, rhs);
    }
}

#endif //CALCULATORCOMRADE_REGISTER_H
