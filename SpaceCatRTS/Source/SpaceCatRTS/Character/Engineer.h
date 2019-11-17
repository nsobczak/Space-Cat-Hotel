#pragma once

#include "CoreMinimal.h"
#include "Character/Worker.h"
#include "Engineer.generated.h"

/**
 * 
 */
UCLASS()
class SPACECATRTS_API AEngineer : public AWorker
{
	GENERATED_BODY()
	
public:
	AEngineer();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
