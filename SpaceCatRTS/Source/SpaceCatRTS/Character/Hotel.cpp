#include "Hotel.h"

int32 AHotel::HotelCount = 0;

AHotel::AHotel()
{
	FNature = EFacilityNature::FFN_HOTEL;

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
	NeededEngineerCount = 1 + RoomCount / NumberOfRoomPerEngineer;
}

bool AHotel::AssignRoomToClient()
{
	//TODO: addapt with goal class
	if (GetFreeRoomCount() > 0 && CurrentEngineerCount >= 1 + (ClientCount + 1) / NumberOfRoomPerEngineer)
	{
		ClientCount++;
		return true;
	}
	else
	{
		return false;
	}
}

void AHotel::AddRoom(int32 val)
{
	RoomCount += val;
	UpdateNeededEngineerCount();
}