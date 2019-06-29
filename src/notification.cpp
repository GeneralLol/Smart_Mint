/*
 * Implementation of the notification class.
 */
#include <string>

#include "notification.h"

Notification::Notification(std::string msg){
  this->message = msg;
  flag = false;
}
