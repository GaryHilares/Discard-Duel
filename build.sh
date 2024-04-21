#!/bin/bash
mkdir build
g++ -o build/discard-duel -lstdc++ src/Bot.cpp src/Card.cpp src/Game.cpp src/main.cpp src/Hand.cpp
