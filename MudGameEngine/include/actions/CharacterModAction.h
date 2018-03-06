#ifndef CHARACTERMODACTION_H
#define CHARACTERMODACTION_H

#include "Action.h"
#include "gamemanager/GameManager.h"

/**
 * The CharacterModAction allows players to modify their characters
 */
class CharacterModAction : public Action {
  public:
    using Action::Action;
    void execute_impl() override;

  protected:
    std::string description() const override {
        return u8"Character mod action";
    }
    CharacterModAction *clone() override;
    void showCharacterName(const CharacterEntity &character);
};
#endif // CHARACTERMODACTION_H