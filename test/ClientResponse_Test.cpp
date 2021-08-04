#include <limits.h>
#include "gtest/gtest.h"
#include "../src/Client/ClientResponse.h"

class ClientResponseTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
  }

  virtual void TearDown() {
    // Code here will be called immediately after each test
    // (right before the destructor).
  }
};


TEST_F(ClientResponseTest, twoValues) {
  const int task = 1;
  int client_serial_number = 512;

  Message from_server(Message::ACTION::RESPONSE, Message::STATUS::BUSY, task, 19700101);

  ClientResponse reply(client_serial_number, 2);
  reply.Processing(&from_server, task, Message::STATUS::READY);
  auto to_server = reply.GetResponce();

  Message correct(Message::ACTION::RESPONSE, Message::STATUS::ACCEPTED, task, client_serial_number);

  EXPECT_EQ(correct.action, to_server.action);
  EXPECT_EQ(correct.status, to_server.status);
  EXPECT_EQ(correct.task,   to_server.task);
  EXPECT_EQ(correct.sender, to_server.sender);
}

