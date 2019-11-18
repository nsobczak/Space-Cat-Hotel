#pragma once

#include "CoreMinimal.h"
#include "Character/SpaceCatRTSSelectable.h"
#include "Facility.generated.h"

UENUM(BlueprintType)
enum class EFacilityNature : uint8
{
	FFN_MINE UMETA(DisplayName = "Mine"),
	FFN_HOTEL UMETA(DisplayName = "Hotel"),
	FFN_EARTH UMETA(DisplayName = "Earth")
};

/**
 *
 */
UCLASS()
class SPACECATRTS_API AFacility : public ASpaceCatRTSSelectable
{
	GENERATED_BODY()

public:
	AFacility();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Facility")
		EFacilityNature FNature;

	UFUNCTION(BlueprintPure, Category = "Facility")
		FORCEINLINE float GetDistToBeSeenInside() { return DistToBeSeenInside; };
	UFUNCTION(BlueprintPure, Category = "Facility")
		FORCEINLINE float GetSqDistToBeSeenInside() { return DistToBeSeenInside * DistToBeSeenInside; };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Facility")
		float DistToBeSeenInside = 500.f;
};
