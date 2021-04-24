// Copyright (c) 2021 Mika Pi

#include "prj_hud.h"
#include "hud_ui.h"
//#include "pause_ui.h"

APrjHud::APrjHud()
{
  static ConstructorHelpers::FClassFinder<UHudUi> hudUiClassFinder(TEXT("/Game/BP_HudUi"));
  hudUi = CreateWidget<UHudUi>(GetWorld(), hudUiClassFinder.Class);
}

auto APrjHud::BeginPlay() -> void
{
  Super::BeginPlay();
  if (hudUi)
    hudUi->AddToViewport();
  auto playerController = GetWorld()->GetFirstPlayerController();
  if (!playerController)
    return;
  playerController->SetInputMode(FInputModeGameOnly{});
  playerController->bShowMouseCursor = false;

  //  pauseUi = CreateWidget<UPauseUi>(GetWorld(), pauseUiClass);
  //  pauseUi->AddToViewport();
  //  pauseUi->SetVisibility(ESlateVisibility::Hidden);
  //  pauseUi->loadSettings();
}

// auto APrjHud::showPause(class UInwards &val) -> void
//{
//  pauseUi->show(val);
//}
