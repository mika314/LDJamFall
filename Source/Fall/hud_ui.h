// Copyright (c) 2021 Mika Pi

#pragma once

#include <Blueprint/UserWidget.h>
#include <CoreMinimal.h>

#include "hud_ui.generated.h"

UCLASS()
class FALL_API UHudUi : public UUserWidget
{
  GENERATED_BODY()
public:
  auto NativeTick(const FGeometry &MyGeometry, float InDeltaTime) -> void override;
};
