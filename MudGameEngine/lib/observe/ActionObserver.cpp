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

ActionObserver:: ActionObserver(std::vector<CharacterController*> *controllers, GameState *state ){
    for(auto& controller : *controllers) {
        assert(controller->getCharacter() != nullptr);
        characterToControllers[controller->getCharacter()] = controller;
    }
    gameState = state;
}

void ActionObserver::receiveEvent(Action *source) {
    source->accept(this);
}

void ActionObserver::visit(AttackAction* action) {
    auto attacker = action->getPerformingEntity();
    auto args = action->getArgs();
    if (args.size() < 1) {
        return;
    }

    auto room = gameState->getCharacterLocation(*attacker);
    if (!room) {
        return;
    }

    //--get ids of characters in the attackers room
    auto IDsOfCharactersInRoom =
            gameState->getCharactersInRoom(room);
    if (IDsOfCharactersInRoom.empty()) {
        return;
    }

    auto attackerId = attacker->getEntityId();
    auto nameOfAttackTarget = args[0];

    // see if the target is in the same room as the attacker
    for (auto characterID : IDsOfCharactersInRoom) {
        auto currentEntity = gameState->getCharacterFromLUT(characterID);
        if (!currentEntity)
            return;

        auto shortDescOfCurrentCharacter = currentEntity->getShortDesc();
        if (boost::to_lower_copy(shortDescOfCurrentCharacter) ==
            boost::to_lower_copy(nameOfAttackTarget)){

            auto itr = characterToControllers.find(currentEntity);
            if(itr != characterToControllers.end()) {
                auto e = event::Event{
                        attacker,
                        event::EventType::startcombat,
                        {}
                };

                auto controller = itr->second;
                controller->passEvent(e);
                return;
            }
        }
    }
}

void ActionObserver::visit(MoveAction* action){
}

void ActionObserver::visit(SayAction* action){
}
