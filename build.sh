#!/bin/bash
mkdir build
g++ -o build/discard-duel -lstdc++ src/Bot.cpp src/Card.cpp src/game.cpp src/main.cpp
