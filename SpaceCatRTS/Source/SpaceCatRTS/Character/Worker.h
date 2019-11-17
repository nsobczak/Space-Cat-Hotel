#pragma once

#include "CoreMinimal.h"
#include "Character/SpaceCatRTSSelectable.h"
#include "Worker.generated.h"

UENUM(BlueprintType)
enum class EWorkerNature : uint8
{
	FWN_HARVESTER UMETA(DisplayName = "Harvester"),
	FWN_ENGINEER UMETA(DisplayName = "Engineer")
};

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
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Worker", meta = (AllowPrivateAccess = "true"))
		EWorkerNature WNature;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
