// Copyright (c) 2021 Mika Pi

#pragma once
#include <CoreMinimal.h>
#include <GameFramework/GameStateBase.h>

#include "prj_game_state.generated.h"

UCLASS()
class FALL_API APrjGameState : public AGameStateBase
{
  GENERATED_BODY()
public:
  APrjGameState();

private:
  auto BeginPlay() -> void override;
  auto Tick(float) -> void override;
};
