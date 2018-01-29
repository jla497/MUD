#ifndef OBJECT_ENTITY_H
#define OBJECT_ENTITY_H

#include <string>

#include "Entity.h"

class ObjectEntity : public Entity {
   private:
    std::vector<std::string> m_attribute;
    unsigned int m_cost;
    std::vector<std::string> m_extra;
    unsigned int m_objectTypeId;
    std::string m_itemType;  // possible for enum?
    std::vector<std::string> m_keywords;
    std::string m_longDesc;
    std::string m_shortDesc;
    std::vector<std::string> m_wearFlags;
    int m_weight;

   public:
    ObjectEntity(std::vector<std::string>& attribute, unsigned int cost,
                 std::vector<std::string>& extra, unsigned int objectTypeId,
                 std::string& itemType, std::vector<std::string>& keywords,
                 std::string& longDesc, std::string& shortDesc,
                 std::vector<std::string>& wearFlags, int weight);
};

#endif
