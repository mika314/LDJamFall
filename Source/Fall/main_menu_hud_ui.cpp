#include "main_menu_hud_ui.h"
#include "get_prop.h"
#include <Components/Button.h>
#include <Components/CanvasPanel.h>
#include <Components/WidgetSwitcher.h>
#include <Kismet/GameplayStatics.h>

UMainMenuHudUi::UMainMenuHudUi(const FObjectInitializer &initializer) : UUserWidget(initializer) {}

auto UMainMenuHudUi::uiSetupFinished() -> void
{
  {
    auto btn = getProp<UButton>(this, TEXT("PlayBtn"));
    btn->OnClicked.AddDynamic(this, &UMainMenuHudUi::onPlay);
  }
  {
    auto btn = getProp<UButton>(this, TEXT("BackBtn"));
    btn->OnClicked.AddDynamic(this, &UMainMenuHudUi::onBack);
  }
  {
    auto btn = getProp<UButton>(this, TEXT("QuitBtn"));
    btn->OnClicked.AddDynamic(this, &UMainMenuHudUi::onQuit);
  }

#define LVL(x)                                                         \
  {                                                                    \
    auto btn = getProp<UButton>(this, TEXT("Level" #x "Btn"));         \
    btn->OnClicked.AddDynamic(this, &UMainMenuHudUi::onLevel##x##Btn); \
  }
  LVL(1e);
  LVL(1n);
  LVL(1h);
  LVL(2e);
  LVL(2n);
  LVL(2h);
#undef LVL
}

auto UMainMenuHudUi::onPlay() -> void
{
  auto switcher = getProp<UWidgetSwitcher>(this, TEXT("Switcher"));
  auto levelSelectionPanel = getProp<UCanvasPanel>(this, TEXT("LevelSelectionPanel"));
  switcher->SetActiveWidget(levelSelectionPanel);
}

auto UMainMenuHudUi::onBack() -> void
{
  auto switcher = getProp<UWidgetSwitcher>(this, TEXT("Switcher"));
  auto mainMenuPanel = getProp<UCanvasPanel>(this, TEXT("MainMenuPanel"));
  switcher->SetActiveWidget(mainMenuPanel);
}

auto UMainMenuHudUi::onQuit() -> void
{
  UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
}

auto UMainMenuHudUi::onLevel1eBtn() -> void
{
  UGameplayStatics::OpenLevel(this, FName("GamePlay"), true, TEXT("1e"));
}

auto UMainMenuHudUi::onLevel1nBtn() -> void
{
  UGameplayStatics::OpenLevel(this, FName("GamePlay"), true, TEXT("1n"));
}

auto UMainMenuHudUi::onLevel1hBtn() -> void
{
  UGameplayStatics::OpenLevel(this, FName("GamePlay"), true, TEXT("1h"));
}

auto UMainMenuHudUi::onLevel2eBtn() -> void
{
  UGameplayStatics::OpenLevel(this, FName("GamePlay"), true, TEXT("2e"));
}

auto UMainMenuHudUi::onLevel2nBtn() -> void
{
  UGameplayStatics::OpenLevel(this, FName("GamePlay"), true, TEXT("2n"));
}

auto UMainMenuHudUi::onLevel2hBtn() -> void
{
  UGameplayStatics::OpenLevel(this, FName("GamePlay"), true, TEXT("2h"));
}
