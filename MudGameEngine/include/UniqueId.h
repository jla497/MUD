#ifndef UNIQUE_ID_H
#define UNIQUE_ID_H

/* Generates unique Ids for the use of game entities, to be
   used at time of construction */
class UniqueId {
   private:
    static unsigned int nextUniqueId;
    unsigned int id;

   public:
    UniqueId() : id(nextUniqueId++) {}

    bool operator==(const UniqueId& rhs ) const {
        return ( id == rhs.id );
    }
    bool operator<(const UniqueId& rhs ) const {
        return ( id < rhs.id );
    }
};

#endif
