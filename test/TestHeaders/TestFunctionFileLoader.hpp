/**
 * @file testFunctionFileLoader.h
 * @author Henrik Henriksson
 *
 * @brief This file contains test function for the fileLoader class
 * @details In order to test that a file has been loaded correctly, we want a
 * function that creates a new file specifically for the test.
 */

#include <fstream>
#include <iostream>
#include <string>

void CreateFileToRead(std::string name) {
  std::ofstream of(name);
  of << "20x10\n";
  of << "00000000000000000000\n00000010000011001100\n00111000010010000010\n"
        "01110001010011001100\n00010100001000111010\n01000100000110001010\n"
        "00110011000110011000\n00001110000110011000\n01000001000011001100\n"
        "00000000000000000000";
  of.close();
};
