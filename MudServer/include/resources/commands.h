
#ifndef ADVENTURE2018_COMMANDS_H
#define ADVENTURE2018_COMMANDS_H

namespace mudserver {
namespace resources {
namespace commands {

constexpr const char *UNDEFINED = u8"undefined";
constexpr const char *SAY = u8"say";
constexpr const char *LOOK = u8"look";
constexpr const char *MOVE = u8"move";
constexpr const char *ATTACK = u8"attack";
constexpr const char *PROGRAM = u8"program";
constexpr const char *NPC = u8"npc";
constexpr const char *PC = u8"pc";
constexpr const char *OBJECT = u8"object";
constexpr const char *CNAME = u8"name";
constexpr const char *CARMOR = u8"armor";
constexpr const char *CDAMAGE = u8"damage";
constexpr const char *CDESCRIPTION = u8"description";
constexpr const char *CEXP = u8"exp";
constexpr const char *CGOLD = u8"gold";
constexpr const char *CHIT = u8"hit";
constexpr const char *CID = u8"id";
constexpr const char *CKEYWORDS = u8"keywords";
constexpr const char *CLEVEL = u8"level";
constexpr const char *CLONGDESC = u8"longdesc";
constexpr const char *CSHORTDESC = u8"shortdesc";
constexpr const char *CTHAC0 = u8"thac0";
constexpr const char *CHELP = u8"help";
constexpr const char *CREATE = u8"create";
constexpr const char *MODIFY = u8"modify";
constexpr const char *IDENTIFY = u8"identify";
constexpr const char *SAVE = u8"save";
constexpr const char *TIMED = u8"timed";
constexpr const char *CHARMOD = u8"character";
constexpr const char *HALT = u8"halt";
constexpr const char *SWAP = u8"swap";
constexpr const char *CAST = u8"cast";
constexpr const char *TAKE = u8"take";

} // namespace commands
} // namespace resources
} // namespace mudserver

#endif // ADVENTURE2018_COMMANDS_H
