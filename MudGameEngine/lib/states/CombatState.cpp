//
// Created by jla497 on 25/03/18.
//

//
// Created by jla497 on 13/03/18.
//

#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>

#include "states/CombatState.h"

namespace state{

    using Tokenizer = boost::tokenizer<boost::char_separator<char>>;

//for each action
//if attack action. auto nameOfAttackTarget = boost::join(actionArguments, " ");
//get attacker

//if say action. auto see if recipient is you. find speaker


    void CombatState::update() {
        //check if character dies. If true, return
        auto combatComponent = entity->getCombatComponent();
        if (combatComponent->isCharacterDead() == true) {
            //remove controller from controller queue
            auto e = event::Event{ nullptr,
                                   event::EventType::died_self,
                                   {}
                                 };
            controller->passEvent(e);
            return;
        }

        auto e = controller->getEvent();
        switch(e.getType()) {
            case event::EventType::startcombat: {
                auto newEntity = e.getEntity();
                targetEntity = newEntity;
                std::cout<<"in combatstate..."<<std::endl;
                auto cmd = "attack "+newEntity->getShortDesc();
                controller->setCmdString(cmd);
                break;
            }

            case event::EventType::undefined: {
                std::cout<<"combatstate undefined event..."<<std::endl;
                if(targetEntity != nullptr){
                    //check if anyone is still in room, if not pass alone event
                    auto room = state->getCharacterLocation(*entity);
                    auto chIds = state->getCharactersInRoom(room);
                    for (auto id : chIds) {
                        auto character = state->getCharacterFromLUT(id);
                        if(character->getEntityId() == targetEntity->getEntityId()){
                            auto cmd = "attack "+targetEntity->getShortDesc();
                            controller->setCmdString(cmd);
                            return;
                        }
                    }

                }
                std::cout<<"lin 65"<<std::endl;
                //attacker no longer in room, can either create pursue state. But too much work
                auto e = event::Event{ nullptr,
                                       event::EventType::endcombat,
                                       {}
                };
                controller->passEvent(e);
                break;
            }

            default: {
                //do nothing
            }
        }

        return;
    }

    void CombatState::enter(){};
    void CombatState::exit(){};
    StateType CombatState::getType() {
        return StateType::combat;
    }
}