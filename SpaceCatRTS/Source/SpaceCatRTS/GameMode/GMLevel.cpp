#include "GMLevel.h"
#include "PlayerController/SpaceCatRTSPlayerController.h"
#include "Character/SpaceCatRTSCamera.h"
#include "Character/Hotel.h"
#include "Character/Mine.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "WorldSettings/LevelSettings.h"


AGMLevel::AGMLevel()
{
	PrimaryActorTick.bCanEverTick = true; // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bTickEvenWhenPaused = false;

	// use our custom PlayerController class
	PlayerControllerClass = ASpaceCatRTSPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/PlayerController/BPCamera"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

}

void AGMLevel::SetupGame()
{

	ALevelSettings* LevelSettings = Cast< ALevelSettings>(GetWorld()->GetWorldSettings());
	if (!LevelSettings)
	{
		UE_LOG(LogTemp, Error, TEXT("failed to cast GetWorldSettings() to ALevelSettings"));
	}
	else
	{
		GameTimer = LevelSettings->LevelInfo.LevelTimeLimit;

		Oxygen = 0;
		AHotel::ResetHotelCount();
		AMine::ResetMineCount();
	}
}


void AGMLevel::BeginPlay()
{
	SetupGame();
}

void AGMLevel::Tick(float DeltaTime)
{
	GameTimer -= DeltaTime;

	if (GameTimer <= 0)
	{
		GameOver();
	}
}

void AGMLevel::GameOver()
{
	UE_LOG(LogTemp, Log, TEXT("Game Over"));

}

float AGMLevel::GetCurrentGameTimer() { return GameTimer; }
int32 AGMLevel::GetCurrentGameTimerMinutes() { return (int32)GameTimer / 60; }
int32 AGMLevel::GetCurrentGameTimerSeconds() { return (int32)GameTimer % 60; }
