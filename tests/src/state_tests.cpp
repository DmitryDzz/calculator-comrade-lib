//
// Created by dmitrydzz on 18.10.18.
//

#include <gmock/gmock.h>
#include <gtest/internal/gtest-port.h>
#include <fstream>
#include <dirent.h>
#include "json.hpp"

#include "calculator/calculator.h"
#include "calculator/state.h"
#include "calculator/button.h"
#include "calculator/operation.h"

using calculatorcomrade::Calculator;
using calculatorcomrade::DisplayRegister;
using calculatorcomrade::State;
using calculatorcomrade::Button;
using calculatorcomrade::Operation;
using nlohmann::json;

struct JsonState {
    int x;
    int y;
    std::string operation;
    int displayReg;
    int signX;
    int signY;
    int pointPosX;
    int pointPosY;
    int overflow;
};

void from_json(const json& j, JsonState& v) {
    j.at("x").get_to(v.x);
    j.at("y").get_to(v.y);
    j.at("operation").get_to(v.operation);
    j.at("displayReg").get_to(v.displayReg);
    j.at("signX").get_to(v.signX);
    j.at("signY").get_to(v.signY);
    j.at("pointPosX").get_to(v.pointPosX);
    j.at("pointPosY").get_to(v.pointPosY);
    j.at("overflow").get_to(v.overflow);
}

struct JsonKeyState {
    std::string key;
    JsonState state;
};

void from_json(const json& j, JsonKeyState& v) {
    j.at("key").get_to(v.key);
    j.at("state").get_to(v.state);
}

struct JsonStateTest {
    std::string name;
    std::vector<JsonKeyState> keys;
};

void from_json(const json& j, JsonStateTest& v) {
    j.at("name").get_to(v.name);
    j.at("keys").get_to(v.keys);
}

uint8_t getDigitsFromParams() {
    std::vector<std::string> argvs = testing::internal::GetArgvs();
    const std::string PARAM = "--digits=";
    for (auto& argv : argvs) {
        if (argv.find(PARAM) == 0) {
            try {
                return static_cast<uint8_t>(std::stoi(argv.erase(0, PARAM.size())));
            } catch(std::invalid_argument) {
                return Config::DEFAULT_DIGITS;
            }
        }
    }
    return Config::DEFAULT_DIGITS;
}

std::string getStateTestsDirectoryFromParams() {
    std::vector<std::string> argvs = testing::internal::GetArgvs();
    const std::string PARAM = "--state-tests-dir=";
    for (auto& argv : argvs) {
        if (argv.find(PARAM) == 0)
            return argv.erase(0, PARAM.size());
    }
    return "";
}

void getFilesInDirectory(const std::string& name, std::vector<std::string>& files) {
    const unsigned char IS_FILE = 0x08;
    DIR* dirp = opendir(name.c_str());
    struct dirent* dp;
    while ((dp = readdir(dirp)) != nullptr) {
        if (dp->d_type == IS_FILE) {
            files.emplace_back(dp->d_name);
        }
    }
    closedir(dirp);
}

void fillState(const JsonState& jsonState, State& state) {
    if (jsonState.operation == "+")
        state.operation = Operation::add;
    else if (jsonState.operation == "-")
        state.operation = Operation::sub;
    else if (jsonState.operation == "*")
        state.operation = Operation::mul;
    else if (jsonState.operation == "/")
        state.operation = Operation::div;
    else if (jsonState.operation == "%")
        state.operation = Operation::percent;
    else
        state.operation = Operation::none;

    if (jsonState.displayReg == 0)
        state.displayRegister = DisplayRegister::x;
    else if (jsonState.displayReg == 1)
        state.displayRegister = DisplayRegister::y;
    else
        state.displayRegister = DisplayRegister::none;

    state.x.setValue(jsonState.x);
    state.y.setValue(jsonState.y);

    state.x.negative = jsonState.signX > 0;
    state.y.negative = jsonState.signY > 0;

    state.x.pointPos = static_cast<uint8_t>(jsonState.pointPosX);
    state.y.pointPos = static_cast<uint8_t>(jsonState.pointPosY);

    state.x.overflow = jsonState.displayReg == 0 && jsonState.overflow > 0;
    state.y.overflow = jsonState.displayReg == 1 && jsonState.overflow > 0;
}

TEST(TestStates, JsonTests) {
    uint8_t digits = getDigitsFromParams();
    std::string stateTestsDirectory = getStateTestsDirectoryFromParams();
    std::vector<std::string> files;
    getFilesInDirectory(stateTestsDirectory, files);

    for (auto& filename : files) {
        std::string s = stateTestsDirectory + filename;
        std::ifstream jsonFile(s);
        json j;
        jsonFile >> j;
        std::vector<JsonStateTest> tests = j;

        for (auto& test : tests) {
            std::cout << "[   TEST   ] " << test.name << std::endl;
            int line = 1;
            for (auto& keyState : test.keys) {
                Calculator calculator(digits);
                calculator.input(keyState.key);
                State state(digits);
                fillState(keyState.state, state);
                ASSERT_EQ(state, calculator.getState()) << "(" << test.name << ": line #" << line++ << ")" << std::endl;
            }
        }
    }
}
