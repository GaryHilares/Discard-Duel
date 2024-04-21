#!/bin/bash
mkdir build
g++ -o build/discard-duel -lstdc++ src/model/Bot.cpp src/model/Card.cpp src/ui/Game.cpp src/ui/main.cpp src/model/Hand.cpp
