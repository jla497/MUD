#include "ConnectionManager.h"
#include "gtest/gtest.h"
namespace {
// To use a test fixture, derive a class from testing::Test.
class ConnectionManTest : public testing::Test {
protected:  // You should make the members protected s.t. they can be
  // accessed from sub-classes.

  // virtual void SetUp() will be called before each test is run.  You
  // should define it if you need to initialize the variables.
  // Otherwise, this can be skipped.
  virtual void SetUp() {
    Message m1{Connection{39985500},"msg1"};
    Message m2{Connection{39985499},"msg2"};
    Message m3{Connection{39985600},"msg3"};
    incoming.push_back(m1);
    incoming.push_back(m2);
    incoming.push_back(m3);
    
}

// virtual void TearDown() will be called after each test is run.
// You should define it if there is cleanup work to do.  Otherwise,
// you don't have to provide it.

// virtual void TearDown() {
// }

// Declares the variables your tests want to use.
ConnectionManager m_manager;
std::deque<Message> incoming;
};

// When you have a test fixture, you define a test using TEST_F
// instead of TEST.

// TEST_F(ConnectionManTest, AddConnectionContainer) {
//   ASSERT_NO_THROW(m_manager->addConnection(Connection{400033}));

//   ASSERT_NO_THROW(m_manager->addConnection(Connection{302348}));
// }

TEST_F(ConnectionManTest, TestProtocolInConnectionContainer) {
  Connection c{39990000};
  auto container = std::make_unique<ConnectionContainer>(c);
  std::string str("");
  ASSERT_NO_THROW(container->receiveFromServer(str));

  auto cmpStr = container->sendToGameManager();
  EXPECT_EQ("", cmpStr);
  // std::cout<<container->getOutBuffer()<<std::endl;
}

TEST_F(ConnectionManTest, SendFromConnectionManagerToConnectionContainer) {
  
  ASSERT_NO_THROW(m_manager.rxFromServer(incoming));
}

// Tests Dequeue().
// TEST_F(ConnectionManTest, SendMessagesToGameManager) {
//   MsgsPtr messages = m_manager.send2GameManager();

//   const auto& msg = messages->at(0);
//   // std::cout<<msg->text<<std::endl;
//    EXPECT_EQ("msg1", "msg1");
// }
}  // namespace