#include "Engineer.h"
#include "UObject/ConstructorHelpers.h"
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

	// Default blueprints
	static ConstructorHelpers::FClassFinder<AMine> oxMineBP(TEXT("/Game/Selectable/Facility/BPMineOxygen"));
	if (oxMineBP.Succeeded())
	{
		BPOxygenMineToBuild = oxMineBP.Class;
	}
	static ConstructorHelpers::FClassFinder<AMine> rawMineBP(TEXT("/Game/Selectable/Facility/BPMineRawMat"));
	if (rawMineBP.Succeeded())
	{
		BPRawMineToBuild = rawMineBP.Class;
	}
	static ConstructorHelpers::FClassFinder<AHotel> hotelPCBP(TEXT("/Game/Selectable/Facility/BPHotelPurpleCone"));
	if (hotelPCBP.Succeeded())
	{
		BPPurpleConeHotelToBuild = hotelPCBP.Class;
	}
	static ConstructorHelpers::FClassFinder<AHotel> hotelYCBP(TEXT("/Game/Selectable/Facility/BPHotelYellowCube"));
	if (hotelYCBP.Succeeded())
	{
		BPYellowCubeHotelToBuild = hotelYCBP.Class;
	}
	static ConstructorHelpers::FClassFinder<AHotel> hotelRCBP(TEXT("/Game/Selectable/Facility/BPHotelRedCylinder"));
	if (hotelRCBP.Succeeded())
	{
		BPRedCylinderHotelToBuild = hotelRCBP.Class;
	}

	CostOxygenToSpawn = 80;
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
	if (DEBUG) UE_LOG(LogTemp, Log, TEXT("DoNothing called"));
	AssignHotelToWork(nullptr);
}

bool AEngineer::AssignHotelToWork(class AHotel* newHotel)
{
	TargetHotel = newHotel;
	if (newHotel)
	{
		if (DEBUG) UE_LOG(LogTemp, Log, TEXT("working at hotel"));
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
		const FVector dest = FVector(TargetHotel->GetActorLocation().X, TargetHotel->GetActorLocation().Y, GetActorLocation().Z);
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), dest);

		//if at Hotel
		if (FVector::DistSquared(GetActorLocation(), TargetHotel->GetActorLocation()) < TargetHotel->GetSqDistToBeSeenInside())
		{
			bIsBuilding = true;
			TargetHotel->AddEngineer();
			if (this == PC->GetSelectedActor())
			{
				if (DEBUG) UE_LOG(LogTemp, Log, TEXT("RemoveSelectedActor"));
				PC->RemoveSelectedActor();
			}
			Destroy();
		}
	}
}

AMine* AEngineer::BuildMine(FVector location, EMineNature mineNature)
{
	if (bCanBuildMine && BPOxygenMineToBuild && BPRawMineToBuild)
	{
		FVector NewLocation = location + FVector(0.f, 0.f, 150.f);
		switch (mineNature)
		{
		case EMineNature::FMN_OXYGEN:
			if (BPOxygenMineToBuild && PC && BPOxygenMineToBuild.GetDefaultObject()
				&& PC->GetOxygenVal() >= BPOxygenMineToBuild.GetDefaultObject()->CostOxygenToSpawn
				&& PC->GetRawMatVal() >= BPOxygenMineToBuild.GetDefaultObject()->CostRawToSpawn)
			{
				if (AMine* const newMine = GetWorld()->SpawnActor<AMine>(BPOxygenMineToBuild, NewLocation, FRotator::ZeroRotator))
				{
					PC->AddOxygenVal(-BPOxygenMineToBuild.GetDefaultObject()->CostOxygenToSpawn);
					PC->AddRawMatVal(-BPOxygenMineToBuild.GetDefaultObject()->CostRawToSpawn);
					return newMine;
				}
			}
			break;
		default:
			if (BPRawMineToBuild && PC && BPRawMineToBuild.GetDefaultObject()
				&& PC->GetOxygenVal() >= BPRawMineToBuild.GetDefaultObject()->CostOxygenToSpawn
				&& PC->GetRawMatVal() >= BPRawMineToBuild.GetDefaultObject()->CostRawToSpawn)
			{
				if (AMine* const newMine = GetWorld()->SpawnActor<AMine>(BPRawMineToBuild, NewLocation, FRotator::ZeroRotator))
				{
					PC->AddOxygenVal(-BPRawMineToBuild.GetDefaultObject()->CostOxygenToSpawn);
					PC->AddRawMatVal(-BPRawMineToBuild.GetDefaultObject()->CostRawToSpawn);
					return newMine;
				}
			}
			break;
		}
	}
	return nullptr;
}

