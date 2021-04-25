#include "main_menu_pawn.h"

AMainMenuPawn::AMainMenuPawn() : root(CreateDefaultSubobject<USceneComponent>("root"))
{
  SetRootComponent(root);
  PrimaryActorTick.bCanEverTick = true;
}

auto AMainMenuPawn::Tick(float dt) -> void
{
  Super::Tick(dt);
  auto controller = GetInstigatorController();
  const auto rot = GetActorRotation() + dt * FRotator{0, 1, 0};
  controller->SetControlRotation(rot);
  SetActorRotation(rot);
}
