// Copyright (c) 2021 Mika Pi

#include "prj_game_state.h"
#include "log.h"
#include "midi_parser.h"
#include "test_mid.h"
#include <sstream>

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
  for (auto n : notes)
    LOG(n.note(), n.startTime(), n.duration());
}

auto APrjGameState::Tick(float dt) -> void
{
  Super::Tick(dt);
}
