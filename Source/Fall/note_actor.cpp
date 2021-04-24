#include "note_actor.h"
#include "log.h"

ANoteActor::ANoteActor()
{
  PrimaryActorTick.bCanEverTick = true;
  static ConstructorHelpers::FObjectFinder<UStaticMesh> staticMeshFinder(
    TEXT("/Engine/VREditor/BasicMeshes/SM_Ball_01"));
  GetStaticMeshComponent()->SetStaticMesh(staticMeshFinder.Object);
  GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
  GetStaticMeshComponent()->SetNotifyRigidBodyCollision(true);
}

auto ANoteActor::BeginPlay() -> void
{
  Super::BeginPlay();
  OnActorHit.AddDynamic(this, &ANoteActor::onHit);
}

auto ANoteActor::Tick(float dt) -> void
{
  Super::Tick(dt);
  const auto loc = GetActorLocation();
  SetActorLocation(loc + FVector{0, 0, dt * 1000.f});
}

auto ANoteActor::onHit(AActor *me, AActor *other, FVector impact, const FHitResult &hitResult)
  -> void
{
  LOG("me", me->GetName(), "other", other->GetName());
  Destroy();
}
