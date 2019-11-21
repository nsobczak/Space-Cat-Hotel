#include "Harvester.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Character/Mine.h"
#include "Character/Earth.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "PlayerController/SpaceCatRTSPlayerController.h"



AHarvester::AHarvester()
{
	WNature = EWorkerNature::FWN_HARVESTER;

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	CostOxygenToSpawn = 50;
}

void AHarvester::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEarth::StaticClass(), FoundActors);
	if (FoundActors.Num() > 0)
	{
		Earth = Cast<AEarth>(FoundActors[0]);
	}
	if (!Earth)
	{
		UE_LOG(LogTemp, Error, TEXT("Earth is null"));
	}
}

void AHarvester::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (TargetMine)
	{
		if (HarvestTimer > 0 && bIsBuilding)
			HarvestTimer -= DeltaSeconds;
		WorkAtMine();
	}

}

bool AHarvester::AssignMineToHarvest(AMine* newMine)
{
	TargetMine = newMine;
	if (newMine)
	{
		HarvestTimer = 0;
		if (DEBUG) UE_LOG(LogTemp, Log, TEXT("working at mine"));
		return true;
	}
	else
	{
		bIsBuilding = false;
		return false;
	}
}

void AHarvester::DoNothing()
{
	if (DEBUG) UE_LOG(LogTemp, Log, TEXT("DoNothing called"));
	AssignMineToHarvest(nullptr);
}

void AHarvester::WorkAtMine()
{
	//UE_LOG(LogTemp, Log, TEXT("in WorkAtMine function"));

	if (HarvestTimer <= 0)
	{
		if (0 == ResourceAmount && bIsBuilding)
			ResourceAmount = TargetMine->GetResourceAmountPerHarvest();

		if (ResourceAmount > 0)
		{
			//go to Earth
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), Earth->GetActorLocation());
			bIsBuilding = false;

			//if at earth
			if (FVector::DistSquared(GetActorLocation(), Earth->GetActorLocation()) < Earth->GetSqDistToBeSeenInside())
			{
				if (TargetMine->GetMineNature() == EMineNature::FMN_OXYGEN)
				{
					PC->AddOxygenVal(ResourceAmount);
				}
				else
				{
					PC->AddRawMatVal(ResourceAmount);
				}
				ResourceAmount = 0;
			}
		}

		else
		{
			//go at mine
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), TargetMine->GetActorLocation());

			//if at mine
			if (!bIsBuilding && FVector::DistSquared(GetActorLocation(), TargetMine->GetActorLocation()) < TargetMine->GetSqDistToBeSeenInside())
			{
				bIsBuilding = true;
				HarvestTimer = TargetMine->GetTimeToHarvest();
			}
		}
	}
}
