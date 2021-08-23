#include <limits.h>
#include "gtest/gtest.h"
#include "../src/Client/ClientResponse.h"

class ClientResponseTest : public ::testing::Test {
protected:
  virtual void SetUp() override {
  }

  virtual void TearDown() override {
  }
public:
  const int total_tasks_num = 20;
  const int c_serial_num = 512;
  const int s_serial_num = 19700101;
};


TEST_F(ClientResponseTest, nextCommandForServer) {

  const int task = 10;

  Message from_server(Message::ACTION::RESPONSE, Message::STATUS::ACCEPTED, task, s_serial_num);

  ClientResponse c_response(c_serial_num, total_tasks_num, task);
  c_response.Processing(&from_server);

  auto to_server = c_response.GetResponce();

  Message correct(Message::ACTION::COMMAND, Message::STATUS::ACCEPTED, task + 1, c_serial_num);

  EXPECT_EQ(correct.action, to_server.action);
  EXPECT_EQ(correct.status, to_server.status);
  EXPECT_EQ(correct.task,   to_server.task);
  EXPECT_EQ(correct.sender, to_server.sender);
}

TEST_F(ClientResponseTest, lastCommandForServer) {

  Message from_server(Message::ACTION::RESPONSE, Message::STATUS::ACCEPTED, total_tasks_num - 1, s_serial_num);

  ClientResponse c_response(c_serial_num, total_tasks_num, total_tasks_num - 1);
  c_response.Processing(&from_server);

  auto to_server = c_response.GetResponce();

  Message correct(Message::ACTION::COMMAND, Message::STATUS::DONE, total_tasks_num, c_serial_num);

  EXPECT_EQ(correct.action, to_server.action);
  EXPECT_EQ(correct.status, to_server.status);
  EXPECT_EQ(correct.task,   to_server.task);
  EXPECT_EQ(correct.sender, to_server.sender);
}

TEST_F(ClientResponseTest, passCommandForBusyServer) {

  const int task = 10;

  Message from_server(Message::ACTION::RESPONSE, Message::STATUS::BUSY, task, s_serial_num);

  ClientResponse c_response(c_serial_num, total_tasks_num, task);
  c_response.Processing(&from_server);

  auto to_server = c_response.GetResponce();

  Message correct(Message::ACTION::RESPONSE, Message::STATUS::ACCEPTED, task, c_serial_num);

  EXPECT_EQ(correct.action, to_server.action);
  EXPECT_EQ(correct.status, to_server.status);
  EXPECT_EQ(correct.task,   to_server.task);
  EXPECT_EQ(correct.sender, to_server.sender);
}

TEST_F(ClientResponseTest, getCommandFromServer) {

  const int task = 5;

  Message from_server(Message::ACTION::COMMAND, Message::STATUS::ACCEPTED, task, s_serial_num);

  ClientResponse c_response(c_serial_num, total_tasks_num, task);
  c_response.Processing(&from_server);

  auto to_server = c_response.GetResponce();

  Message correct(Message::ACTION::RESPONSE, Message::STATUS::ACCEPTED, task, c_serial_num);

  EXPECT_EQ(correct.action, to_server.action);
  EXPECT_EQ(correct.status, to_server.status);
  EXPECT_EQ(correct.task,   to_server.task);
  EXPECT_EQ(correct.sender, to_server.sender);
}


TEST_F(ClientResponseTest, busyServer) {

  const int task = 5;

  Message from_server(Message::ACTION::RESPONSE, Message::STATUS::BUSY, task, s_serial_num);

  ClientResponse c_response(c_serial_num, total_tasks_num, task);
  c_response.Processing(&from_server);

  auto to_server = c_response.GetResponce();

  Message correct(Message::ACTION::RESPONSE, Message::STATUS::ACCEPTED, task, c_serial_num);

  EXPECT_EQ(correct.action, to_server.action);
  EXPECT_EQ(correct.status, to_server.status);
  EXPECT_EQ(correct.task,   to_server.task);
  EXPECT_EQ(correct.sender, to_server.sender);
}

TEST_F(ClientResponseTest, busyClient) {

  const int task = 5;

  Message from_server(Message::ACTION::RESPONSE, Message::STATUS::BUSY, task, s_serial_num);

  ClientResponse c_response(c_serial_num, total_tasks_num, task);
  c_response.SetStatus(Message::STATUS::BUSY);
  c_response.Processing(&from_server);

  auto to_server = c_response.GetResponce();

  Message correct(Message::ACTION::RESPONSE, Message::STATUS::BUSY, task, c_serial_num);

  EXPECT_EQ(correct.action, to_server.action);
  EXPECT_EQ(correct.status, to_server.status);
  EXPECT_EQ(correct.task,   to_server.task);
  EXPECT_EQ(correct.sender, to_server.sender);
}