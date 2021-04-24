#include "midi_note.h"

MidiNote::MidiNote(int note, uint32_t duration, uint32_t startTime)
  : note_(note), duration_(duration), startTime_(startTime)
{
}

int MidiNote::note() const
{
  return note_;
}

uint32_t MidiNote::startTime() const
{
  return startTime_;
}

uint32_t MidiNote::duration() const
{
  return duration_;
}
