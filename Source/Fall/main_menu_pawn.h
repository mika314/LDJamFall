#pragma once

#include <CoreMinimal.h>
#include <GameFramework/Pawn.h>

#include "main_menu_pawn.generated.h"

UCLASS()
class FALL_API AMainMenuPawn : public APawn
{
  GENERATED_BODY()
public:
  UPROPERTY()
  class USceneComponent *root;

  AMainMenuPawn();
  auto Tick(float) -> void override;
};
