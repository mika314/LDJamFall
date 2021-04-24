#include "prj_pawn.h"
#include "cat.h"
#include "log.h"

APrjPawn::APrjPawn() : root(CreateDefaultSubobject<USceneComponent>("root"))
{
  SetRootComponent(root);
  PrimaryActorTick.bCanEverTick = true;
}

auto APrjPawn::BeginPlay() -> void
{
  Super::BeginPlay();
  auto controller = GetInstigatorController();
  controller->SetControlRotation(FRotator{-45, 0, 0});
  SetActorRotation(FRotator{-45, 0, 0});

  FActorSpawnParameters param;
  param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
  cat = GetWorld()->SpawnActor<ACat>(ACat::StaticClass(), FVector{}, FRotator{}, param);
}

auto APrjPawn::SetupPlayerInputComponent(class UInputComponent *in) -> void
{
  Super::SetupPlayerInputComponent(in);
  in->BindAction("Down", IE_Pressed, this, &APrjPawn::down);
  in->BindAction("Left", IE_Pressed, this, &APrjPawn::left);
  in->BindAction("Right", IE_Pressed, this, &APrjPawn::right);
  in->BindAction("Up", IE_Pressed, this, &APrjPawn::up);
}

auto APrjPawn::down() -> void
{
  LOG("down");
  cat->down();
}
auto APrjPawn::left() -> void
{
  LOG("left");
  cat->left();
}
auto APrjPawn::right() -> void
{
  LOG("right");
  cat->right();
}
auto APrjPawn::up() -> void
{
  LOG("up");
  cat->up();
}
