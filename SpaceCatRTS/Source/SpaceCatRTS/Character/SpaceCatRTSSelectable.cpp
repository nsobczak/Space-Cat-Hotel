#include "SpaceCatRTSSelectable.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "PlayerController/SpaceCatRTSPlayerController.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "Actor/ActorWithMeshBase.h"

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

	// Highlight class
	static ConstructorHelpers::FClassFinder<AActorWithMeshBase> selectionHighlightAsset(TEXT("/Game/Selectable/BPSelectionHighlight"));
	if (selectionHighlightAsset.Succeeded())
	{
		SelectionHighlightClass = selectionHighlightAsset.Class;
	}

	// Highlight materials
	ConstructorHelpers::FObjectFinder<UMaterialInterface> matHighlight(TEXT("/Game/Selectable/M_SelectionHighlight"));
	if (matHighlight.Succeeded())
	{
		Mat_Highlighted = matHighlight.Object;
	}
	ConstructorHelpers::FObjectFinder<UMaterialInterface> matInvisible(TEXT("/Game/Geometry/M_invisible"));
	if (matInvisible.Succeeded())
	{
		Mat_NotHighlighted = matInvisible.Object;
	}

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

	// Highlight actor
	FVector NewLocation = GetActorLocation() + SelectionHighlightPostion;
	SelectionHighlight = GetWorld()->SpawnActor<AActorWithMeshBase>(SelectionHighlightClass, NewLocation, FRotator::ZeroRotator);
	RemoveHighlight();
}


void ASpaceCatRTSSelectable::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (SelectionHighlight)
	{
		SelectionHighlight->SetActorLocation(this->GetActorLocation() + SelectionHighlightPostion);
	}
}

void ASpaceCatRTSSelectable::Destroyed()
{
	RemoveHighlight();
}


void ASpaceCatRTSSelectable::Highlight()
{
	if (SelectionHighlight)
	{
		SelectionHighlight->GetBaseMesh()->SetMaterial(0, Mat_Highlighted);
	}
}

void ASpaceCatRTSSelectable::RemoveHighlight()
{
	if (SelectionHighlight)
	{
		SelectionHighlight->GetBaseMesh()->SetMaterial(0, Mat_NotHighlighted);
	}
}