#include "hole_section.h"

AHoleSection::AHoleSection()
{
  PrimaryActorTick.bCanEverTick = true;
  static ConstructorHelpers::FObjectFinder<UStaticMesh> staticMeshFinder(TEXT("/Game/SM_Hole"));
  auto mesh = GetStaticMeshComponent();
  mesh->SetStaticMesh(staticMeshFinder.Object);
  mesh->SetMobility(EComponentMobility::Movable);
  mesh->SetCollisionProfileName(TEXT("NoCollision"));
}

auto AHoleSection::Tick(float dt) -> void
{
  Super::Tick(dt);
  const auto loc = GetActorLocation();
  if (loc.Z < 4000)
    SetActorLocation(loc + FVector{0, 0, dt * 1000.f});
  else
    SetActorLocation(FVector{0, 0, -10000});
}