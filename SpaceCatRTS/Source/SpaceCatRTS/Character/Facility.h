#pragma once

#include "CoreMinimal.h"
#include "Character/SpaceCatRTSSelectable.h"
#include "Facility.generated.h"

UENUM(BlueprintType)
enum class EFacilityNature : uint8
{
	FFN_MINE UMETA(DisplayName = "Mine"),
	FFN_HOTEL UMETA(DisplayName = "Hotel")
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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Worker, meta = (AllowPrivateAccess = "true"))
		EFacilityNature FNature;
};
