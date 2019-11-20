#pragma once

#include "CoreMinimal.h"
#include "Character/SpaceCatRTSSelectable.h"
#include "Utils/GameEnums.h"
#include "Facility.generated.h"


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
