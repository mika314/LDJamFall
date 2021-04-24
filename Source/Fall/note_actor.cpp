#include "note_actor.h"
#include "log.h"
#include "prj_game_state.h"

ANoteActor::ANoteActor()
{
  PrimaryActorTick.bCanEverTick = true;
  static ConstructorHelpers::FObjectFinder<UStaticMesh> staticMeshFinder(TEXT("/Game/SM_Mouse"));
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
  auto gs = GetWorld()->GetGameState<APrjGameState>();
  if (!gs)
    return;
  const auto loc = GetActorLocation();
  SetActorLocation(loc + FVector{0, 0, dt * 1000.f});
  if (loc.Z > 500)
  {
    Destroy();
    gs->bad();
  }
}

auto ANoteActor::onHit(AActor *me, AActor *other, FVector impact, const FHitResult &hitResult)
  -> void
{
  LOG("me", me->GetName(), "other", other->GetName());
  auto gs = GetWorld()->GetGameState<APrjGameState>();
  if (!gs)
    return;
  Destroy();
  gs->good();
}
