// Copyright (c) 2021 Mika Pi

#include "hud_ui.h"
#include "get_prop.h"
#include "log.h"
#include "prj_game_state.h"
#include <Components/TextBlock.h>
#include <Kismet/GameplayStatics.h>

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
}
