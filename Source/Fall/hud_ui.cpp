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

  auto scoreTb = getProp<UTextBlock>(this, TEXT("ScoreTb"));
  if (!scoreTb)
    return;

  {
    auto total = gs->badN + gs->goodN;
    FFormatNamedArguments args;
    if (total == 0)
      args.Add("percent", NSLOCTEXT("Prj", "100.0", "100.0"));
    else
    {
      FNumberFormattingOptions opt;
      opt.MaximumFractionalDigits = 1;
      opt.MinimumFractionalDigits = 1;
      args.Add("percent", FText::AsNumber(100.f * gs->goodN / total, &opt));
    }
    scoreTb->SetText(FText::Format(NSLOCTEXT("prj", "Score", "Score: {percent}%"), args));
  }
}
