#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SpaceCatRTSSelectable.generated.h"


UENUM(BlueprintType)
enum class ESelectableNature : uint8
{
	FSN_FACILITY UMETA(DisplayName = "Facility"),
	FSN_WORKER UMETA(DisplayName = "Worker")
};

UCLASS(Blueprintable)
class ASpaceCatRTSSelectable : public ACharacter
{
	GENERATED_BODY()

public:
	ASpaceCatRTSSelectable();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Selectable", meta = (AllowPrivateAccess = "true"))
		ESelectableNature SNature;

	UFUNCTION(BlueprintPure, Category = "Selectable")
		FORCEINLINE bool GetCostOxygenToSpawn() { return CostOxygenToSpawn; }
	UFUNCTION(BlueprintPure, Category = "Selectable")
		FORCEINLINE bool GetCostRawToSpawn() { return CostRawToSpawn; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Selectable")
		class ASpaceCatRTSPlayerController* PC;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Selectable")
		int32 CostOxygenToSpawn = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Selectable")
		int32 CostRawToSpawn = 0;
};

