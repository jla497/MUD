Gibanica MUD README
===================

## Packages Needed

You may need to install these packages

- boost
- libyaml-cpp-dev

### gtest/gmock

These are included as submodules, so they need to be initialized with
```
git submodule init && git submodule update
```

## Usage

Server:
- ./mudserver < config_file_path >

Client:
- ./chatclient < config_file_path >

< config_file_path > = "config.yaml"

## Actions Supported
- identify < username > < password > (logs player in, creates new player if username doesn't already exist)
- say 
- move 
- attack (attack player by indicating shortDesc)
- look (at the room)
- swap < character > (swap's the player's character with < character >)
- save (saves the state of the game to disk)
- halt (halt's the game server and saves to disk)
- program --help (gives help!)
- program --modify < npc id > --gold < number > (adds gold to npc)
- program --modify < npc id > --experience < number > (adds exp to npc)


