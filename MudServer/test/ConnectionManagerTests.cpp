#include "connectionmanager/ConnectionManager.h"

#include "gtest/gtest.h"

namespace {

  using namespace networking;
  using namespace mudserver::connection;

// To use a test fixture, derive a class from testing::Test.
class ConnectionManTest : public testing::Test {
protected:  // You should make the members protected s.t. they can be
  // accessed from sub-classes.

    ConnectionManager m_manager{4000};
    std::deque<Message> incoming;
    std::vector<mudserver::connection::gameAndUserInterface> gameMsgs;

    void SetUp() override {
    Message m1{Connection{39985500},"msg1"};

    Message m2{Connection{39985499},"msg2"};
    Message m3{Connection{39985600},"msg3"};

    incoming.push_back(m1);
    incoming.push_back(m2);
    incoming.push_back(m3);

      mudserver::connection::gameAndUserInterface reply1{"reply", {39985500}};
      mudserver::connection::gameAndUserInterface reply2{"reply", {39985499}};
      mudserver::connection::gameAndUserInterface reply3{"reply", {39985600}};


    gameMsgs.push_back(reply1);
    gameMsgs.push_back(reply2);
    gameMsgs.push_back(reply3);
  }

// virtual void TearDown() will be called after each test is run.
// You should define it if there is cleanup work to do.  Otherwise,
// you don't have to provide it.

// virtual void TearDown() {
// }

// Declares the variables your tests want to use.

};


TEST_F(ConnectionManTest, TestProtocolInConnectionContainer) {
  Connection c{39990000};
  auto container = std::make_unique<ConnectionContainer>(c);
  std::string str;
  ASSERT_NO_THROW(container->receiveFromServer(str));

  auto cmpStr = container->sendToGameManager();
  EXPECT_EQ("", cmpStr);
  // std::cout<<container->getOutBuffer()<<std::endl;
}

TEST_F(ConnectionManTest, SendFromConnectionManagerToConnectionContainerProtocol) {
  
  ASSERT_NO_THROW(m_manager.rxFromServer(incoming));
}

TEST_F(ConnectionManTest, SendFromConnectionManagerToGameManager) {
 m_manager.rxFromServer(incoming);
  auto msgs = m_manager.sendToGameManager();

  auto itr = std::find_if(msgs.begin(), msgs.end(), findGameAndUserInterface(Connection{39985500}));
  const auto& text = itr->text;
  ASSERT_EQ(text,"msg1\n");

  itr = std::find_if(msgs.begin(), msgs.end(), findGameAndUserInterface(Connection{39985499}));
  const auto& text2 = itr->text;
  ASSERT_EQ(text2,"msg2\n");

  itr = std::find_if(msgs.begin(), msgs.end(), findGameAndUserInterface(Connection{39985600}));
  const auto& text3 = itr->text;
  ASSERT_EQ(text3,"msg3\n");

  }

  TEST_F(ConnectionManTest, SendFromGameManagerToServer) {
    m_manager.rxFromServer(incoming);
    auto msgs = m_manager.sendToGameManager();

    ASSERT_NO_THROW(m_manager.receiveFromGameManager(gameMsgs));
    auto msgsToServer = m_manager.sendToServer();

    for(auto& msg: msgsToServer) {
      ASSERT_EQ("reply\n",msg.text);
    }

  }

// Tests Dequeue().
// TEST_F(ConnectionManTest, SendMessagesToGameManager) {
//   MsgsPtr messages = m_manager.sendToGameManager();

//   const auto& msg = messages->at(0);
//   // std::cout<<msg->text<<std::endl;
//    EXPECT_EQ("msg1", "msg1");
// }
}  // namespace
