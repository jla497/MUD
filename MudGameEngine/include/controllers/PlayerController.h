//
// Created by jla497 on 13/03/18.
//

#ifndef ADVENTURE2018_PLAYERCONTROLLER_H
#define ADVENTURE2018_PLAYERCONTROLLER_H

#include "controllers/CharacterController.h"
#include "Event.h"

class PlayerController : public CharacterController {

  public:
    using CharacterController::CharacterController;
    void update() override;
};

#endif // ADVENTURE2018_PLAYERCONTROLLER_H
