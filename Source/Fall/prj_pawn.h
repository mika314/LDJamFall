#pragma once
#include <CoreMinimal.h>
#include <GameFramework/Pawn.h>

#include "prj_pawn.generated.h"

UCLASS()
class FALL_API APrjPawn : public APawn
{
  GENERATED_BODY()
public:
  UPROPERTY()
  class USceneComponent *root;

  APrjPawn();
  auto SetupPlayerInputComponent(class UInputComponent *) -> void override;

private:
  auto BeginPlay() -> void;
  auto down() -> void;
  auto left() -> void;
  auto pause() -> void;
  auto right() -> void;
  auto up() -> void;

  class ACat *cat;
};
