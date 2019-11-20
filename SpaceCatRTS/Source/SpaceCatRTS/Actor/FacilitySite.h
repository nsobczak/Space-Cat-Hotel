#pragma once

#include "CoreMinimal.h"
#include "Actor/ActorWithMeshBase.h"
#include "Utils/GameEnums.h"
#include "FacilitySite.generated.h"

UCLASS()
class SPACECATRTS_API AFacilitySite : public AActorWithMeshBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFacilitySite();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintPure, Category = "FacilitySite")
		FORCEINLINE bool IsFree() { return bIsFree; }

	UFUNCTION(BlueprintCallable, Category = "FacilitySite")
		void SetOccupied() { this->bIsFree = false; }
	UFUNCTION(BlueprintCallable, Category = "FacilitySite")
		void FreeSite() { this->bIsFree = true; }

	UFUNCTION(BlueprintPure, Category = "FacilitySite")
		FORCEINLINE EFacilityNature GetConstructibleFacilityNature() { return ConstructibleFacilityNature; }
	
	UFUNCTION(BlueprintPure, Category = "FacilitySite")
		FORCEINLINE EMineNature GetConstructibleMineNature() { return ConstructibleMineNature; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "FacilitySite")
		bool bIsFree = true;

	UPROPERTY(EditDefaultsOnly, Category = "FacilitySite")
		EFacilityNature ConstructibleFacilityNature;

	//TODO: EditConditioncan be used like that only after ue4.23
	UPROPERTY(EditAnywhere, Category = "FacilitySite", meta = (EditCondition = "ConstructibleFacilityNature == EFacilityNature::FFN_MINE"))
		EMineNature ConstructibleMineNature;
};
