#include "GMLevel.h"
#include "PlayerController/SpaceCatRTSPlayerController.h"
#include "Character/SpaceCatRTSCamera.h"
#include "Character/Hotel.h"
#include "Character/Mine.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "WorldSettings/LevelSettings.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "HUDClass/HUDMain.h"


AGMLevel::AGMLevel()
{
	PrimaryActorTick.bCanEverTick = true; // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bTickEvenWhenPaused = false;

	// use our custom PlayerController class
	PlayerControllerClass = ASpaceCatRTSPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/BPCamera"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

}

void AGMLevel::SetupGame()
{

	LevelSettings = Cast< ALevelSettings>(GetWorld()->GetWorldSettings());
	if (!LevelSettings)
	{
		UE_LOG(LogTemp, Error, TEXT("failed to cast GetWorldSettings() to ALevelSettings"));
	}
	else
	{
		GameTimer = LevelSettings->LevelInfo.LevelTimeLimit;


		ASpaceCatRTSPlayerController* pc = Cast<ASpaceCatRTSPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if (pc)
		{
			pc->SetOxygenVal(0);
			pc->SetRawMatVal(0);

			pc->SetInputMode(FInputModeGameAndUI().SetHideCursorDuringCapture(false));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("gamemode begin failed to cast GetPlayerController to ASpaceCatRTSPlayerController"));
		}

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
	else
	{
		HandleGoals();
	}
}



void AGMLevel::GameOver()
{
	if (ASpaceCatRTSPlayerController* pc = Cast<ASpaceCatRTSPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		AHUDMain * currentHUD = Cast<AHUDMain>(pc->GetHUD());
		if (currentHUD && !currentHUD->IsShowingWidget(EHudWidget::FHW_END))
		{
			UE_LOG(LogTemp, Log, TEXT("Game Over"));

			pc->SetInputMode(FInputModeUIOnly());
			pc->SetCinematicMode(true, false, false, true, true);
			pc->bMoveCameraWithCursor = false;
			currentHUD->ShowEndingWidget();
		}
	}
}

void AGMLevel::HandleGoals()
{
	for (size_t i = 0; i < LevelSettings->Goals.Num(); ++i)
	{
		if (LevelSettings->Goals[i].IsHidden())
		{
			if (GameTimer < LevelSettings->Goals[i].TimeLeftWhenGoalAppears)
			{
				LevelSettings->Goals[i].SetActive();
			}
		}
		else if (LevelSettings->Goals[i].IsActive())
		{
			float timeLeft = LevelSettings->Goals[i].GoalTimeToComplete - (LevelSettings->Goals[i].TimeLeftWhenGoalAppears - GameTimer);
			if (0 >= timeLeft)
			{
				LevelSettings->Goals[i].SetMissed();
			}
		}
	}
}
