#include "main_menu_game_mode.h"
#include "main_menu_hud.h"
#include "main_menu_pawn.h"

AMainMenuGameMode::AMainMenuGameMode()
{
  HUDClass = AMainMenuHud::StaticClass();
  DefaultPawnClass = AMainMenuPawn::StaticClass();
}
