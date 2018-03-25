#ifndef LOOKACTION_H
#define LOOKACTION_H

#include "Action.h"
#include "gamemanager/GameManager.h"

/**
 * The LookAction class defines the behavior for when an player 'looks' at
 * something. Can only look at one thing at a time.
 * 		Look with no arguments assume looking at the room itself
 * 		Look with one argument would let player look at that object
 *  	Look with more than one argument would return an error?
 */
class LookAction : public Action {

    std::string
    getDescriptionOfCharactersInRoom(RoomEntity *characterCurrentRoom);
    std::string getDescriptionOfObjectsInRoom(RoomEntity *characterCurrentRoom);
    std::string
    getDescriptionOfTargetCharacter(std::string nameOfTarget,
                                    RoomEntity *characterCurrentRoom);
    std::string
    getStringFromStringVector(std::vector<std::string> stringVector);

  public:
    using Action::Action;
    void execute_impl() override;
    std::unique_ptr<Action> clone() const override;

  protected:
    std::string description() const override { return u8"Look action"; }
    const unsigned int MAX_LOOK_ARGS = 1;
};
#endif