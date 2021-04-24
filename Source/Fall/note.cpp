#include "note.h"

Note::Note(int note, uint32_t duration, uint32_t startTime)
  : note_(note), duration_(duration), startTime_(startTime)
{
}

int Note::note() const
{
  return note_;
}

uint32_t Note::startTime() const
{
  return startTime_;
}

uint32_t Note::duration() const
{
  return duration_;
}
