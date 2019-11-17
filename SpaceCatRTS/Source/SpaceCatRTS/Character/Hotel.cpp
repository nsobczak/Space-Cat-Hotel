#include "Hotel.h"

int32 AHotel::HotelCount = 0;

AHotel::AHotel()
{
	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AHotel::BeginPlay()
{
	Super::BeginPlay();

	AHotel::HotelCount++;
}

void AHotel::Destroyed()
{
	AHotel::HotelCount--;
}

void AHotel::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

