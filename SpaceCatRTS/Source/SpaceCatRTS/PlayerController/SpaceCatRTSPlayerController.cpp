#include "SpaceCatRTSPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "Character/SpaceCatRTSSelectable.h"
#include "Character/Facility.h"
#include "Character/Mine.h"
#include "Character/Hotel.h"
#include "Character/Harvester.h"
#include "Character/Engineer.h"
#include "Engine/World.h"
#include "Engine/GameViewportClient.h"

#define ECC_ClickableLeft ECC_GameTraceChannel1
#define ECC_ClickableRight ECC_GameTraceChannel2

ASpaceCatRTSPlayerController::ASpaceCatRTSPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ASpaceCatRTSPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}

	float LocationX, LocationY;
	GetMousePosition(LocationX, LocationY);
	//UE_LOG(LogTemp, Log, TEXT("MousePos: X = %f | Y = %f"), LocationX, LocationY);
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	//UE_LOG(LogTemp, Log, TEXT("ViewportSize: X = %f | Y = %f"), ViewportSizeX, ViewportSizeY);

	float xPercentage = LocationX / ViewportSizeX;
	float yPercentage = LocationY / ViewportSizeY;
	bMoveCameraXAxis = xPercentage < 0.04 ? -1 : xPercentage > 0.96 ? 1 : 0;
	bMoveCameraYAxis = yPercentage < 0.04 ? 1 : yPercentage > 0.96 ? -1 : 0;
}

void ASpaceCatRTSPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &ASpaceCatRTSPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &ASpaceCatRTSPlayerController::OnSetDestinationReleased);

	InputComponent->BindAction("SelectPawn", IE_Pressed, this, &ASpaceCatRTSPlayerController::OnSelectPawnPressed);
	InputComponent->BindAction("SelectPawn", IE_Released, this, &ASpaceCatRTSPlayerController::OnSelectPawnReleased);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ASpaceCatRTSPlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ASpaceCatRTSPlayerController::MoveToTouchLocation);
}


void ASpaceCatRTSPlayerController::MoveToMouseCursor()
{
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(Hit.ImpactPoint);
	}
}

void ASpaceCatRTSPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void ASpaceCatRTSPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	if (SelectedActor && SelectedActor->SNature == ESelectableNature::FSN_WORKER)
	{
		float const Distance = FVector::Dist(DestLocation, SelectedActor->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if ((Distance > 120.0f))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(SelectedActor->GetController(), DestLocation);
			if (DEBUG) UE_LOG(LogTemp, Log, TEXT("moving selected actor"));
		}
	}
}

void ASpaceCatRTSPlayerController::OnSetDestinationPressed()
{
	if (SelectedActor)
	{
		// set flag to keep updating destination until released
		bMoveToMouseCursor = true;

		// Trace to see what is under the mouse cursor
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_ClickableRight, false, Hit);

		AHarvester* const selectedHarvester = Cast<AHarvester>(SelectedActor);
		AEngineer* const selectedEngineer = Cast<AEngineer>(SelectedActor);

		if (Hit.bBlockingHit)
		{
			AMine* const newMine = Cast<AMine>(Hit.GetActor());
			AHotel* const newHotel = Cast<AHotel>(Hit.GetActor());
			if (AFacility* const newFacility = Cast<AFacility>(Hit.GetActor()))
			{
				if (DEBUG) UE_LOG(LogTemp, Log, TEXT("We right clicked on a facility"));
				if (newMine && selectedHarvester)
				{
					if (DEBUG) UE_LOG(LogTemp, Log, TEXT("Right clicked facility is a mine"));
					selectedHarvester->AssignMineToHarvest(newMine);
				}
				if (newHotel && selectedEngineer)
				{
					if (DEBUG) UE_LOG(LogTemp, Log, TEXT("Right clicked facility is a mine"));
					selectedEngineer->AssignHotelToWork(newHotel);
				}
			}
		}
		else
		{
			//reset selected pawn
			if (selectedHarvester)
			{
				selectedHarvester->DoNothing();
			}
			if (selectedEngineer)
			{
				selectedEngineer->DoNothing();
			}
		}
	}

}

void ASpaceCatRTSPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}

void ASpaceCatRTSPlayerController::OnSelectPawnPressed()
{
	// We click, unposses current
	if (SelectedActor)
	{
		SelectedActor = nullptr;
	}

	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_ClickableLeft, false, Hit);

	if (Hit.bBlockingHit)
	{
		if (ASpaceCatRTSSelectable* const newActor = Cast<ASpaceCatRTSSelectable>(Hit.GetActor()))
		{
			if (DEBUG) UE_LOG(LogTemp, Log, TEXT("We selected a clickable actor"));
			SelectedActor = newActor;
		}

	}
}

void ASpaceCatRTSPlayerController::OnSelectPawnReleased()
{

}