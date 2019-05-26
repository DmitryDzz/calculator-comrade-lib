/**
 * Calculator Comrade Library
 * License: https://github.com/DmitryDzz/calculator-comrade-lib/blob/master/LICENSE
 * Author: Dmitry Dzakhov
 * Email: info@robot-mitya.ru
 */
#include <gmock/gmock.h>
#include "calculator/calculator.h"
#include "calculator/config.h"
#include "calc_helper.h"

using calculatorcomrade::Button;
using calculatorcomrade::Calculator;
using calculatorcomrade::Config;
//using namespace calculatorcomrade;

#define TEST_DUMP(test_name) TEST(TestDump, test_name)

// Dump structure for 8 digit calculator:
// 0    version
// 1    dump size
// 2    size_
// 3    options_
// 4    operation_
// 5    hasOperation_
// 6    inNumber_
// 7    inputSize_
// 8    inputHasPoint_
// 9    lastButton_
// 10   lastButtonWasCe_
//
//  Register X
// 11   data[0]
// 12   data[1]
// 13   data[2]
// 14   data[3]
// 15   data[4]
// 16   data[5]
// 17   data[6]
// 18   data[7]
// 19   pointPos_
// 20   negative_
// 21   hasError_
// 22   hasOverflow_
//
//  Register Y
// 23   data[0]
// 24   data[1]
// 25   data[2]
// 26   data[3]
// 27   data[4]
// 28   data[5]
// 29   data[6]
// 30   data[7]
// 31   pointPos_
// 32   negative_
// 33   hasError_
// 34   hasOverflow_
//
//  Register M
// 35   data[0]
// 36   data[1]
// 37   data[2]
// 38   data[3]
// 39   data[4]
// 40   data[5]
// 41   data[6]
// 42   data[7]
// 43   pointPos_
// 44   negative_
// 45   hasError_
// 46   hasOverflow_

TEST_DUMP(DumpSize) {
    Calculator calc8(8);
    int8_t dumpSize8 = calc8.exportDump(nullptr);
    ASSERT_EQ(47, dumpSize8);

    Calculator calc12(12);
    int8_t dumpSize12 = calc12.exportDump(nullptr);
    ASSERT_EQ(59, dumpSize12);
}

TEST_DUMP(ExportDump) {
    Calculator c(8);

    int8_t dumpSize = c.exportDump(nullptr);
    auto* dump = new int8_t[dumpSize];

    dumpSize = c.exportDump(dump);
    ASSERT_EQ(47, dumpSize);
    ASSERT_EQ((int8_t) Config::DUMP_VERSION, dump[0]);
    ASSERT_EQ(dumpSize, dump[1]);
    ASSERT_EQ((int8_t) Config::OPTIONS_DEFAULT, dump[3]);
    for (int8_t i = 4; i < dumpSize; i++) {
        ASSERT_EQ(0, dump[i]);
    }
}

TEST_DUMP(CheckDump) {
    Calculator c(8);

    int8_t dumpSize = c.exportDump(nullptr);
    auto* dump = new int8_t[dumpSize];

    c.input(Button::d2);
    c.input(Button::plus);
    c.input(Button::d3);
    c.input(Button::ceca);

    c.exportDump(dump);

    c.input(Button::d4);
    c.input(Button::equals);
    ASSERT_EQ(6, getIntValue(c.getX()));

    int8_t importedSize = c.importDump(dump, dumpSize);
    ASSERT_EQ(dumpSize, importedSize);

    c.input(Button::d5);
    c.input(Button::equals);
    ASSERT_EQ(7, getIntValue(c.getX()));
}