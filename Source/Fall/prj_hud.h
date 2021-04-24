// Copyright (c) 2021 Mika Pi

#pragma once

#include <CoreMinimal.h>
#include <GameFramework/HUD.h>

#include "prj_hud.generated.h"

UCLASS()
class FALL_API APrjHud : public AHUD
{
  GENERATED_BODY()
public:
  APrjHud();
  //  auto showPause(class UInwards &) -> void;

private:
  auto BeginPlay() -> void override;

  class UHudUi *hudUi = nullptr;
  //  class UPauseUi *pauseUi = nullptr;
};
