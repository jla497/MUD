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
    ObjectEntity(std::vector<std::string>& attributes, unsigned int cost,
                 std::vector<std::string>& descExtra,
                 std::vector<std::string>& keywordsExtra,
                 unsigned int objectTypeId, std::string& itemType,
                 std::vector<std::string>& keywords,
                 std::vector<std::string>& longDesc, std::string& shortDesc,
                 std::vector<std::string>& wearFlags, int weight);

    // Need to change this to somehow give a different one
    // each time
    std::vector<std::string> getAttributes() const;

    unsigned int getCost() const;

    unsigned int getObjectTypeId() const;

    std::string getItemType() const;

    std::vector<std::string> getKeywords() const;

    std::vector<std::string> getLongDesc() const;

    std::string getShortDesc() const;

    std::vector<std::string> getWearFlags() const;

    int getWeight() const;

    std::vector<std::string> getExtraKeyword() const;

    std::vector<std::string> getExtraDesc() const;
};

#endif
