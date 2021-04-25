#include "main_menu_hud.h"
#include "main_menu_hud_ui.h"
#include <Blueprint/UserWidget.h>

AMainMenuHud::AMainMenuHud()
{
  static ConstructorHelpers::FClassFinder<UMainMenuHudUi> hudUiClassFinder(
    TEXT("/Game/BP_MainMenuHudUi"));
  hudUiClass = hudUiClassFinder.Class;
  hudUi = CreateWidget<UMainMenuHudUi>(GetWorld(), hudUiClass);
}

auto AMainMenuHud::BeginPlay() -> void
{
  Super::BeginPlay();
  if (!hudUi)
    return;
  hudUi->AddToViewport();
  auto playerController = GetWorld()->GetFirstPlayerController();
  if (!playerController)
    return;
  playerController->SetInputMode(FInputModeUIOnly{});
  playerController->bShowMouseCursor = true;
  playerController->bEnableMouseOverEvents = true;
}
