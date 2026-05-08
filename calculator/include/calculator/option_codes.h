/**
* Calculator Comrade Library
 * License: https://github.com/DmitryDzz/calculator-comrade-lib/blob/master/LICENSE
 * Author: Dmitry Dzakhov
 * Email: info@robot-mitya.ru
 */
#ifndef CALCULATORCOMRADE_OPTION_CODES_H
#define CALCULATORCOMRADE_OPTION_CODES_H

#ifdef __cplusplus
    #include <cstdint>
    using CalculatorOptions = std::uint8_t;
#else
    #include <stdint.h>
    typedef uint8_t CalculatorOptions;
#endif

#ifdef __cplusplus
enum : CalculatorOptions {
#else
enum {
#endif

    /**
     * Removes trailing zeros from an overflowed arithmetic result.
     *
     * When this option is enabled, trailing zeros are truncated after an
     * arithmetic operation that overflows the available display digits.
     *
     * For example, if the display has 8 digits, the exact result of
     * 10,000,000 * 100 is 1,000,000,000. Since the display has only 8 digits,
     * the calculator normally shows this as 10.000000. The decimal point after
     * the two most significant digits indicates that two additional digits are
     * implied beyond the visible result.
     *
     * With this option enabled, the result is shown without the zeros after the
     * decimal point: "10.". This behavior is less explicit, but some calculators
     * work this way.
     *
     * This option is not enabled by default.
     */
    CALC_OPTION_TRUNC_ZEROS_ON_OVERFLOW = 0x01,

    /**
     * Clears the X register when a memory operation overflows the memory
     * register.
     *
     * When this option is enabled, pressing M+ or M- clears the X register if
     * the memory register overflows. The X register is always shown on the
     * display, so clearing it provides a visible indication that a memory
     * overflow occurred.
     *
     * This is useful because memory register overflow does not show the
     * calculator error indicator on the display.
     *
     * This option is enabled by default. Some calculators keep the X register
     * unchanged when the memory register overflows.
     */
    CALC_OPTION_MEMORY_OVERFLOW_CLEARS_X = 0x02,

    /**
     * Default calculator options.
     *
     * By default, memory register overflow clears the X register, while
     * trailing zeros are not truncated after arithmetic overflow.
     */
    CALC_OPTIONS_DEFAULT = CALC_OPTION_MEMORY_OVERFLOW_CLEARS_X

};

#endif //CALCULATORCOMRADE_OPTION_CODES_H
