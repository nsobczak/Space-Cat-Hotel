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

	virtual void DoNothing() override;

	UFUNCTION(BlueprintPure, Category = "Engineer")
		FORCEINLINE class AHotel* GetTargetHotel() { return TargetHotel; };

	UFUNCTION(BlueprintCallable, Category = "Engineer")
		bool AssignHotelToWork(class AHotel* newHotel);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Debug")
		class AHotel* TargetHotel;

	void WorkAtHotel();
};
