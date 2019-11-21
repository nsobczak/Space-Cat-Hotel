#include "SpaceCatRTSPlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/DecalComponent.h"
#include "Materials/Material.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "Character/SpaceCatRTSSelectable.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

#include "Character/Facility.h"
#include "Character/Mine.h"
#include "Character/Hotel.h"
#include "Character/Harvester.h"
#include "Character/Engineer.h"
#include "Actor/FacilitySite.h"
#include "Engine/World.h"
#include "Engine/GameViewportClient.h"
#include "UMG/Public/UMG.h"



#define ECC_ClickableLeft ECC_GameTraceChannel1
#define ECC_ClickableRight ECC_GameTraceChannel2
#define ECC_CanBeHighlighted ECC_GameTraceChannel3

ASpaceCatRTSPlayerController::ASpaceCatRTSPlayerController()
{
	bShowMouseCursor = false;
	DefaultMouseCursor = EMouseCursor::None;
	bMoveCameraWithCursor = true;
}

void ASpaceCatRTSPlayerController::SetMouseCursorWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (NewWidgetClass != nullptr)
	{
		if (MouseCursorWidget)
		{
			MouseCursorWidget->RemoveFromViewport();
		}

		MouseCursorWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (MouseCursorWidget != nullptr)
		{
			MouseCursorWidget->AddToViewport();
		}
	}
}

void ASpaceCatRTSPlayerController::BeginPlay()
{
	SetInputMode(FInputModeGameAndUI().SetHideCursorDuringCapture(false));

	SetMouseCursorWidget(MouseCursorWidgetClass);
}

void ASpaceCatRTSPlayerController::HandleCamera(float LocationX, float LocationY)
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	//UE_LOG(LogTemp, Log, TEXT("ViewportSize: X = %f | Y = %f"), ViewportSizeX, ViewportSizeY);
	float xPercentage = LocationX / ViewportSizeX;
	float yPercentage = LocationY / ViewportSizeY;
	bMoveCameraXAxis = xPercentage < 0.075 ? -1 : xPercentage > 0.925 ? 1 : 0;
	bMoveCameraYAxis = yPercentage < 0.075 ? 1 : yPercentage > 0.925 ? -1 : 0;
}

void ASpaceCatRTSPlayerController::HandleFacilityHighlight()
{
	if (SelectedActor)
	{
		AEngineer* const selectedEngineer = Cast<AEngineer>(SelectedActor);
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_CanBeHighlighted, false, Hit);
		if (Hit.bBlockingHit && selectedEngineer)
		{
			// We are hovering an something
			AFacilitySite* const site = Cast<AFacilitySite>(Hit.GetActor());
			bool canBuildHotel = selectedEngineer->GetCanBuildPurpleCone()
				|| selectedEngineer->GetCanBuildRedCylinder() || selectedEngineer->GetCanBuildYellowCube();
			if (site &&
				(site->IsMineFacility() && selectedEngineer->GetCanBuildMine()
					|| site->IsHotelFacility() && canBuildHotel))
			{
				site->Highlight();
			}
		}
	}
}

void ASpaceCatRTSPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
		MoveToMouseCursor();

	float LocationX, LocationY;
	GetMousePosition(LocationX, LocationY);

	// Mouse cursor
	if (MouseCursorWidget)
		MouseCursorWidget->SetPositionInViewport(FVector2D(LocationX, LocationY));

	if (bMoveCameraWithCursor)
		HandleCamera(LocationX, LocationY);

	HandleFacilityHighlight();
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
			if (DEBUG) 	UE_LOG(LogTemp, Log, TEXT("moving selected actor"));
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
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_ClickableLeft, false, Hit);

	// We click, unposses current or build
	if (SelectedActor)
	{
		AEngineer*const oldEngineer = Cast<AEngineer>(SelectedActor);
		if (oldEngineer && Hit.bBlockingHit)
		{
			if (AFacilitySite* const newSite = Cast<AFacilitySite>(Hit.GetActor()))
			{
				if (DEBUG) UE_LOG(LogTemp, Log, TEXT("We try building"));
				switch (newSite->GetConstructibleFacilityNature())
				{
				case EFacilityNature::FFN_MINE:
					if (oldEngineer->GetCanBuildMine())
					{
						if (oldEngineer->BuildMine(newSite->GetActorLocation(), newSite->GetConstructibleMineNature()))
							newSite->Destroy();
					}
					break;
				case EFacilityNature::FFN_HOTEL:
					if (oldEngineer->GetCanBuildPurpleCone())
					{
						if (oldEngineer->BuildHotel_PurpleCone(newSite->GetActorLocation()))
							newSite->Destroy();
					}
					else if (oldEngineer->GetCanBuildRedCylinder())
					{
						if (oldEngineer->BuildHotel_RedCylinder(newSite->GetActorLocation()))
							newSite->Destroy();
					}
					else if (oldEngineer->GetCanBuildYellowCube())
					{
						if (oldEngineer->BuildHotel_YellowCube(newSite->GetActorLocation()))
							newSite->Destroy();
					}
					break;
				default:
					oldEngineer->ResetBuildPossibilities();
					break;
				}
			}
			else
			{
				oldEngineer->ResetBuildPossibilities();
				oldEngineer->RemoveHighlight();
			}
		}
		else
		{
			SelectedActor->RemoveHighlight();
			SelectedActor = nullptr;
		}
	}

	if (Hit.bBlockingHit)
	{
		if (ASpaceCatRTSSelectable* const newSelectable = Cast<ASpaceCatRTSSelectable>(Hit.GetActor()))
		{
			if (DEBUG) UE_LOG(LogTemp, Log, TEXT("We selected a clickable actor"));
			SelectedActor = newSelectable;
			SelectedActor->Highlight();
		}
	}
}

void ASpaceCatRTSPlayerController::OnSelectPawnReleased()
{

}