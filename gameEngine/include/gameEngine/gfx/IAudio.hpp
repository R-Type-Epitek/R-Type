//
// Created by lsg on 16/12/23.
//

#pragma once

class IAudio {
public:
  virtual ~IAudio() = default;
  virtual void playAudio() = 0;
  virtual void pauseAudio() = 0;
  virtual void stopAudio() = 0;

private:
};