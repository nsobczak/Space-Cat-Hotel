#include "SpaceCatRTSCamera.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerController/SpaceCatRTSPlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/World.h"
#include "WorldSettings/LevelSettings.h"

// Sets default values
ASpaceCatRTSCamera::ASpaceCatRTSCamera()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = false; // Rotate character to moving direction
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 1000.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

}

// Called when the game starts or when spawned
void ASpaceCatRTSCamera::BeginPlay()
{
	Super::BeginPlay();

	LevelSettings = Cast< ALevelSettings>(GetWorld()->GetWorldSettings());
	if (!LevelSettings)
	{
		UE_LOG(LogTemp, Error, TEXT("failed to cast GetWorldSettings() to ALevelSettings"));
	}

	PlayerController = Cast<ASpaceCatRTSPlayerController>(GetController());
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("failed to cast GetController() to ASpaceCatRTSPlayerController"));
	}
}

// Called every frame
void ASpaceCatRTSCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//check if we should move camera
	if (PlayerController && LevelSettings)
	{
		FVector loc = GetActorLocation();
		FVector dir = FVector(PlayerController->bMoveCameraYAxis, PlayerController->bMoveCameraXAxis, 0);
		if (dir.X == -1 && loc.X < LevelSettings->LevelInfo.xMin ||
			dir.X == 1 && loc.X > LevelSettings->LevelInfo.xMax)
		{
			dir.X = 0;
		}
		if (dir.Y == -1 && loc.Y < LevelSettings->LevelInfo.yMin ||
			dir.Y == 1 && loc.Y > LevelSettings->LevelInfo.yMax)
		{
			dir.Y = 0;
		}

		AddActorWorldOffset(Speed*dir);
	}
}


