// Copyright Epic Games, Inc. All Rights Reserved.

#include "fall_game_mode_base.h"
#include "prj_game_state.h"
#include "prj_hud.h"
#include "prj_pawn.h"

AFallGameModeBase::AFallGameModeBase()
{
  HUDClass = APrjHud::StaticClass();
  GameStateClass = APrjGameState::StaticClass();
  DefaultPawnClass = APrjPawn::StaticClass();
}
