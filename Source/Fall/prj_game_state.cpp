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
    {-9, {0, 0, 0}},
    {-10, {0, -300, 0}},
  };
  for (auto n : notes)
  {
    LOG(n.note(), n.startTime(), n.duration());
    FActorSpawnParameters param;
    param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    GetWorld()->SpawnActor<ANoteActor>(ANoteActor::StaticClass(),
                                       notesMap[n.note()] + FVector{.0f, .0f, -1.f * n.startTime()},
                                       FRotator{},
                                       param);
  }
}

auto APrjGameState::Tick(float dt) -> void
{
  Super::Tick(dt);
}
