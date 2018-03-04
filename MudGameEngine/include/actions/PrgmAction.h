#ifndef PRGMACTION_H
#define PRGMACTION_H

#include <boost/algorithm/string.hpp>
#include <string>
#include <type_traits>
#include <unordered_map>

#include "Action.h"
#include "gamemanager/GameManager.h"
#include "logging.h"
#include "resources/PlayerCharacterDefaults.h"
#include "resources/commands.h"
#include <vector>

/**
 * The Program Action class defines the behavior for when a admin creates a
 * character
 */

class PrgmAction : public Action {
    enum class PrgmKeyword {
        undefined,
        npc,
        pc,
        object,
        name,
        armor,
        damage,
        description,
        exp,
        gold,
        hit,
        shortdesc,
        level,
        thac0,
        actions
    };

  public:
    class PrgmParser {

        using OptValMap = std::unordered_map<std::string, std::string>;

      public:
        PrgmParser() = default;

        void addArgument(std::string arg, std::string info) {
            optionLookup[arg] = info;
        };

        std::string printHelp();

        std::string getArgument(std::string arg);

        OptValMap parseOptValPairs(std::vector<std::string> args);

      private:
        static OptValMap optionLookup;
        OptValMap optionValuePairs;
    };

    static std::unordered_map<std::string, PrgmKeyword> prgmLookup;

    void prgmNpc();
    void prgmObject();

  public:
    using Action::Action;
    void execute_impl();

  protected:
    std::string description() const override { return u8"Program action"; }
    PrgmAction *clone();
};
#endif