#include "log/log.hpp"

#include <time.h>
#include <fstream>
#include <string>

#include "gtest/gtest.h"

bool base_handle_called = false;
bool full_handle_called = false;

void BaseHandle(std::string entry) { base_handle_called = true; }

void FullHandle(std::pair<unsigned int, std::string> entry) {
  full_handle_called = true;
}

void SetLogs() {
  ostendo::log::ClearLogs();
  ostendo::log::Log(ostendo::log::ERROR, "test 0", "test");
  ostendo::log::Log(ostendo::log::WARNING, "test 1", "test");
  ostendo::log::Log(ostendo::log::TRACE, "test 2", "test");
  ostendo::log::Log(ostendo::log::DEBUG, "test 3", "test");
  ostendo::log::Log(ostendo::log::SUCCESS, "test 4", "test");
  ostendo::log::Log(ostendo::log::INFO, "test 5", "test");
  ostendo::log::Log(ostendo::log::DATA, "test 6", "test");
  ostendo::log::Log(ostendo::log::ERROR, "test 7", "test");
  ostendo::log::Log(ostendo::log::WARNING, "test 8", "test");
  ostendo::log::Log(ostendo::log::TRACE, "test 9", "test");
  ostendo::log::Log(ostendo::log::DEBUG, "test 10", "test");
  ostendo::log::Log(ostendo::log::SUCCESS, "test 11", "test");
  ostendo::log::Log(ostendo::log::INFO, "test 12", "test");
  ostendo::log::Log(ostendo::log::DATA, "test 13", "test");
}

TEST(LogTest, Log) {
  ostendo::log::Log(ostendo::log::DATA, "log entry test", "test");
  std::pair<unsigned int, std::string> log_entry =
      ostendo::log::FGetLog(ostendo::log::NONE);
  EXPECT_EQ(log_entry.first, ostendo::log::DATA);
  EXPECT_EQ(log_entry.second, "[DATA][log entry test][test]");
}

TEST(LogTest, Log_TimeStamp) {
  ostendo::log::SetLogOption(ostendo::log::TIME_STAMP, true);
  ostendo::log::Log(ostendo::log::DATA, "log time stamp test", "test");
  std::pair<unsigned int, std::string> log_entry =
      ostendo::log::FGetLog(ostendo::log::NONE);
  EXPECT_EQ(log_entry.first, ostendo::log::DATA);
  time_t current = time(NULL);
  struct tm* time_info = localtime(&current);
  char buffer[80];
  strftime(buffer, 80, "%T", time_info);
  std::string str(buffer);
  str = "[DATA][" + str + "][log time stamp test][test]";
  EXPECT_EQ(log_entry.second, str);
  ostendo::log::SetLogOption(ostendo::log::TIME_STAMP, false);
}

TEST(LogTest, Log_DateStamp) {
  ostendo::log::SetLogOption(ostendo::log::DATE_STAMP, true);
  ostendo::log::Log(ostendo::log::DATA, "log date stamp test", "test");
  std::pair<int, std::string> log_entry =
      ostendo::log::FGetLog(ostendo::log::NONE);
  EXPECT_EQ(log_entry.first, ostendo::log::DATA);
  time_t current = time(NULL);
  struct tm* time_info = localtime(&current);
  char buffer[80];
  strftime(buffer, 80, "%D", time_info);
  std::string str(buffer);
  str = "[DATA][" + str + "][log date stamp test][test]";
  EXPECT_EQ(log_entry.second, str);
  ostendo::log::SetLogOption(ostendo::log::DATE_STAMP, false);
}

TEST(LogTest, GetLogSize) {
  SetLogs();
  EXPECT_EQ(ostendo::log::GetLogSize(), 14);
}

TEST(LogTest, ClearLogs) {
  SetLogs();
  EXPECT_NE(ostendo::log::GetLogSize(), 0);
  ostendo::log::ClearLogs();
  EXPECT_EQ(ostendo::log::GetLogSize(), 0);
}

