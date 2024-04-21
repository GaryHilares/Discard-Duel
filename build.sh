#!/bin/bash
mkdir build
g++ -o build/discard-duel -lstdc++ src/model/Player.cpp src/model/BotPlayer.cpp\
    src/model/Card.cpp src/model/Game.cpp src/ui/GameUI.cpp src/ui/main.cpp src/model/Hand.cpp
