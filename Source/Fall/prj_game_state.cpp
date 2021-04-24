// Copyright (c) 2021 Mika Pi

#include "prj_game_state.h"
#include "log.h"
#include "midi_parser.h"
#include "note_actor.h"
#include "test_mid.h"
#include <sstream>
#include <unordered_map>

APrjGameState::APrjGameState()
{
  PrimaryActorTick.bCanEverTick = true;
}

auto APrjGameState::BeginPlay() -> void
{
  Super::BeginPlay();
  LOG("reading midi");
  std::string mid{reinterpret_cast<const char *>(Assets_midi_Test_mid), Assets_midi_Test_mid_len};
  std::istringstream ss(mid);
  auto notes = MidiParser{}.parse(ss);
  static std::unordered_map<int, FVector> notesMap = {
    {-12, {300, 0, 0}},
    {-9, {0, 300, 0}},
    {-10, {0, -300, 0}},
  };
  for (auto n : notes)
  {
    LOG(n.note(), n.startTime(), n.duration());
    auto it = notesMap.find(n.note());
    if (it == std::end(notesMap))
      continue;
    FActorSpawnParameters param;
    param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    GetWorld()->SpawnActor<ANoteActor>(ANoteActor::StaticClass(),
                                       it->second + FVector{.0f, .0f, -1.f * n.startTime() - 250},
                                       FRotator{0, 1.f * (rand() % 360), 0},
                                       param);
  }
  badN = 0;
  goodN = 0;
}

auto APrjGameState::Tick(float dt) -> void
{
  Super::Tick(dt);
}

auto APrjGameState::bad() -> void
{
  ++badN;
  combo = 0;
}

auto APrjGameState::good() -> void
{
  ++goodN;
  ++combo;
  score += getMulti();
}

auto APrjGameState::getMulti() const -> int
{
  if (combo <= 0)
    return 1;
  return log2(combo);
}

auto APrjGameState::getScore() const -> int
{
  return score;
}

auto APrjGameState::getPercent() const -> float
{
  const auto total = badN + goodN;
  return total != 0 ? 100.f * goodN / total : 100.f;
}

auto APrjGameState::getCombo() const -> int
{
  return combo;
}
