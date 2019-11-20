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

	UFUNCTION(BlueprintPure, Category = "Hotel")
		FORCEINLINE int32 GetHotelCount() { return HotelCount; }

	static void ResetHotelCount() { HotelCount = 0; }

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hotel")
		EHotelNature HNature;

	UFUNCTION(BlueprintPure, Category = "Hotel")
		FORCEINLINE int32 GetNeedeedEngineerCount() { return NeededEngineerCount; }

	UFUNCTION(BlueprintPure, Category = "Hotel")
		FORCEINLINE int32 GetCurrentEngineerCount() { return CurrentEngineerCount; }
	UFUNCTION(BlueprintCallable, Category = "Hotel")
		void AddEngineer(int32 val = 1) { CurrentEngineerCount += val; }

	UFUNCTION(BlueprintPure, Category = "HotelRoom")
		FORCEINLINE int32 GetRoomCount() { return RoomCount; }
	UFUNCTION(BlueprintPure, Category = "HotelRoom")
		FORCEINLINE int32 GetRoomBooked() { return RoomBooked; }
	UFUNCTION(BlueprintCallable, Category = "HotelRoom")
		void AddRoom(int32 val = 1);

	UFUNCTION(BlueprintPure, Category = "Hotel")
		FORCEINLINE int32 GetClientCount() { return ClientCount; }
	UFUNCTION(BlueprintPure, Category = "Hotel")
		FORCEINLINE int32 GetFreeRoomCount() { return RoomCount - RoomBooked; }

	UFUNCTION(BlueprintCallable, Category = "Hotel")
		bool AssignRoomToClient();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	static int32 HotelCount;

	class ALevelSettings* LevelSettings;

	UPROPERTY(VisibleAnywhere, Category = "Hotel")
		int32 NeededEngineerCount;
	UPROPERTY(EditAnywhere, Category = "Hotel")
		int32 NumberOfRoomPerEngineer = 2;
	void UpdateNeededEngineerCount();

	UPROPERTY(VisibleAnywhere, Category = "Hotel")
		int32 CurrentEngineerCount;

	UPROPERTY(VisibleAnywhere, Category = "Room")
		int32 RoomCount = 1;
	UPROPERTY(VisibleAnywhere, Category = "Room")
		int32 RoomBooked = 0;
	UPROPERTY(VisibleAnywhere, Category = "Room")
		int32 ClientCount;
};
