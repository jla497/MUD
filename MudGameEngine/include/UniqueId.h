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
};

unsigned int UniqueId::nextUniqueId = 1;

#endif
