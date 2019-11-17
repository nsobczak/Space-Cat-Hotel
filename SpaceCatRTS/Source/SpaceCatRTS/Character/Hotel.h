// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Facility.h"
#include "Hotel.generated.h"

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

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mine")
//	EMineNature MNature;

	UFUNCTION(BlueprintPure, Category = "Action")
		FORCEINLINE int32 GetRoomCount() { return RoomCount; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	static int32 HotelCount;

	UPROPERTY(VisibleAnywhere, Category = "Room")
		int32 RoomCount;
};
