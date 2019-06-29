/*
 * Definition for the notification class.
 * The notification is not sent here because the blynk lib can only be included
 * once.
 */

#pragma once

#include <string>

class Notification{
public: 
  std::string message;
  bool flag;
public:
  Notification(std::string msg);
 };
