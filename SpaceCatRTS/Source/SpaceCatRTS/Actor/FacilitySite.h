#pragma once

#include "CoreMinimal.h"
#include "Actor/ActorWithMeshBase.h"
#include "Utils/GameEnums.h"
#include "Materials/MaterialInterface.h"
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
		FORCEINLINE bool IsMineFacility() { return ConstructibleFacilityNature == EFacilityNature::FFN_MINE; }
	UFUNCTION(BlueprintPure, Category = "FacilitySite")
		FORCEINLINE bool IsHotelFacility() { return ConstructibleFacilityNature == EFacilityNature::FFN_HOTEL; }

	UFUNCTION(BlueprintPure, Category = "FacilitySite")
		FORCEINLINE EMineNature GetConstructibleMineNature() { return ConstructibleMineNature; }

	UFUNCTION(BlueprintCallable, Category = "FacilitySite")
		void Highlight();

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FacilitySite")
		UMaterialInterface* Mat_base;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FacilitySite")
		UMaterialInterface* Mat_highlighted;
	/**In seconds*/
	UPROPERTY(EditDefaultsOnly, Category = "FacilitySite")
		float TimeStayingHigligtedAfterHovering = 0.05f;

	float HighlightTimer;
	bool bIsHighlighted;
};
