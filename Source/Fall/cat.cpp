#include "cat.h"
#include <Components/CapsuleComponent.h>

ACat::ACat()
{
  PrimaryActorTick.bCanEverTick = true;
  ConstructorHelpers::FObjectFinder<USkeletalMesh> meshFinder(TEXT("/Game/SK_Cat"));
  auto mesh = GetSkeletalMeshComponent();
  mesh->SetSkeletalMesh(meshFinder.Object);
  mesh->SetCollisionProfileName(TEXT("Ragdoll"));
  mesh->SetEnableGravity(false);
  mesh->SetSimulatePhysics(true);
  mesh->SetNotifyRigidBodyCollision(true);
}

auto ACat::Tick(float dt) -> void
{
  Super::Tick(dt);
  auto mesh = GetSkeletalMeshComponent();
  const auto loc = GetActorLocation();
  const auto vel = mesh->GetPhysicsLinearVelocity();
  mesh->AddImpulse((-80 * loc - 40.f * vel) * 120 * dt);
}

auto ACat::down() -> void
{
  auto mesh = GetSkeletalMeshComponent();
  const auto loc = GetActorLocation();
  mesh->AddImpulse((FVector{-300, 0, 0} - loc) * 8000);
}
auto ACat::left() -> void
{
  auto mesh = GetSkeletalMeshComponent();
  const auto loc = GetActorLocation();
  mesh->AddImpulse((FVector{0, -300, 0} - loc) * 8000);
}
auto ACat::right() -> void
{
  auto mesh = GetSkeletalMeshComponent();
  const auto loc = GetActorLocation();
  mesh->AddImpulse((FVector{0, 300, 0} - loc) * 8000);
}
auto ACat::up() -> void
{
  auto mesh = GetSkeletalMeshComponent();
  const auto loc = GetActorLocation();
  mesh->AddImpulse((FVector{300, 0, 0} - loc) * 8000);
}
