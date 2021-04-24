#pragma once

#include <Animation/SkeletalMeshActor.h>
#include <CoreMinimal.h>

#include "cat.generated.h"

UCLASS()
class FALL_API ACat : public ASkeletalMeshActor
{
  GENERATED_BODY()
public:
  ACat();
  auto Tick(float) -> void override;
  auto down() -> void;
  auto left() -> void;
  auto right() -> void;
  auto up() -> void;
};
