//
// Created by Badi on 9/6/2024.
//

#ifndef PROJECT_ESPRIT_MODEL_C_CHARACTER_H
#define PROJECT_ESPRIT_MODEL_C_CHARACTER_H

#include <iostream>
#include "Bar.h"

class Character {
private:
    std::string name; // Character name

    int level; // Character Level
    int hp; // Health points, if it reaches 0, the character falls.
    int exp;

    Bar hp_bar; // Bar manager for the current health points.
    Bar esprit; // Bar manager for the Esprit fuel.

    int STR; // Strength, represents physical prowess.
    int DEX; // Dexterity, represents hand-eye, quick reactions.
    int CON; // Constitution, represents the bodily fortitude.
    int WIS; // Wisdom, describes the ability to perceive and infer on survival instincts.
    int INT; // Intelligence, describes one's mental fortitude and intellect.
    int CHA; // Charisma, describes one's ability to talk and convey emotion.
    int LUK; // Luck, influences a few random events, and critical hits.

    



};


#endif //PROJECT_ESPRIT_MODEL_C_CHARACTER_H
