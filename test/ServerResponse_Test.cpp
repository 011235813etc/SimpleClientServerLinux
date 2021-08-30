#include <limits.h>
#include "gtest/gtest.h"
#include "../src/Server/ServerResponse.h"

class ServerResponseTest : public ::testing::Test {
protected:
  virtual void SetUp() override {
  }

  virtual void TearDown() override {
  }
public:
  const int total_tasks_num = 20;
  const int s_serial_num = 512;
  const int c_serial_num = 19700101;
};


TEST_F(ServerResponseTest, nextCommandForClient) {

  const int task = 10;

  Message from_client(Message::ACTION::RESPONSE, Message::STATUS::DONE, task, c_serial_num);

  ServerResponse s_response(s_serial_num);
  s_response.SaveCommand(task + 1);
  s_response.SaveCommand(task + 2);
  s_response.SetCommandsLoadComplete(true);
  s_response.Processing(&from_client);

  auto to_client = s_response.GetResponce();

  Message correct(Message::ACTION::COMMAND, Message::STATUS::READY, task + 1, s_serial_num);

  EXPECT_EQ(correct.action, to_client.action);
  EXPECT_EQ(correct.status, to_client.status);
  EXPECT_EQ(correct.task,   to_client.task);
  EXPECT_EQ(correct.sender, to_client.sender);
}

TEST_F(ServerResponseTest, passCommandForBusyClient) {

  const int task = 10;

  Message from_client(Message::ACTION::RESPONSE, Message::STATUS::BUSY, task, c_serial_num);

  ServerResponse s_response(s_serial_num);
  s_response.SaveCommand(task);
  s_response.SaveCommand(task + 1);
  s_response.Processing(&from_client);

  auto to_client = s_response.GetResponce();

  Message correct(Message::ACTION::RESPONSE, Message::STATUS::ACCEPTED, task, s_serial_num);

  EXPECT_EQ(correct.action, to_client.action);
  EXPECT_EQ(correct.status, to_client.status);
  EXPECT_EQ(correct.task,   to_client.task);
  EXPECT_EQ(correct.sender, to_client.sender);
}

TEST_F(ServerResponseTest, getCommandFromClient) {

  const int task = 5;

  Message from_client(Message::ACTION::COMMAND, Message::STATUS::ACCEPTED, task, c_serial_num);

  ServerResponse s_response(s_serial_num);
  s_response.Processing(&from_client);

  auto to_client = s_response.GetResponce();

  Message correct(Message::ACTION::RESPONSE, Message::STATUS::ACCEPTED, task, s_serial_num);

  EXPECT_EQ(correct.action, to_client.action);
  EXPECT_EQ(correct.status, to_client.status);
  EXPECT_EQ(correct.task,   to_client.task);
  EXPECT_EQ(correct.sender, to_client.sender);
}