TEST(LogTest, GetLog) {
  SetLogs();
  std::string log_entry = ostendo::log::GetLog(ostendo::log::SUCCESS);
  EXPECT_EQ(log_entry, "[SUCCESS][test 11][test]");
  log_entry = ostendo::log::GetLog(ostendo::log::NONE);
  EXPECT_EQ(log_entry, "[DATA][test 13][test]");
}

TEST(LogTest, FGetLog) {
  SetLogs();
  std::pair<int, std::string> log_entry =
      ostendo::log::FGetLog(ostendo::log::DEBUG);
  EXPECT_EQ(log_entry.first, ostendo::log::DEBUG);
  EXPECT_EQ(log_entry.second, "[DEBUG][test 10][test]");
}

TEST(LogTest, IGetLog) {
  SetLogs();
  std::string log_entry = ostendo::log::IGetLog(6);
  EXPECT_EQ(log_entry, "[DATA][test 6][test]");
}

TEST(LogTest, IFGetLog) {
  SetLogs();
  std::pair<int, std::string> log_entry = ostendo::log::IFGetLog(7);
  EXPECT_EQ(log_entry.first, ostendo::log::ERROR);
  EXPECT_EQ(log_entry.second, "[ERROR][test 7][test]");
}

TEST(LogTest, VGetLog) {
  SetLogs();
  std::vector<std::string> entries = ostendo::log::VGetLog(1, 4);
  EXPECT_EQ(entries.size(), 4);
  if (entries.size() == 4) {
    EXPECT_EQ(entries[0], "[WARNING][test 1][test]");
    EXPECT_EQ(entries[1], "[TRACE][test 2][test]");
    EXPECT_EQ(entries[2], "[DEBUG][test 3][test]");
    EXPECT_EQ(entries[3], "[SUCCESS][test 4][test]");
  }
}

TEST(LogTest, VFGetLog) {
  SetLogs();
  std::vector<std::pair<unsigned int, std::string>> entries =
      ostendo::log::VFGetLog(1, 4);
  EXPECT_EQ(entries.size(), 4);
  if (entries.size() == 4) {
    EXPECT_EQ(entries[0].first, ostendo::log::WARNING);
    EXPECT_EQ(entries[0].second, "[WARNING][test 1][test]");
    EXPECT_EQ(entries[1].first, ostendo::log::TRACE);
    EXPECT_EQ(entries[1].second, "[TRACE][test 2][test]");
    EXPECT_EQ(entries[2].first, ostendo::log::DEBUG);
    EXPECT_EQ(entries[2].second, "[DEBUG][test 3][test]");
    EXPECT_EQ(entries[3].first, ostendo::log::SUCCESS);
    EXPECT_EQ(entries[3].second, "[SUCCESS][test 4][test]");
  }
}

TEST(LogTest, SetLogHandle) {
  ostendo::log::SetLogHandle(BaseHandle);
  ostendo::log::Log(ostendo::log::INFO, "test", "test");
  EXPECT_EQ(base_handle_called, true);
}

TEST(LogTest, SetFullLogHandle) {
  ostendo::log::SetLogHandle(FullHandle);
  ostendo::log::Log(ostendo::log::INFO, "test", "test");
  EXPECT_EQ(full_handle_called, true);
}

TEST(LogTest, GetTypeStr) {
  std::string str = ostendo::log::GetTypeStr(ostendo::log::DEBUG);
  EXPECT_EQ(str, "DEBUG");
}

TEST(LogTest, SaveLog) {
  SetLogs();
  ostendo::log::SaveLog("tmp.log");
  std::ifstream f("tmp.log");
  EXPECT_TRUE(f.is_open());
  std::vector<std::string> entries = ostendo::log::VGetLog(0, 13);
  if (f.is_open()) {
    std::string line;
    size_t i = 0, j = 0;
    while (getline(f, line)) {
      if (i < entries.size()) {
        EXPECT_EQ(line, entries[i]);
      }
      i++;
      j++;
    }
    EXPECT_EQ(entries.size(), j);
    f.close();
  }
  remove("tmp.log");
}