AHotel* AEngineer::BuildHotel(TSubclassOf <class AHotel> hotelBP, FVector location, EHotelNature hotelNature)
{
	if (hotelBP)
	{
		FVector NewLocation = location + FVector(0.f, 0.f, 150.f);
		return GetWorld()->SpawnActor<AHotel>(hotelBP, NewLocation, FRotator::ZeroRotator);
	}
	return nullptr;
}

AHotel* AEngineer::BuildHotel_PurpleCone(FVector location)
{
	if (bCanBuildPurpleCone && BPPurpleConeHotelToBuild && PC && BPPurpleConeHotelToBuild.GetDefaultObject()
		&& PC->GetOxygenVal() >= BPPurpleConeHotelToBuild.GetDefaultObject()->CostOxygenToSpawn
		&& PC->GetRawMatVal() >= BPPurpleConeHotelToBuild.GetDefaultObject()->CostRawToSpawn)
	{
		if (AHotel* const newHotel = BuildHotel(BPPurpleConeHotelToBuild, location, EHotelNature::FHN_PURPLE_CONE))
		{
			PC->AddOxygenVal(-BPPurpleConeHotelToBuild.GetDefaultObject()->CostOxygenToSpawn);
			PC->AddRawMatVal(-BPPurpleConeHotelToBuild.GetDefaultObject()->CostRawToSpawn);
			return newHotel;
		}
	}
	return nullptr;
}

AHotel* AEngineer::BuildHotel_YellowCube(FVector location)
{
	if (bCanBuildYellowCube && BPYellowCubeHotelToBuild && PC && BPYellowCubeHotelToBuild.GetDefaultObject()
		&& PC->GetOxygenVal() >= BPYellowCubeHotelToBuild.GetDefaultObject()->CostOxygenToSpawn
		&& PC->GetRawMatVal() >= BPYellowCubeHotelToBuild.GetDefaultObject()->CostRawToSpawn)
	{
		if (AHotel* const newHotel = BuildHotel(BPYellowCubeHotelToBuild, location, EHotelNature::FHN_YELLOW_CUBE))
		{
			PC->AddOxygenVal(-BPYellowCubeHotelToBuild.GetDefaultObject()->CostOxygenToSpawn);
			PC->AddRawMatVal(-BPYellowCubeHotelToBuild.GetDefaultObject()->CostRawToSpawn);
			return newHotel;
		}
	}
	return nullptr;
}

AHotel* AEngineer::BuildHotel_RedCylinder(FVector location)
{
	if (bCanBuildRedCylinder && BPRedCylinderHotelToBuild && PC && BPRedCylinderHotelToBuild.GetDefaultObject()
		&& PC->GetOxygenVal() >= BPRedCylinderHotelToBuild.GetDefaultObject()->CostOxygenToSpawn
		&& PC->GetRawMatVal() >= BPRedCylinderHotelToBuild.GetDefaultObject()->CostRawToSpawn)
	{
		if (AHotel* const newHotel = BuildHotel(BPRedCylinderHotelToBuild, location, EHotelNature::FHN_RED_CYLINDER))
		{
			PC->AddOxygenVal(-BPRedCylinderHotelToBuild.GetDefaultObject()->CostOxygenToSpawn);
			PC->AddRawMatVal(-BPRedCylinderHotelToBuild.GetDefaultObject()->CostRawToSpawn);
			return newHotel;
		}
	}
	return nullptr;
}
