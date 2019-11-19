#include "SpaceCatRTSSelectable.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "PlayerController/SpaceCatRTSPlayerController.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"

ASpaceCatRTSSelectable::ASpaceCatRTSSelectable()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	SetCanAffectNavigationGeneration(true);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ASpaceCatRTSSelectable::BeginPlay()
{
	Super::BeginPlay();

	PC = Cast<ASpaceCatRTSPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!PC)
	{
		UE_LOG(LogTemp, Error, TEXT("ASpaceCatRTSSelectable failed to get and cast GetPlayerController in Begin function"));
	}
}


void ASpaceCatRTSSelectable::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}
