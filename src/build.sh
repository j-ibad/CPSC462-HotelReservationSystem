#!/bin/sh
g++  *.cpp -o out -I . ./Domain/*/*.cpp ./TechnicalServices/*/*.cpp ./UI/*.cpp -std=c++17