#pragma once

#include "CoreMinimal.h"
#include "Character/Worker.h"
#include "Harvester.generated.h"

/**
 *
 */
UCLASS()
class SPACECATRTS_API AHarvester : public AWorker
{
	GENERATED_BODY()

public:
	AHarvester();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	virtual void DoNothing() override;

	UFUNCTION(BlueprintPure, Category = "Harvester")
		FORCEINLINE class AMine* GetTargetMine() { return TargetMine; };

	UFUNCTION(BlueprintCallable, Category = "Harvester")
		bool AssignMineToHarvest(class AMine* newMine);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Debug")
		class AEarth* Earth;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Debug")
		class AMine* TargetMine;

	void WorkAtMine();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Harvester")
		float HarvestTimer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Harvester")
		int32 ResourceAmount = 0;
};
