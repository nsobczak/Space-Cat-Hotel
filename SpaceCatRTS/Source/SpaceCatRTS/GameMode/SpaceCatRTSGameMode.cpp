#include "SpaceCatRTSGameMode.h"
#include "PlayerController/SpaceCatRTSPlayerController.h"
//#include "Character/SpaceCatRTSWorker.h"
#include "UObject/ConstructorHelpers.h"

ASpaceCatRTSGameMode::ASpaceCatRTSGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ASpaceCatRTSPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/PlayerController/BPCamera"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}