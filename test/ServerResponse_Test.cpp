#include <limits.h>
#include "gtest/gtest.h"
#include "../src/Server/ServerResponse.h"
#include <memory>

class ServerResponseTest : public ::testing::Test {

  const int server_number = 512;
  const int client_number = 19700101;
protected:
  std::unique_ptr<ServerResponse> s_response;

  virtual void SetUp() override {
    s_response = std::unique_ptr<ServerResponse>(new ServerResponse(server_number));
  }

  virtual void TearDown() override {

  }
public:
  Message GetCorrect(ACTION a, STATUS s, int t) {
    return Message(a, s, t, server_number);
  }

  Message FromClient(ACTION a, STATUS s, int t) {
    return Message(a, s, t, client_number);
  }

};

////////////////////////////////////////////////////////////////////////////////

TEST_F(ServerResponseTest, FromClientCommandDone) {

  const int tasks = 1;
  auto from_client = FromClient(ACTION::COMMAND, STATUS::DONE, tasks);
  s_response->Processing(&from_client);

  auto result = s_response->GetResponce();
  auto correct = GetCorrect(ACTION::RESPONSE, STATUS::DONE, tasks);

  EXPECT_EQ(correct, result);
  EXPECT_EQ(s_response->IsAcceptingCommands(), false);
  EXPECT_EQ(s_response->GetSavedCommandsCount(), 1);
}

TEST_F(ServerResponseTest, FromClientCommandError) {

  int task = 5;
  auto from_client = FromClient(ACTION::COMMAND, STATUS::ERROR, task);
  
  s_response->SaveCommand(task);
  s_response->SaveCommand(++task);
  s_response->SaveCommand(++task);
  s_response->SaveCommand(++task);
  s_response->Processing(&from_client);

  auto result = s_response->GetResponce();
  auto correct = GetCorrect(ACTION::RESPONSE, STATUS::DONE, Message::launch_task);

  EXPECT_EQ(correct, result);  
  EXPECT_EQ(s_response->GetSavedCommandsCount(), 0);
}

TEST_F(ServerResponseTest, FromClientCommandReadyInit) {

  const int task = Message::launch_task;
  auto from_client = FromClient(ACTION::COMMAND, STATUS::READY, task);
  s_response->Processing(&from_client);

  auto result = s_response->GetResponce();
  auto correct = GetCorrect(ACTION::RESPONSE, STATUS::READY, task);

  EXPECT_EQ(correct, result);
  EXPECT_EQ(s_response->IsAcceptingCommands(), true);
  EXPECT_EQ(s_response->GetSavedCommandsCount(), 0);
}

TEST_F(ServerResponseTest, FromClientCommandReadyNext) {

  const int task = 100;
  auto from_client = FromClient(ACTION::COMMAND, STATUS::READY, task);
  s_response->Processing(&from_client);

  auto result = s_response->GetResponce();
  auto correct = GetCorrect(ACTION::RESPONSE, STATUS::ACCEPTED, task);

  EXPECT_EQ(correct, result);
  EXPECT_EQ(s_response->IsAcceptingCommands(), true);
  EXPECT_EQ(s_response->GetSavedCommandsCount(), 1);
}

TEST_F(ServerResponseTest, FromClientCommandBusy) {

  const int task = 5;
  auto from_client = FromClient(ACTION::COMMAND, STATUS::BUSY, task);
  s_response->Processing(&from_client);

  EXPECT_EQ(s_response->IsNeedResponse(), false);
}

TEST_F(ServerResponseTest, FromClientCommandAccepted) {

  const int task = 5;
  auto from_client = FromClient(ACTION::COMMAND, STATUS::ACCEPTED, task);
  s_response->Processing(&from_client);

  EXPECT_EQ(s_response->IsNeedResponse(), false);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(ServerResponseTest, FromClientResponseDoneAcceptingCmd) {

  const int tasks = 1;
  auto from_client = FromClient(ACTION::RESPONSE, STATUS::DONE, tasks);
  s_response->SetAcceptingCommands(true);
  s_response->Processing(&from_client);

  EXPECT_EQ(s_response->IsNeedResponse(), false);
}

TEST_F(ServerResponseTest, FromClientResponseDoneNotAcceptingCmdWithCmd) {

  int task = 1;
  auto from_client = FromClient(ACTION::RESPONSE, STATUS::DONE, task);
  s_response->SaveCommand(++task);
  s_response->Processing(&from_client);

  auto result = s_response->GetResponce();
  auto correct = GetCorrect(ACTION::COMMAND, STATUS::READY, task);

  EXPECT_EQ(correct, result);
}

TEST_F(ServerResponseTest, FromClientResponseDoneNotAcceptingCmdNoCmd) {

  const int tasks = 1;
  auto from_client = FromClient(ACTION::RESPONSE, STATUS::DONE, tasks);
  s_response->Processing(&from_client);

  auto result = s_response->GetResponce();
  auto correct = GetCorrect(ACTION::RESPONSE, STATUS::DONE, Message::done_task);

  EXPECT_EQ(correct, result);
  EXPECT_EQ(s_response->GetSavedCommandsCount(), 0);
}

TEST_F(ServerResponseTest, FromClientResponseError) {

  const int tasks = 1;
  auto from_client = FromClient(ACTION::RESPONSE, STATUS::ERROR, tasks);
  s_response->Processing(&from_client);

  EXPECT_EQ(s_response->IsNeedResponse(), false);
}

TEST_F(ServerResponseTest, FromClientResponseReadyAcceptingCmd) {

  const int tasks = 1;
  auto from_client = FromClient(ACTION::RESPONSE, STATUS::READY, tasks);
  s_response->SetAcceptingCommands(true);
  s_response->Processing(&from_client);

  auto result = s_response->GetResponce();
  auto correct = GetCorrect(ACTION::RESPONSE, STATUS::BUSY, Message::launch_task);

  EXPECT_EQ(correct, result);
}

TEST_F(ServerResponseTest, FromClientResponseDoneReadyAcceptingCmdWithCmd) {

  int task = 1;
  auto from_client = FromClient(ACTION::RESPONSE, STATUS::READY, task);
  s_response->SaveCommand(++task);
  s_response->Processing(&from_client);

  auto result = s_response->GetResponce();
  auto correct = GetCorrect(ACTION::COMMAND, STATUS::READY, task);

  EXPECT_EQ(correct, result);
}

TEST_F(ServerResponseTest, FromClientResponseReadyNotAcceptingCmdNoCmd) {

  const int tasks = 1;
  auto from_client = FromClient(ACTION::RESPONSE, STATUS::READY, tasks);
  s_response->Processing(&from_client);

  auto result = s_response->GetResponce();
  auto correct = GetCorrect(ACTION::RESPONSE, STATUS::DONE, Message::done_task);

  EXPECT_EQ(correct, result);
  EXPECT_EQ(s_response->GetSavedCommandsCount(), 0);
}

TEST_F(ServerResponseTest, FromClientResponseBusy) {

  const int tasks = 1;
  auto from_client = FromClient(ACTION::RESPONSE, STATUS::BUSY, tasks);
  s_response->Processing(&from_client);

  EXPECT_EQ(s_response->IsNeedResponse(), false);
}

TEST_F(ServerResponseTest, FromClientResponseAccepted) {

  const int tasks = 1;
  auto from_client = FromClient(ACTION::RESPONSE, STATUS::ACCEPTED, tasks);
  s_response->Processing(&from_client);

  EXPECT_EQ(s_response->IsNeedResponse(), false);
}