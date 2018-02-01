#include <string>
#include <vector>
#include "AttackAction.h"

void AttackAction::execute(){


}

  AttackAction::AttackAction(const std::string& entityPerformingAction,
  		const std::vector<std::string>* entitiesBeingActedUpon,
  		const mudserver::gamemanager::GameManager& gameManager) :
   		entityPerformingAction{entityPerformingAction},
   		entitiesBeingActedUpon{entitiesBeingActedUpon},
   		comment{comment},
   		gameManager{gameManager}{}

   		