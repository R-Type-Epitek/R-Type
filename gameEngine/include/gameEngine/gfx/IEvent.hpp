//
// Created by lsg on 16/12/23.
//

#pragma once

class IEvent {
public:
  virtual ~IEvent() = default;
  virtual void updateEvent() = 0;
  virtual void getEvent() = 0;

private:
};
