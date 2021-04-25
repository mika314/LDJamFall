// Copyright (c) 2021 Mika Pi

#pragma once
#include <CoreMinimal.h>
#include <GameFramework/GameStateBase.h>
#include <string>
#include <unordered_map>

#include "prj_game_state.generated.h"

UCLASS()
class FALL_API APrjGameState : public AGameStateBase
{
  GENERATED_BODY()
public:
  APrjGameState();
  auto bad() -> void;
  auto good() -> void;
  auto getMulti() const -> int;
  auto getScore() const -> int;
  auto getPercent() const -> float;
  auto getCombo() const -> int;

  UPROPERTY(EditAnywhere)
  class UAudioComponent *soundTrack = nullptr;

private:
  auto BeginPlay() -> void override;
  auto Tick(float) -> void override;
  int badN = 0;
  int goodN = 0;
  int combo = 0;
  int score = 0;
  std::unordered_map<std::string, class USoundBase *> soundTracks;
};
