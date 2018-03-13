//
// Created by jla497 on 11/03/18.
//
#include "controllers/AiController.h"
#include "states/IState.h"

void AiController::update() {
    current->update();
}
