#pragma once

#include "CoreMinimal.h"
#include "Character/SpaceCatRTSSelectable.h"
#include "Utils/GameEnums.h"
#include "Worker.generated.h"

/**
 *
 */
UCLASS()
class SPACECATRTS_API AWorker : public ASpaceCatRTSSelectable
{
	GENERATED_BODY()

public:
	AWorker();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Worker")
		EWorkerNature WNature;

	UFUNCTION(BlueprintCallable, Category = "Worker")
		virtual void DoNothing();

	UFUNCTION(BlueprintPure, Category = "Worker")
		FORCEINLINE bool GetIsBuilding() { return bIsBuilding; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool bIsBuilding = false;

};
