#include <string>
#include <vector>

#include "MoveAction.h"

void MoveAction::execute() {}

MoveAction::MoveAction(const std::string& entityPerformingAction,
                       const std::vector<std::string>* entitiesBeingActedUpon,
                       const mudserver::gamemanager::GameManager& gameManager)
    : Action(entityPerformingAction, entitiesBeingActedUpon, gameManager) {}
