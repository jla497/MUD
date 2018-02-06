#ifndef UNIQUE_ID_H
#define UNIQUE_ID_H

#include <iostream>

/* Generates unique Ids for the use of game entities, to be
   used at time of construction */
class UniqueId {
   private:
    static unsigned int nextUniqueId;
    unsigned int id;

   public:
    UniqueId() : id(nextUniqueId++) {}

    unsigned int getId() const;

    bool operator==(const UniqueId& rhs ) const {
        return ( id == rhs.id );
    }
    bool operator<(const UniqueId& rhs ) const {
        return ( id < rhs.id );
    }

    inline friend std::ostream& operator<< (std::ostream& os, const UniqueId& Uid) {
      os << Uid.id;
      return os;
    }
};

#endif
