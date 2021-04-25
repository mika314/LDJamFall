#pragma once

#include <Blueprint/UserWidget.h>

#include "main_menu_hud_ui.generated.h"

UCLASS()
class FALL_API UMainMenuHudUi : public UUserWidget
{
  GENERATED_BODY()
public:
  UMainMenuHudUi(const FObjectInitializer &);

  UFUNCTION(BlueprintCallable)
  void uiSetupFinished();

private:
  UFUNCTION()
  void onPlay();
  UFUNCTION()
  void onLevel1eBtn();
  UFUNCTION()
  void onLevel1nBtn();
  UFUNCTION()
  void onLevel1hBtn();
};
