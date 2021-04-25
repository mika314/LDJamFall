#pragma once

#include <CoreMinimal.h>
#include <GameFramework/HUD.h>

#include "main_menu_hud.generated.h"

UCLASS()
class FALL_API AMainMenuHud : public AHUD
{
  GENERATED_BODY()
public:
  AMainMenuHud();

  class UMainMenuHudUi *hudUi = nullptr;

private:
  auto BeginPlay() -> void override;
  TSubclassOf<class UMainMenuHudUi> hudUiClass = nullptr;
};
