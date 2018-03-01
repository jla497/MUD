#include "connectionmanager/ConnectionManager.h"
#include "gmock/gmock.h"

class MockConnectionManager : public mudserver::connection::ConnectionManager {
  public:
    MockConnectionManager() : ConnectionManager(4000) {}
};