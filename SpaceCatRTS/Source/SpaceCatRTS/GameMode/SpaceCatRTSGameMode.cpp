#include "SpaceCatRTSGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "PlayerController/SpaceCatRTSPlayerController.h"
#include "Components/AudioComponent.h"
#include "Engine/World.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"

ASpaceCatRTSGameMode::ASpaceCatRTSGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ASpaceCatRTSPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/BPCamera"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ASpaceCatRTSGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (MapTheme)
	{
		CurrentTheme_AC = UGameplayStatics::SpawnSound2D(GetWorld(), MapTheme);
		CurrentTheme_AC->SetUISound(true);
		CurrentTheme_AC->FadeIn(1.0f);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Audio: MapTheme is null"));
	}
}