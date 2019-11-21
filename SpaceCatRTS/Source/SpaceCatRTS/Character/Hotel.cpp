#include "Hotel.h"
#include "Engine/World.h"
#include "WorldSettings/LevelSettings.h"
#include "PlayerController/SpaceCatRTSPlayerController.h"

int32 AHotel::HotelCount = 0;

AHotel::AHotel()
{
	FNature = EFacilityNature::FFN_HOTEL;
	DistToBeSeenInside = 200.f;

	CostOxygenToSpawn = 20;
	CostRawToSpawn = 100;
	CostOxygenToAddRoom = 10;
	CostRawToAddRoom = 10;

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AHotel::BeginPlay()
{
	Super::BeginPlay();

	AHotel::HotelCount++;
	RoomCount = 1;
	UpdateNeededEngineerCount();

	LevelSettings = Cast< ALevelSettings>(GetWorld()->GetWorldSettings());
	if (!LevelSettings)
	{
		UE_LOG(LogTemp, Error, TEXT("failed to cast GetWorldSettings() to ALevelSettings"));
	}
}

void AHotel::Destroyed()
{
	AHotel::HotelCount--;
}

void AHotel::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AHotel::UpdateNeededEngineerCount()
{
	NeededEngineerCount = FMath::Max(1, RoomCount / NumberOfRoomPerEngineer);
}

bool AHotel::AssignRoomToClient()
{
	//TODO: look into active goal list for goals with this hotel
	// in these goals looks for 1st one that can be completed
	// return true if one was found false otherwise

	if (LevelSettings)
	{
		for (size_t i = 0; i < LevelSettings->Goals.Num(); ++i)
		{
			if (LevelSettings->Goals[i].IsActive())
			{
				bool canAddClient = false;
				int32 roomCountToAdd = 0;
				for (size_t j = 0; j < LevelSettings->Goals[i].ClientNeeds.Num(); ++j)
				{
					int32 freeRoomCount = this->RoomCount - this->RoomBooked;
					if (LevelSettings->Goals[i].ClientNeeds[j].HotelNature == this->HNature
						&& LevelSettings->Goals[i].ClientNeeds[j].RoomCount <= freeRoomCount
						&& CurrentEngineerCount >= FMath::Max(1, (1 + this->RoomBooked + LevelSettings->Goals[i].ClientNeeds[j].RoomCount) / NumberOfRoomPerEngineer))
					{
						canAddClient = true;
						roomCountToAdd += LevelSettings->Goals[i].ClientNeeds[j].RoomCount;
					}
				}
				if (canAddClient)
				{
					ClientCount++;
					RoomBooked += roomCountToAdd;
					LevelSettings->Goals[i].SetCompleted();
					return true;
				}
			}
		}
	}

	return false;
}

bool AHotel::AddRoom(int32 val)
{
	if (PC && PC->GetOxygenVal() >= CostOxygenToAddRoom && PC->GetRawMatVal() >= CostRawToAddRoom)
	{
		RoomCount += val;
		UpdateNeededEngineerCount();
		PC->AddOxygenVal(-CostOxygenToAddRoom);
		PC->AddRawMatVal(-CostRawToAddRoom);
		return true;
	}
	return false;
}