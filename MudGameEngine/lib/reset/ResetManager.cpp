//
// Created by jla497 on 01/03/18.
//

#include <cassert>

#include "gamemanager/GameState.h"
#include "reset/ResetManager.h"

ResetManager::ResetManager(const std::vector<Reset> &resets) : resets(resets) {}

void ResetManager::applyResets(mudserver::gamemanager::GameState *state) {
    auto factory = state->getFactory();
    std::vector<UniqueId> previousNpcIds{};
    for (auto &reset : resets) {

        if (reset.getAction() == "object") {
            auto objectId = reset.getTypeId();
            auto roomId = reset.getRoomId();
            auto object = factory.buildObject(objectId);
            auto room = state->getRoomFromLUT(roomId);
            room->addObject(object);
        }

        if (reset.getAction() == "npc") {

            auto npcTypeId = reset.getTypeId();
            auto roomId = reset.getRoomId();
            auto limit = reset.getLimit();
            auto numOfExistingNpcs =
                getNumOfNpcsInRoom(roomId, npcTypeId, state);
            limit = limit - numOfExistingNpcs;
            if (limit <= 0) {
                continue;
            }

            assert(npcTypeId > 0 && roomId > 0 && limit > 0);
            auto entities = populateNpcs(limit, npcTypeId, state);
            // add characters to the room
            addNpcsToRooms(entities, roomId, state);

            previousNpcIds.clear();
            for (auto &entity : entities) {
                previousNpcIds.push_back(entity.getEntityId());
            }
        }

        if (reset.getAction() == "give") {
            auto objectId = reset.getTypeId();
            auto object = factory.buildObject(objectId);
            equipNpcs(object, previousNpcIds, state);
        }
    }
}

std::vector<CharacterEntity>
ResetManager::populateNpcs(int limit, int npcTypeId,
                           mudserver::gamemanager::GameState *state) {
    std::vector<CharacterEntity> entities;
    auto factory = state->getFactory();
    for (auto i = 0; i < limit; i++) {
        auto npc = factory.buildNpc(npcTypeId);
        entities.push_back(npc);
    }

    return entities;
}

void ResetManager::equipNpcs(const ObjectEntity &object,
                             std::vector<UniqueId> &NpcIds,
                             mudserver::gamemanager::GameState *state) {
    for (auto &npcId : NpcIds) {
        auto entity = state->getCharacterFromLUT(npcId);
        entity->addObject(object);
    }
}

void ResetManager::addNpcsToRooms(std::vector<CharacterEntity> &entities,
                                  int roomId,
                                  mudserver::gamemanager::GameState *state) {
    for (auto &npc : entities) {
        try {
            state->addCharacter(npc, roomId);
        } catch (const std::range_error &e) {
            // TODO log it
        }
    }
}

int ResetManager::getNumOfNpcsInRoom(int roomId, int npcTypeId,
                                     mudserver::gamemanager::GameState *state) {
    auto room = state->getRoomFromLUT(roomId);
    auto characterIds = state->getCharactersInRoom(room);
    int numOfExistingNpcs = 0;
    for (auto id : characterIds) {
        auto character = state->getCharacterFromLUT(id);
        auto thisId = character->getTypeId();
        if (thisId == (unsigned int)npcTypeId) {
            numOfExistingNpcs++;
        }
    }

    return numOfExistingNpcs;
}