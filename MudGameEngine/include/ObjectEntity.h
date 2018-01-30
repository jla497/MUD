#ifndef OBJECT_ENTITY_H
#define OBJECT_ENTITY_H

#include "Entity.h"

struct Extra {
    std::vector<std::string> desc;
    std::vector<std::string> keywords;
};

class ObjectEntity : public Entity {
   private:
    std::vector<std::string> m_attributes;
    unsigned int m_cost;
    Extra m_extra;
    unsigned int m_objectTypeId;
    std::string m_itemType;  // possible for enum?
    std::vector<std::string> m_keywords;
    std::vector<std::string> m_longDesc;
    std::string m_shortDesc;
    std::vector<std::string> m_wearFlags;
    int m_weight;

   public:
    ObjectEntity(UniqueId& id, std::vector<std::string>& attributes,
                 unsigned int cost, std::vector<std::string>& descExtra,
                 std::vector<std::string>& keywordsExtra,
                 unsigned int objectTypeId, std::string& itemType,
                 std::vector<std::string>& keywords,
                 std::vector<std::string>& longDesc, std::string& shortDesc,
                 std::vector<std::string>& wearFlags, int weight);
};

#endif
