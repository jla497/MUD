//
// Created by jla497 on 01/03/18.
//
#include "reset/ResetManager.h"
#include "gamemanager/GameState.h"

ResetManager::ResetManager(std::vector<Reset> resets) : resets(resets) {}

void ResetManager::applyResets(mudserver::gamemanager::GameState *state) {
    auto factory = state->getFactory();

    for (auto it = resets.begin(); it != resets.end(); ++it) {

        if (it->getAction() == "object") {
            auto objectId = it->getTypeId();
            auto roomId = it->getRoomId();
            auto object = factory.buildObject(objectId);
            auto room = state->getRoomFromLUT(roomId);
            room->equipObject(object);
        }

        if (it->getAction() == "npc") {

            auto npcTypeId = it->getTypeId();
            auto roomId = it->getRoomId();
            auto limit = it->getLimit();
            auto numOfExistingNpcs =
                getNumOfNpcsInRoom(roomId, npcTypeId, state);
            limit = limit - numOfExistingNpcs;

            if (limit <= 0) {
                continue;
            }
            assert(npcTypeId > 0 && roomId > 0 && limit > 0);

            auto entities = populateNpcs(limit, npcTypeId, state);

            it++;
            if (it != resets.end()) {
                if (it->getAction() == "give") {
                    auto objectId = it->getTypeId();
                    auto object = factory.buildObject(objectId);
                    equipNpcs(object, entities);
                }
            }

            it--;
            // add characters to the room
            addNpcsToRooms(entities, roomId, state);
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

void ResetManager::equipNpcs(ObjectEntity object,
                             std::vector<CharacterEntity> &entities) {
    for (auto &npc : entities) {
        npc.equipObject(object);
    }
}

void ResetManager::addNpcsToRooms(std::vector<CharacterEntity> &entities,
                                  int roomId,
                                  mudserver::gamemanager::GameState *state) {
    for (auto &npc : entities) {
        try {
            state->addCharacter(npc, roomId);
        } catch (std::exception e) {
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