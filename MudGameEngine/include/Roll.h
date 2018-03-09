#ifndef ROLL_H
#define ROLL_H

#include <boost/serialization/access.hpp>

/* Roll packages all the information used by damage, hit and other die rolls.
 */
struct Roll {
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        (void)version;
        ar &numOfDie;
        ar &sizeOfDie;
        ar &rollModifier;
    }

    int numOfDie{};
    // sizeOfDie = number of sides on the die.
    int sizeOfDie{};
    int rollModifier{};
};

#endif
