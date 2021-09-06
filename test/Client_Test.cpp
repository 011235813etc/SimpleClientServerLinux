#include <limits.h>
#include <memory>
#include "gtest/gtest.h"
#include "../src/TaskList/TaskList.h"
#include "../src/Client/Client.h"

#include <string>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;

class ClientTest : public ::testing::Test {
protected:
  virtual void SetUp() override {
  }

  virtual void TearDown() override {
  }
public:
  char* path_test_server1 = "./taske_for_client_server/launch_server_for_test1.sh";
  char* path_test_server2 = "./taske_for_client_server/launch_server_for_test2.sh";
  
  void Compare(Client::type_history& history, Client::type_history& correct) {
    if(history.size() != correct.size()) {
      FAIL() << "received size: " << history.size() << " correct size: " << correct.size(); 
    } else {
      for(unsigned int i = 0; i < history.size(); i++) {
        EXPECT_EQ(history[i].first, correct[i].first); 
        EXPECT_EQ(history[i].second, correct[i].second); 
      }
    }
  }
};



TEST_F(ClientTest, sendCommandsFromClientToServer) {

  system(path_test_server1);

  const uint8_t one_sec = 1;
  std::chrono::seconds dura(one_sec);
  std::this_thread::sleep_for(dura);

  char path[] = "/home/lemongrab/cpp_projects/vs_code/SimpleClientServerLinux/task_list.txt";

	std::unique_ptr<TaskList> t_list(new TaskList(path));
  std::unique_ptr<Client> client = std::unique_ptr<Client>(new Client(ACTION::COMMAND, t_list->size()));

  client->LoadTasks();

  auto history = client->GetHistory();

  vector<pair<Message, TYPE> > correct;
  const int c_sender = client->GetSerialNumber(); 
  const int s_sender = 19700101; 

  correct.push_back(make_pair(Message(ACTION::COMMAND, 
                                      STATUS::READY, 
                                      Message::launch_task, 
                                      c_sender), 
                                      TYPE::SENT));

  correct.push_back(make_pair(Message(ACTION::RESPONSE, 
                                      STATUS::READY, 
                                      Message::launch_task, 
                                      s_sender), 
                                      TYPE::RECEIVED));

  correct.push_back(make_pair(Message(ACTION::COMMAND, 
                                      STATUS::READY, 
                                      0, 
                                      c_sender), 
                                      TYPE::SENT));

  correct.push_back(make_pair(Message(ACTION::RESPONSE, 
                                      STATUS::ACCEPTED, 
                                      0, 
                                      s_sender), 
                                      TYPE::RECEIVED));

  correct.push_back(make_pair(Message(ACTION::COMMAND, 
                                      STATUS::DONE, 
                                      1, 
                                      c_sender), 
                                      TYPE::SENT));

  correct.push_back(make_pair(Message(ACTION::RESPONSE, 
                                      STATUS::DONE, 
                                      1, 
                                      s_sender), 
                                      TYPE::RECEIVED));

  Compare(history, correct);
}

TEST_F(ClientTest, sendCommandsFromServerToClient) {

  system(path_test_server2);

  const uint8_t one_sec = 1;
  std::chrono::seconds dura(one_sec);
  std::this_thread::sleep_for(dura);

  char path[] = "/home/lemongrab/cpp_projects/vs_code/SimpleClientServerLinux/task_list.txt";

	std::unique_ptr<TaskList> t_list(new TaskList(path));
  std::unique_ptr<Client> client = std::unique_ptr<Client>(new Client(ACTION::COMMAND, t_list->size()));


  client->SetEnableHistoryRecording(false);
  client->LoadTasks();
  client->SetEnableHistoryRecording(true);

  client->CommandRequest();
  client->CommandRequest();
  client->CommandRequest();

  auto history = client->GetHistory();

  Client::type_history correct;
  const int c_sender = client->GetSerialNumber(); 
  const int s_sender = 19700101; 
  const int first_task = 0;
  const int second_task = 1;


  correct.push_back(make_pair(Message(ACTION::RESPONSE, 
                                      STATUS::READY, 
                                      Message::launch_task, 
                                      c_sender), 
                                      TYPE::SENT));

  correct.push_back(make_pair(Message(ACTION::COMMAND, 
                                      STATUS::READY, 
                                      first_task, 
                                      s_sender), 
                                      TYPE::RECEIVED));

  correct.push_back(make_pair(Message(ACTION::RESPONSE, 
                                      STATUS::ACCEPTED, 
                                      first_task, 
                                      c_sender), 
                                      TYPE::SENT));

  correct.push_back(make_pair(Message(ACTION::RESPONSE, 
                                      STATUS::DONE, 
                                      first_task, 
                                      c_sender), 
                                      TYPE::SENT));

  correct.push_back(make_pair(Message(ACTION::COMMAND, 
                                      STATUS::READY, 
                                      second_task, 
                                      s_sender), 
                                      TYPE::RECEIVED));

  correct.push_back(make_pair(Message(ACTION::RESPONSE, 
                                      STATUS::ACCEPTED, 
                                      second_task, 
                                      c_sender), 
                                      TYPE::SENT));

  correct.push_back(make_pair(Message(ACTION::RESPONSE, 
                                      STATUS::DONE, 
                                      second_task, 
                                      c_sender), 
                                      TYPE::SENT));                                  

  correct.push_back(make_pair(Message(ACTION::RESPONSE, 
                                      STATUS::DONE, 
                                      Message::done_task, 
                                      s_sender), 
                                      TYPE::RECEIVED));

  Compare(history, correct);
}
