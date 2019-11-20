#pragma once

#include "CoreMinimal.h"
#include "Character/Facility.h"
#include "Earth.generated.h"

/**
 *
 */
UCLASS()
class SPACECATRTS_API AEarth : public AFacility
{
	GENERATED_BODY()

public:
	AEarth();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "Action")
		class AHarvester* SpawnHarvester();
	UFUNCTION(BlueprintCallable, Category = "Action")
		class AEngineer* SpawnEngineer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Action")
		TSubclassOf<class AHarvester> BPHarvesterToSpawn;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Action")
		TSubclassOf <class AEngineer> BPEngineerToSpawn;

};
