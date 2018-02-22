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
- ./mudserver <config_file_path>

Client:
- ./chatclient <config_file_path>

<config_file_path> = "config.yaml"

## Actions Supported
- say 
- move 
- attack (attack player by indicating shortDesc)
- look (at the room)

