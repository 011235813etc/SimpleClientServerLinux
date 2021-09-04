#include <limits.h>
#include "gtest/gtest.h"
#include "../src/Client/ClientResponse.h"

class ClientResponseTest : public ::testing::Test {
  const int client_number = 512;
  const int server_number = 19700101;
  const int current_task = 10;
protected:

  std::unique_ptr<ClientResponse> c_response;
  virtual void SetUp() override {
    c_response = std::unique_ptr<ClientResponse>(
      new ClientResponse(client_number, total_tasks_num, current_task));
  }

  virtual void TearDown() override {
  }
public:
  const int total_tasks_num = 20;

  Message GetCorrect(ACTION a, STATUS s, int t) {
    return Message(a, s, t, server_number);
  }

  Message FromServer(ACTION a, STATUS s, int t) {
    return Message(a, s, t, client_number);
  }
};

TEST_F(ClientResponseTest, busyClient) {

  const int task = 5;

  auto from_server = FromServer(ACTION::RESPONSE, STATUS::BUSY, task);
  c_response->SetStatus(STATUS::BUSY);
  c_response->Processing(&from_server);

  auto result = c_response->GetResponce();
  auto correct = GetCorrect(ACTION::RESPONSE, STATUS::BUSY, task);

  EXPECT_EQ(correct, result);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(ClientResponseTest, FromServerCommandDone) {

  const int task = 1;
  auto from_server = FromServer(ACTION::COMMAND, STATUS::DONE, task);
  c_response->Processing(&from_server);

  EXPECT_EQ(c_response->IsNeedResponse(), false);
}

TEST_F(ClientResponseTest, FromServerCommandError) {

  const int task = 1;
  auto from_server = FromServer(ACTION::COMMAND, STATUS::ERROR, task);
  c_response->Processing(&from_server);

  EXPECT_EQ(c_response->IsNeedResponse(), false);
}

TEST_F(ClientResponseTest, FromServerCommandBusy) {

  const int task = 1;
  auto from_server = FromServer(ACTION::COMMAND, STATUS::BUSY, task);
  c_response->Processing(&from_server);

  EXPECT_EQ(c_response->IsNeedResponse(), false);
}

TEST_F(ClientResponseTest, FromServerCommandAccepted) {

  const int task = 1;
  auto from_server = FromServer(ACTION::COMMAND, STATUS::ACCEPTED, task);
  c_response->Processing(&from_server);

  EXPECT_EQ(c_response->IsNeedResponse(), false);
}

TEST_F(ClientResponseTest, FromServerCommandReady) {

  const int task = 1;
  auto from_server = FromServer(ACTION::COMMAND, STATUS::READY, task);
  c_response->Processing(&from_server);

  auto result = c_response->GetResponce();
  auto correct = GetCorrect(ACTION::RESPONSE, STATUS::ACCEPTED, task);

  EXPECT_EQ(correct, result);
  EXPECT_EQ(c_response->GetStatus(), STATUS::BUSY);
  EXPECT_EQ(c_response->GetTask(), task);
}
////////////////////////////////////////////////////////////////////////////////

TEST_F(ClientResponseTest, FromServerResponseDoneLoadingTasks) {

  const int task = 1;
  auto from_server = FromServer(ACTION::RESPONSE, STATUS::DONE, task);
  c_response->SetLoading(true);
  c_response->Processing(&from_server);

  EXPECT_EQ(c_response->IsNeedResponse(), false);
  EXPECT_EQ(c_response->GetTask(), (int)Message::launch_task);
  EXPECT_EQ(c_response->GetLoading(), false);
}

TEST_F(ClientResponseTest, FromServerResponseDoneTasksDone) {

  const int task = 1;
  auto from_server = FromServer(ACTION::RESPONSE, STATUS::DONE, task);
  c_response->SetLoading(false);
  c_response->Processing(&from_server);

  auto result = c_response->GetResponce();
  auto correct = GetCorrect(ACTION::RESPONSE, STATUS::DONE, Message::done_task);

  EXPECT_EQ(correct, result);
  EXPECT_EQ(c_response->GetStatus(), STATUS::DONE);
  EXPECT_EQ(c_response->GetTask(), (int)Message::done_task);
}

TEST_F(ClientResponseTest, FromServerResponseError) {

  const int task = 1;
  auto from_server = FromServer(ACTION::RESPONSE, STATUS::ERROR, task);
  c_response->Processing(&from_server);

  EXPECT_EQ(c_response->IsNeedResponse(), false);
}

TEST_F(ClientResponseTest, FromServerResponseBusyRepeat) {

  const int task = 1;
  auto from_server = FromServer(ACTION::RESPONSE, STATUS::BUSY, task);
  c_response->Processing(&from_server);

  auto result = c_response->GetResponce();
  auto correct = GetCorrect(ACTION::RESPONSE, STATUS::READY, task);

  EXPECT_EQ(correct, result);
}

TEST_F(ClientResponseTest, FromServerResponseBusyTimeout) {

  const int task = 1;
  auto from_server = FromServer(ACTION::RESPONSE, STATUS::BUSY, task);
  c_response->Processing(&from_server);
  c_response->Processing(&from_server);
  c_response->Processing(&from_server);

  EXPECT_EQ(c_response->IsNeedResponse(), false);
}

TEST_F(ClientResponseTest, FromServerResponseReadyLaunch) {

  const int task = Message::launch_task;
  const int newTask = 0;
  auto from_server = FromServer(ACTION::RESPONSE, STATUS::READY, task);
  c_response->SetTask(Message::launch_task);
  c_response->Processing(&from_server);

  auto result = c_response->GetResponce();
  auto correct = GetCorrect(ACTION::COMMAND, STATUS::READY, newTask);

  EXPECT_EQ(correct, result);
}

TEST_F(ClientResponseTest, FromServerResponseReadyLaunchAnotherCmd) {

  const int task = Message::launch_task;
  auto from_server = FromServer(ACTION::RESPONSE, STATUS::READY, task);
  c_response->Processing(&from_server);

  EXPECT_EQ(c_response->IsNeedResponse(), false);
}

TEST_F(ClientResponseTest, FromServerResponseReadyContinue) {

  const int task = 1;
  auto from_server = FromServer(ACTION::RESPONSE, STATUS::READY, task);
  c_response->Processing(&from_server);

  EXPECT_EQ(c_response->IsNeedResponse(), false);
}

TEST_F(ClientResponseTest, FromServerResponseAcceptedLoading) {

  const int task = Message::launch_task;
  const int newTask = 0;
  auto from_server = FromServer(ACTION::RESPONSE, STATUS::ACCEPTED, task);
  c_response->SetLoading(true);
  c_response->Processing(&from_server);

  auto result = c_response->GetResponce();
  auto correct = GetCorrect(ACTION::COMMAND, STATUS::READY, newTask);

  EXPECT_EQ(correct, result);
}

TEST_F(ClientResponseTest, FromServerResponseAcceptedLoadingLast) {

  const int task = total_tasks_num - 1;
  auto from_server = FromServer(ACTION::RESPONSE, STATUS::ACCEPTED, task);
  c_response->SetLoading(true);
  c_response->Processing(&from_server);

  auto result = c_response->GetResponce();
  auto correct = GetCorrect(ACTION::COMMAND, STATUS::DONE, total_tasks_num);

  EXPECT_EQ(correct, result);
}

TEST_F(ClientResponseTest, FromServerResponseAcceptedNotLoading) {

  const int task = 1;
  auto from_server = FromServer(ACTION::RESPONSE, STATUS::ACCEPTED, task);
  c_response->SetLoading(false);
  c_response->Processing(&from_server);

  EXPECT_EQ(c_response->IsNeedResponse(), false);
}
