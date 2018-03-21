//
// Created by jla497 on 11/03/18.
//

#ifndef ADVENTURE2018_AICONTROLLER_H
#define ADVENTURE2018_AICONTROLLER_H

#include <unordered_map>

#include "controllers/CharacterController.h"

class AiController : public CharacterController {

  public:
    using CharacterController::CharacterController;
    void init(GameState *state, CharacterEntity *ent,
              Player *plyer);
    void update() override;
};

#endif // ADVENTURE2018_AICONTROLLER_H
