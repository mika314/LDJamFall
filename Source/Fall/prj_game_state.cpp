// Copyright (c) 2021 Mika Pi

#include "prj_game_state.h"
#include "level1e_mid.h"
#include "level1h_mid.h"
#include "level1n_mid.h"
#include "level2e_mid.h"
#include "level2n_mid.h"
#include "level2h_mid.h"
#include "log.h"
#include "midi_parser.h"
#include "note_actor.h"
#include <Components/AudioComponent.h>
#include <Kismet/GameplayStatics.h>
#include <sstream>

APrjGameState::APrjGameState() : soundTrack(CreateDefaultSubobject<UAudioComponent>("soundTrack"))
{
  PrimaryActorTick.bCanEverTick = true;
  {
    static ConstructorHelpers::FObjectFinder<USoundBase> stFinder(TEXT("/Game/ST_Level1"));
    soundTracks["?1e"] = stFinder.Object;
    soundTracks["?1n"] = stFinder.Object;
    soundTracks["?1h"] = stFinder.Object;
  }
  {
    static ConstructorHelpers::FObjectFinder<USoundBase> stFinder(TEXT("/Game/ST_Level2"));
    soundTracks["?2e"] = stFinder.Object;
    soundTracks["?2n"] = stFinder.Object;
    soundTracks["?2h"] = stFinder.Object;
  }
}

auto APrjGameState::BeginPlay() -> void
{
  Super::BeginPlay();
  auto controller = UGameplayStatics::GetPlayerController(this, 0);
  if (!controller)
    return;
  controller->ConsoleCommand(TEXT("t.MaxFPS 60"), true);
  static std::unordered_map<std::string, std::pair<unsigned char *, unsigned int>> levels = {
    {"?1e", {Assets_midi_level1e_mid, Assets_midi_level1e_mid_len}},
    {"?1n", {Assets_midi_level1n_mid, Assets_midi_level1n_mid_len}},
    {"?1h", {Assets_midi_level1h_mid, Assets_midi_level1h_mid_len}},
    {"?2e", {Assets_midi_level2e_mid, Assets_midi_level2e_mid_len}},
    {"?2n", {Assets_midi_level2n_mid, Assets_midi_level2n_mid_len}},
    {"?2h", {Assets_midi_level2h_mid, Assets_midi_level2h_mid_len}},
  };

  LOG("reading midi", UGameplayStatics::GetGameMode(this)->OptionsString);

  const std::string opt = TCHAR_TO_UTF8(*UGameplayStatics::GetGameMode(this)->OptionsString);
  {
    auto it = soundTracks.find(opt);
    if (it == std::end(soundTracks))
      it = soundTracks.begin();
    soundTrack->SetSound(it->second);
    soundTrack->Play();
  }

  const auto notes = [this, &opt]() {
    auto it = levels.find(opt);
    if (it == std::end(levels))
      it = levels.begin();
    std::string mid{reinterpret_cast<const char *>(it->second.first), it->second.second};
    std::istringstream ss(mid);
    return MidiParser{}.parse(ss);
  }();
  static std::unordered_map<int, FVector> notesMap = {
    {-12, {300, 0, 0}},
    {-9, {0, 300, 0}},
    {-10, {0, -300, 0}},
  };
  for (auto n : notes)
  {
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
