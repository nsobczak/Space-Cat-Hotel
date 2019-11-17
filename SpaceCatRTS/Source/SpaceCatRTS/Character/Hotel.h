#pragma once

#include "CoreMinimal.h"
#include "Character/Facility.h"
#include "Hotel.generated.h"

UENUM(BlueprintType)
enum class EHotelNature : uint8
{
	FHN_PURPLE_CONE UMETA(DisplayName = "Purple cone"),
	FHN_YELLOW_CUBE UMETA(DisplayName = "Yellow cube"),
	FHN_RED_CYLINDER UMETA(DisplayName = "Red cylinder")
};

/**
 *
 */
UCLASS()
class SPACECATRTS_API AHotel : public AFacility
{
	GENERATED_BODY()

public:
	AHotel();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	virtual void  Destroyed() override;

	UFUNCTION(BlueprintPure, Category = "Room")
		FORCEINLINE int32 GetHotelCount() { return HotelCount; }

	static void ResetHotelCount() { HotelCount = 0; }

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mine")
		EHotelNature HNature;

	UFUNCTION(BlueprintPure, Category = "Action")
		FORCEINLINE int32 GetRoomCount() { return RoomCount; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	static int32 HotelCount;

	UPROPERTY(VisibleAnywhere, Category = "Room")
		int32 RoomCount;
};
