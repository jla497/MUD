//
// Created by jla497 on 25/03/18.
//
#include "observe/ActionObserver.h"
#include "actions/Action.h"
#include "actions/AttackAction.h"
#include "actions/MoveAction.h"
#include "actions/SayAction.h"
#include "controllers/CharacterController.h"
#include "entities/CharacterEntity.h"
#include "gamemanager/GameState.h"
#include <boost/algorithm/string.hpp>

ActionObserver::ActionObserver(std::vector<CharacterController *> *controllers,
                               GameState *state) {
    for (auto &controller : *controllers) {
        assert(controller->getCharacter() != nullptr);
        characterToControllers[controller->getCharacter()] = controller;
    }
    gameState = state;
}

void ActionObserver::receiveEvent(Action *source) { source->accept(this); }

void ActionObserver::visit(AttackAction *action) {
    auto characters = CharactersInRoom(action);
    if (characters.size() < 1) {
        return;
    }
    auto args = action->getArgs();
    if (args.size() < 1) {
        return;
    }

    auto nameOfTarget = args[0];

    // see if the target is in the same room as the attacker
    for (auto currentEntity : characters) {

        auto shortDescOfCurrentCharacter = currentEntity->getShortDesc();
        if (boost::to_lower_copy(shortDescOfCurrentCharacter) ==
            boost::to_lower_copy(nameOfTarget)) {

            auto itr = characterToControllers.find(currentEntity);
            if (itr != characterToControllers.end()) {

                auto sender = action->getPerformingEntity();
                auto e =
                    event::Event{sender, event::EventType::startcombat, {}};

                auto controller = itr->second;
                controller->passEvent(e);
                return;
            }
        }
    }
}

void ActionObserver::visit(MoveAction *action) {
    auto characters = CharactersInRoom(action);
    if (characters.size() < 1) {
        return;
    }

    auto sender = action->getPerformingEntity();
    for (auto currentEntity : characters) {
        auto itr = characterToControllers.find(currentEntity);
        if (itr != characterToControllers.end()) {
            auto e = event::Event{sender, event::EventType::interact, {}};

            auto controller = itr->second;
            controller->passEvent(e);
        }
    }
}

void ActionObserver::visit(SayAction *action) {
    auto characters = CharactersInRoom(action);
    if (characters.size() < 1) {
        return;
    }

    auto sender = action->getPerformingEntity();
    auto args = action->getArgs();
    for (auto currentEntity : characters) {
        auto itr = characterToControllers.find(currentEntity);
        if (itr != characterToControllers.end()) {
            auto e = event::Event{sender, event::EventType::say, args};

            auto controller = itr->second;
            controller->passEvent(e);
        }
    }
}

std::vector<CharacterEntity *>
ActionObserver::CharactersInRoom(Action *action) {
    auto sender = action->getPerformingEntity();
    std::vector<CharacterEntity *> characters{};

    auto room = gameState->getCharacterLocation(*sender);
    if (!room) {
        return characters;
    }

    //--get ids of characters in the attackers room
    auto IDsOfCharactersInRoom = gameState->getCharactersInRoom(room);
    if (IDsOfCharactersInRoom.empty()) {
        return characters;
    }

    // see if the target is in the same room as the attacker
    for (auto characterID : IDsOfCharactersInRoom) {
        if (characterID == sender->getEntityId()) {
            continue;
        }

        auto currentEntity = gameState->getCharacterFromLUT(characterID);
        if (!currentEntity)
            return characters;

        characters.push_back(currentEntity);
    }

    return characters;
}
