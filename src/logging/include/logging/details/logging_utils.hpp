/*
 * logging_utils.hpp
 *
 * Created on: Dec 28, 2018 11:30
 * Description:
 *
 * Copyright (c) 2018 Ruixiang Du (rdu)
 */

#ifndef XMOTION_LOGGING_UTILS_HPP
#define XMOTION_LOGGING_UTILS_HPP

#include <cstdlib>
#include <ctime>
#include <string>

namespace xmotion {
inline std::string GetProjectRootPath() {
  char *home_path = std::getenv("HOME");
  if (home_path == nullptr) {
    return "/tmp/.xmotion";
  }
  return std::string(home_path) + "/.xmotion";
}

inline std::string GetLogFolderPath() { return GetProjectRootPath() + "/log"; }

// reference:
// https://stackoverflow.com/questions/22318389/pass-system-date-and-time-as-a-filename-in-c
inline std::string CreateLogFileName(const std::string &prefix,
                                      const std::string &path) {
  time_t t = time(0);  // get time now
  struct tm *now = localtime(&t);
  if (now == nullptr) {
    return path + "/" + prefix + ".unknown.csv";
  }

  constexpr size_t kBufferSize = 32;
  char buffer[kBufferSize];
  strftime(buffer, kBufferSize, "%Y%m%d%H%M%S", now);
  std::string time_stamp(buffer);

  return path + "/" + prefix + "." + time_stamp + ".csv";
}
}  // namespace xmotion

#endif  // XMOTION_LOGGING_UTILS_HPP
