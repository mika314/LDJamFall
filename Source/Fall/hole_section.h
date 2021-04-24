#pragma once

#include <CoreMinimal.h>
#include <Engine/StaticMeshActor.h>

#include "hole_section.generated.h"

UCLASS()
class FALL_API AHoleSection : public AStaticMeshActor
{
  GENERATED_BODY()
public:
  AHoleSection();
  auto Tick(float) -> void override;
};
