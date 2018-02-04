#include "gmock/gmock.h"
#include "connectionmanager/ConnectionManager.h"

class MockConnectionManager : public mudserver::connection::ConnectionManager {
public:
    MockConnectionManager() : ConnectionManager(4000) {}
};