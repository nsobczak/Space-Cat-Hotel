#include "Engineer.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Character/Hotel.h"
#include "Character/Mine.h"
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

void  AEngineer::ResetBuildPossibilities()
{
	bCanBuildMine = bCanBuildPurpleCone = bCanBuildYellowCube = bCanBuildRedCylinder = false;
}

void AEngineer::BeginPlay()
{
	Super::BeginPlay();

	ResetBuildPossibilities();
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

AMine* AEngineer::BuildMine(FVector location, EMineNature mineNature)
{
	//TODO: check if enough raw to build
	if (bCanBuildMine && BPOxygenMineToBuild && BPRawMineToBuild)
	{
		FVector NewLocation = location + FVector(0.f, 0.f, 150.f);
		switch (mineNature)
		{
		case EMineNature::FMN_OXYGEN:
			if (BPOxygenMineToBuild)
			{
				return GetWorld()->SpawnActor<AMine>(BPOxygenMineToBuild, NewLocation, FRotator::ZeroRotator);
			}
			return nullptr;
			break;
		default:
			if (BPRawMineToBuild)
			{
				return GetWorld()->SpawnActor<AMine>(BPRawMineToBuild, NewLocation, FRotator::ZeroRotator);
			}
			return nullptr;
			break;
		}
	}
	else
	{
		return nullptr;
	}
}

AHotel* AEngineer::BuildHotel(TSubclassOf <class AHotel> hotelBP, FVector location, EHotelNature hotelNature)
{
	//TODO: check if enough raw to build
	if (hotelBP)
	{
		FVector NewLocation = location + FVector(0.f, 0.f, 150.f);
		return GetWorld()->SpawnActor<AHotel>(hotelBP, NewLocation, FRotator::ZeroRotator);
	}
	else
	{
		return nullptr;
	}
}

AHotel* AEngineer::BuildHotel_PurpleCone(FVector location)
{
	if (bCanBuildPurpleCone && BPPurpleConeHotelToBuild)
	{
		return BuildHotel(BPPurpleConeHotelToBuild, location, EHotelNature::FHN_PURPLE_CONE);
	}
	else
	{
		return nullptr;
	}
}

AHotel* AEngineer::BuildHotel_YellowCube(FVector location)
{
	if (bCanBuildYellowCube && BPYellowCubeHotelToBuild)
	{
		return BuildHotel(BPYellowCubeHotelToBuild, location, EHotelNature::FHN_YELLOW_CUBE);
	}
	else
	{
		return nullptr;
	}
}

AHotel* AEngineer::BuildHotel_RedCylinder(FVector location)
{
	if (bCanBuildRedCylinder && BPRedCylinderHotelToBuild)
	{
		return BuildHotel(BPRedCylinderHotelToBuild, location, EHotelNature::FHN_RED_CYLINDER);
	}
	else
	{
		return nullptr;
	}
}
