//
// Created by lsg on 16/12/23.
//

#pragma once

#include "IAudio.hpp"

class Audio : public IAudio {
 public:
  void playAudio();
  void pauseAudio();
  void stopAudio();

 private:
};