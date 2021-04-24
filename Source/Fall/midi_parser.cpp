#include "midi_parser.h"
#include "log.h"
#include <cassert>
#include <cstring>
#include <iomanip>
#include <sstream>
#include <stdexcept>

template <typename T>
T swap_endian(T u)
{
  union
  {
    T u;
    unsigned char u8[sizeof(T)];
  } source, dest;

  source.u = u;

  for (size_t k = 0; k < sizeof(T); k++)
    dest.u8[k] = source.u8[sizeof(T) - k - 1];

  return dest.u;
}

std::vector<MidiNote> MidiParser::parse(std::istream &strm)
{
  currentTime_ = 0;
  notes_.clear();
  auto chunk = readChunk(strm, "MThd");

#pragma pack(push)
#pragma pack(1)
  struct HeaderChunk
  {
    uint16_t formatType;
    uint16_t numberOfTracks;
    uint16_t timeDivision;
  };
#pragma pack(pop)
  HeaderChunk headerChunk;
  memcpy(&headerChunk, &chunk[0], sizeof(headerChunk));
  auto numberOfTracks = swap_endian(headerChunk.numberOfTracks);
  tickPerBit_ = swap_endian(headerChunk.timeDivision);
  for (int i = 0; i < numberOfTracks; ++i)
  {
    std::istringstream tmp(readChunk(strm, "MTrk"));
    parseMidiEvents(tmp);
  }
  return notes_;
}

std::string MidiParser::readChunk(std::istream &strm, std::string chunkId)
{
#pragma pack(push)
#pragma pack(1)
  struct Header
  {
    char chunkId[4];
    uint32_t chunkSize;
  } header;
#pragma pack(pop)
  strm.read((char *)&header, sizeof(header));
  assert(chunkId.size() == 4);
  if (header.chunkId[0] != chunkId[0] || header.chunkId[1] != chunkId[1] ||
      header.chunkId[2] != chunkId[2] || header.chunkId[3] != chunkId[3])
  {
    LOG("Chunk ID error: '",
        chunkId,
        "' expected by '",
        header.chunkId[0],
        header.chunkId[1],
        header.chunkId[2],
        header.chunkId[3],
        "' found");
  }
  auto sz = swap_endian(header.chunkSize);
  std::string res;
  res.resize(sz);
  strm.read(&res[0], sz);
  return res;
}

static unsigned readVLV(std::istream &strm)
{
  unsigned res = 0;
  while (strm)
  {
    unsigned char ch;
    strm.read(reinterpret_cast<char *>(&ch), 1);
    res = (res << 7) | (ch & 0x7f);
    if ((ch & 0x80) == 0)
      break;
  }
  return res;
}

void MidiParser::parseMidiEvents(std::istream &strm)
{
  unsigned char lastCh = 0;
  while (strm)
  {
    auto vTime = readVLV(strm);
    if (!strm)
      break;
    currentTime_ += vTime;
    unsigned char ch;
    strm.read(reinterpret_cast<char *>(&ch), 1);
    if ((ch & 0x80) == 0)
    {
      strm.putback(ch);
      ch = lastCh;
    }
    switch (ch)
    {
    default: // midi event
    {
      unsigned char note;
      strm.read(reinterpret_cast<char *>(&note), 1);
      unsigned char velocity;
      strm.read(reinterpret_cast<char *>(&velocity), 1);
      if (ch >= 0x90 && ch <= 0x9f)
      {
        if (velocity != 0)
        {
          currentNote_ = note;
          currentStartTime_ = currentTime_;
        }
        else
          notes_.push_back(
            MidiNote(currentNote_ - 4 * 12,
                     (currentTime_ - currentStartTime_) * tempo_ / tickPerBit_ / 1000,
                     1ll * currentStartTime_ * tempo_ / tickPerBit_ / 1000));
      }
      else if (ch == 0x80)
        notes_.push_back(MidiNote(currentNote_ - 4 * 12,
                                  (currentTime_ - currentStartTime_) * tempo_ / tickPerBit_ / 1000,
                                  1ll * currentStartTime_ * tempo_ / tickPerBit_ / 1000));
    }
    break;
    case 0xff: // meta event
    {
      unsigned char metaType;
      strm.read(reinterpret_cast<char *>(&metaType), 1);
      auto len = readVLV(strm);
      unsigned val = 0;
      for (unsigned i = 0; i < len; ++i)
      {
        unsigned char tmp;
        strm.read(reinterpret_cast<char *>(&tmp), 1);
        val = (val << 8) | tmp;
      }
      if (metaType == 0x51)
        tempo_ = val;
      break;
    }
    case 0xf0: // sysex event
    case 0xf7: {
      while (strm)
      {
        unsigned char dataBytes;
        strm.read(reinterpret_cast<char *>(&dataBytes), 1);
        if (dataBytes == 0xf7)
          break;
      }
      break;
    }
    }
    lastCh = ch;
  }
}

int MidiParser::tempo() const
{
  return 60000000 / tempo_;
}
