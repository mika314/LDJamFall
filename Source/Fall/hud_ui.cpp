// Copyright (c) 2021 Mika Pi

#include "hud_ui.h"
#include "get_prop.h"
#include "log.h"
#include "prj_game_state.h"
#include <Components/Button.h>
#include <Components/CanvasPanel.h>
#include <Components/TextBlock.h>
#include <Components/WidgetSwitcher.h>
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetSystemLibrary.h>

void UHudUi::NativeTick(const FGeometry &MyGeometry, float InDeltaTime)
{
  Super::NativeTick(MyGeometry, InDeltaTime);

  auto gs = GetWorld()->GetGameState<APrjGameState>();
  if (!gs)
    return;

  {
    auto percentTb = getProp<UTextBlock>(this, TEXT("PercentTb"));
    if (!percentTb)
      return;

    FFormatNamedArguments args;
    {
      FNumberFormattingOptions opt;
      opt.MaximumFractionalDigits = 1;
      opt.MinimumFractionalDigits = 1;
      args.Add("percent", FText::AsNumber(gs->getPercent(), &opt));
    }
    percentTb->SetText(FText::Format(NSLOCTEXT("prj", "Percent", "{percent}%"), args));
  }
  {
    auto scoreTb = getProp<UTextBlock>(this, TEXT("ScoreTb"));
    FFormatNamedArguments args;
    {
      args.Add("score", gs->getScore());
    }
    scoreTb->SetText(FText::Format(NSLOCTEXT("prj", "Score", "Score: {score}"), args));
  }
  {
    auto scoreTb = getProp<UTextBlock>(this, TEXT("Score2Tb"));
    FFormatNamedArguments args;
    {
      args.Add("score", gs->getScore());
    }
    scoreTb->SetText(FText::Format(NSLOCTEXT("prj", "Score", "Score: {score}"), args));
  }
  {
    auto comboTb = getProp<UTextBlock>(this, TEXT("ComboTb"));
    FFormatNamedArguments args;
    {
      args.Add("combo", gs->getCombo());
    }
    comboTb->SetText(FText::Format(NSLOCTEXT("prj", "Combo", "Combo: {combo}"), args));
  }
  {
    auto multiTb = getProp<UTextBlock>(this, TEXT("MultiTb"));
    FFormatNamedArguments args;
    {
      args.Add("multi", gs->getMulti());
    }
    multiTb->SetText(FText::Format(NSLOCTEXT("prj", "Multi", "x{multi}"), args));
  }
  if (GetWorld()->GetTimeSeconds() > 3 * 60 + 14)
  {
    auto switcher = getProp<UWidgetSwitcher>(this, TEXT("Switcher"));
    auto scorePanel = getProp<UCanvasPanel>(this, TEXT("ScorePanel"));
    if (scorePanel != switcher->GetActiveWidget())
    {
      switcher->SetActiveWidget(scorePanel);
      auto playerController = GetWorld()->GetFirstPlayerController();
      if (!playerController)
        return;
      playerController->SetInputMode(FInputModeUIOnly{});
      playerController->bShowMouseCursor = true;
    }
  }
}

auto UHudUi::uiSetupFinished() -> void
{
  {
    auto btn = getProp<UButton>(this, TEXT("MainMenuBtn"));
    btn->OnClicked.AddDynamic(this, &UHudUi::onMainMenu);
  }
  {
    auto btn = getProp<UButton>(this, TEXT("MainMenu2Btn"));
    btn->OnClicked.AddDynamic(this, &UHudUi::onMainMenu);
  }
  {
    auto btn = getProp<UButton>(this, TEXT("ResumeBtn"));
    btn->OnClicked.AddDynamic(this, &UHudUi::onResume);
  }
  {
    auto btn = getProp<UButton>(this, TEXT("QuitBtn"));
    btn->OnClicked.AddDynamic(this, &UHudUi::onQuit);
  }
  {
    auto btn = getProp<UButton>(this, TEXT("RestartBtn"));
    btn->OnClicked.AddDynamic(this, &UHudUi::onRestart);
  }
}

auto UHudUi::onMainMenu() -> void
{
  UGameplayStatics::OpenLevel(this, FName("MainMenu"), true);
}

auto UHudUi::onResume() -> void
{
  auto switcher = getProp<UWidgetSwitcher>(this, TEXT("Switcher"));
  auto gamePlayPanel = getProp<UCanvasPanel>(this, TEXT("GamePlayPanel"));
  switcher->SetActiveWidget(gamePlayPanel);
  auto playerController = GetWorld()->GetFirstPlayerController();
  if (!playerController)
    return;
  playerController->SetInputMode(FInputModeGameOnly{});
  playerController->bShowMouseCursor = false;
  UGameplayStatics::SetGamePaused(this, false);
}

auto UHudUi::onQuit() -> void
{
  UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
}

auto UHudUi::pause() -> void
{
  UGameplayStatics::SetGamePaused(this, true);
  auto switcher = getProp<UWidgetSwitcher>(this, TEXT("Switcher"));
  auto pausePanel = getProp<UCanvasPanel>(this, TEXT("PausePanel"));
  switcher->SetActiveWidget(pausePanel);
  auto playerController = GetWorld()->GetFirstPlayerController();
  if (!playerController)
    return;
  playerController->SetInputMode(FInputModeUIOnly{});
  playerController->bShowMouseCursor = true;
}

auto UHudUi::onRestart() -> void
{
  UGameplayStatics::OpenLevel(this,
                              FName(*GetWorld()->GetName()),
                              false,
                              UGameplayStatics::GetGameMode(this)->OptionsString.Mid(1));
}
