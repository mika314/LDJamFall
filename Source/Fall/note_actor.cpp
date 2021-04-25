#include "note_actor.h"
#include "cat.h"
#include "log.h"
#include "prj_game_state.h"
#include <Particles/ParticleSystem.h>
#include <Particles/ParticleSystemComponent.h>

ANoteActor::ANoteActor() : explosion(CreateDefaultSubobject<UParticleSystemComponent>("explosion"))
{
  PrimaryActorTick.bCanEverTick = true;
  static ConstructorHelpers::FObjectFinder<UStaticMesh> staticMeshFinder(TEXT("/Game/SM_Mouse"));
  GetStaticMeshComponent()->SetStaticMesh(staticMeshFinder.Object);
  GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
  GetStaticMeshComponent()->SetNotifyRigidBodyCollision(true);

  explosion->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
  static ConstructorHelpers::FObjectFinder<UParticleSystem> psFinder(
    TEXT("/Engine/Tutorial/SubEditors/TutorialAssets/TutorialParticleSystem"));

  explosion->SetTemplate(psFinder.Object);
  explosion->SetAutoActivate(false);
}

auto ANoteActor::BeginPlay() -> void
{
  Super::BeginPlay();
  isDied = false;
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
  if (loc.Z > 500 && !isDied)
  {
    Destroy();
    gs->bad();
  }
}

auto ANoteActor::onHit(AActor *me, AActor *other, FVector impact, const FHitResult &hitResult)
  -> void
{
  LOG("me", me->GetName(), "other", other->GetName());
  if (isDied)
    return;
  auto gs = GetWorld()->GetGameState<APrjGameState>();
  if (!gs)
    return;
  if (!Cast<ACat>(other))
    return;
  gs->good();
  SetLifeSpan(3);
  explosion->Activate();
  isDied = true;
}
