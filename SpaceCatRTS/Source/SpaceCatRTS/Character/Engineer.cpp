#include "Engineer.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Character/Hotel.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "PlayerController/SpaceCatRTSPlayerController.h"

AEngineer::AEngineer()
{
	WNature = EWorkerNature::FWN_ENGINEER;

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	CostOxygenToSpawn = 200;
}

void AEngineer::BeginPlay()
{
	Super::BeginPlay();

}

void AEngineer::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (TargetHotel)
	{
		WorkAtHotel();
	}
}

void AEngineer::DoNothing()
{
	UE_LOG(LogTemp, Log, TEXT("DoNothing called"));
	AssignHotelToWork(nullptr);
}

bool AEngineer::AssignHotelToWork(class AHotel* newHotel)
{
	TargetHotel = newHotel;
	if (newHotel)
	{
		UE_LOG(LogTemp, Log, TEXT("working at hotel"));
		return true;
	}
	else
	{
		bIsBuilding = false;
		return false;
	}
}

void AEngineer::WorkAtHotel()
{
	//UE_LOG(LogTemp, Log, TEXT("in WorkAtHotel function"));

	if (!bIsBuilding)
	{
		//go to Hotel
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), TargetHotel->GetActorLocation());

		//if at Hotel
		if (FVector::DistSquared(GetActorLocation(), TargetHotel->GetActorLocation()) < TargetHotel->GetSqDistToBeSeenInside())
		{
			bIsBuilding = true;
			TargetHotel->AddEngineer();
			if (this == PC->GetSelectedActor())
			{
				UE_LOG(LogTemp, Log, TEXT("RemoveSelectedActor"));
				PC->RemoveSelectedActor();
			}
			Destroy();
		}
	}
}