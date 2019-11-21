#pragma once

#include "CoreMinimal.h"
#include "Character/Hotel.h"
#include "StructClientNeed.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct FStructClientNeed
{
	GENERATED_USTRUCT_BODY()

public:
	FStructClientNeed() :RoomCount(1) {}
	FStructClientNeed(EHotelNature newHotelNature, int32 newRoomCount) :
		HotelNature(newHotelNature), RoomCount(newRoomCount)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Need")
		EHotelNature HotelNature = EHotelNature::FHN_PURPLE_CONE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Need")
		int32 RoomCount = 1;
};