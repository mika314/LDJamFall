#pragma once
#include "midi_note.h"
#include <string>
#include <vector>

class MidiParser
{
public:
  std::vector<MidiNote> parse(std::istream &strm);
  int tempo() const;

private:
  std::string readChunk(std::istream &strm, std::string chunkId);
  void parseMidiEvents(std::istream &strm);
  unsigned tempo_ = 461538;
  unsigned tickPerBit_ = 768;
  std::vector<MidiNote> notes_;
  unsigned currentTime_;
  int currentNote_;
  uint32_t currentStartTime_;
};
