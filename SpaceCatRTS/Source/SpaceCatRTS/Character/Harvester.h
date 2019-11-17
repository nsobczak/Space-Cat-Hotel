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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
