#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

namespace mudserver {
namespace gamemanager {
class GameManager;
}
} // namespace mudserver

namespace mudserver {
namespace gamemanager {

class Administrator {

  public:
    void accessGameManager(mudserver::gamemanager::GameManager &manager);
};
} // namespace gamemanager
} // namespace mudserver

#endif