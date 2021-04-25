#pragma once

#include <CoreMinimal.h>
#include <Engine/StaticMeshActor.h>

#include "note_actor.generated.h"

UCLASS()
class FALL_API ANoteActor : public AStaticMeshActor
{
  GENERATED_BODY()
public:
  ANoteActor();
  auto BeginPlay() -> void override;
  auto Tick(float) -> void override;

  UPROPERTY(EditAnywhere)
  class UParticleSystemComponent *explosion = nullptr;

private:
  UFUNCTION()
  void onHit(AActor *me, AActor *other, FVector impact, const FHitResult &hitResult);
  bool isDied = false;
};