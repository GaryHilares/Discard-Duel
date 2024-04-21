#!/bin/bash
mkdir build
g++ -o build/discard-duel -lstdc++ src/model/Player.cpp src/model/BotPlayer.cpp\
    src/model/Card.cpp src/ui/Game.cpp src/ui/main.cpp src/model/Hand.cpp
