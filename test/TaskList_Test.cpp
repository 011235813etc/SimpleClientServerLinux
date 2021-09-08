#include <limits.h>
#include <memory>
#include "gtest/gtest.h"
#include "../src/TaskList/TaskList.h"

#include <string>
#include <vector>

class TaskListTest : public ::testing::Test {
protected:
  virtual void SetUp() override {
  }

  virtual void TearDown() override {
  }
public:
  std::vector<std::string> split(std::string s, std::string separator) {
      std::vector<std::string> result;
      int start = 0;
      int end = s.find(separator);
      while (end != -1) {
          result.push_back(s.substr(start, end - start));
          std::cout << s.substr(start, end - start) << std::endl;
          start = end + separator.size();
          end = s.find(separator, start);
      }
      std::cout << s.substr(start, end - start) << std::endl;
      result.push_back(s.substr(start, end - start));
      return result;
  }
};

TEST_F(TaskListTest, emptyTaskList) {

  char path[] = "../test/tasks_for_TaskList/empty_task_list.txt";

	std::unique_ptr<TaskList> t_list(new TaskList(path));

  EXPECT_EQ(0, (int)t_list->size());
}

TEST_F(TaskListTest, taskListWithTwoTasks) {

  char path[] = "../test/tasks_for_TaskList/task_list_with_two_tasks.txt";

	std::unique_ptr<TaskList> t_list(new TaskList(path));

  EXPECT_EQ(2, (int)t_list->size());
}

TEST_F(TaskListTest, taskListWithComments) {

  char path[] = "../test/tasks_for_TaskList/task_list_with_comments.txt";

	std::unique_ptr<TaskList> t_list(new TaskList(path));
  std::cout << "task list size is: " << (int)t_list->size() << std::endl;

  EXPECT_EQ(2, (int)t_list->size());
}

TEST_F(TaskListTest, tasksOutput) {

  char path[] = "../test/tasks_for_TaskList/task_list.txt";
	std::unique_ptr<TaskList> t_list(new TaskList(path));

  testing::internal::CaptureStdout();
  (*t_list)[0];
  (*t_list)[1];

  std::string output = testing::internal::GetCapturedStdout();
  std::vector<std::string> result = split(output, "\n");

  EXPECT_EQ("First task was executed.", result[0]);
  EXPECT_EQ("Second task was executed.", result[2]);
}

TEST_F(TaskListTest, tasksExecuteResult) {

  char path[] = "../test/tasks_for_TaskList/task_list.txt";
	std::unique_ptr<TaskList> t_list(new TaskList(path));

  testing::internal::CaptureStdout();
  (*t_list)[0];
  (*t_list)[1];
  
  std::string output = testing::internal::GetCapturedStdout();
  std::vector<std::string> result = split(output, "\n");

  EXPECT_EQ("Task #0 - successfull!", result[1]);
  EXPECT_EQ("Task #1 - failure!",     result[3]);
}
