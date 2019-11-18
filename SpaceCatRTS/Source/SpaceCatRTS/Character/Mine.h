// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Facility.h"
#include "Mine.generated.h"

UENUM(BlueprintType)
enum class EMineNature : uint8
{
	FMN_OXYGEN UMETA(DisplayName = "Oxygen"),
	FMN_RAW UMETA(DisplayName = "Raw materials")
};

/**
 *
 */
UCLASS()
class SPACECATRTS_API AMine : public AFacility
{
	GENERATED_BODY()

public:
	AMine();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintPure, Category = "Mine")
		FORCEINLINE int32 GetMineCount() { return MineCount; }

	static void ResetMineCount() { MineCount = 0; }

	UFUNCTION(BlueprintPure, Category = "Mine")
		FORCEINLINE EMineNature GetMineNature() { return MNature; }

	UFUNCTION(BlueprintPure, Category = "Mine")
		FORCEINLINE int32 GetResourceAmountPerHarvest() { return ResourceAmountPerHarvest; }

	UFUNCTION(BlueprintPure, Category = "Mine")
		FORCEINLINE float GetTimeToHarvest() { return TimeToHarvest; };


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	static int32 MineCount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mine")
		EMineNature MNature;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mine")
		int32 ResourceAmountPerHarvest = 10;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mine")
		float TimeToHarvest = 5.f;
};
