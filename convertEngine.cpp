//
// Created by 刘一辰 on 2021/5/20.
//

#include "convertEngine.h"

ConvertEngine engine;

void ConvertEngine::compile() {
    module->print(dbgs(), nullptr);
}

// Unit test
int main() {
    engine.compile();
}