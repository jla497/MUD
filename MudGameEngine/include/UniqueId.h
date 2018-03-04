#ifndef UNIQUE_ID_H
#define UNIQUE_ID_H

#include <iostream>
#include <boost/serialization/access.hpp>

/* Generates unique Ids for the use of game entities, to be
   used at time of construction */
class UniqueId {
  private:
    static unsigned int nextUniqueId;
    unsigned int id = nextUniqueId++;

    friend class boost::serialization::access;

    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar &id;
        ar &nextUniqueId;
    }

  public:
    UniqueId() : id(nextUniqueId++) {}
    UniqueId(int id) : id((unsigned int)id) {}
    unsigned int getId() const;

    bool operator==(const UniqueId &rhs) const { return (id == rhs.id); }
    bool operator<(const UniqueId &rhs) const { return (id < rhs.id); }

    inline friend std::ostream &operator<<(std::ostream &os,
                                           const UniqueId &Uid) {
        os << Uid.id;
        return os;
    }
};

#endif
