#pragma once
#include <cstdint>

class MidiNote
{
public:
  MidiNote(int note, uint32_t duration, uint32_t startTime);
  int note() const;
  uint32_t startTime() const;
  uint32_t duration() const;

private:
  int note_;
  uint32_t duration_;
  uint32_t startTime_;
};
