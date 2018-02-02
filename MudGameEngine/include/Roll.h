#ifndef ROLL_H
#define ROLL_H

/* Roll packages all the information used by damage, hit and other die rolls.
 */
struct Roll {
    int numOfDie;
    // sizeOfDie = number of sides on the die.
    int sizeOfDie;
    int rollModifier;
};

#endif