#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Utils/GameEnums.h"
#include "SpaceCatRTSSelectable.generated.h"

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

	/** Returns SelectionHighlight actor **/
	UFUNCTION(BlueprintPure, Category = "Selectable")
		FORCEINLINE class AActorWithMeshBase* GetSelectionHighlightActor() { return SelectionHighlight; }
	UFUNCTION(BlueprintCallable, Category = "SelectableHighlight")
		void Highlight();
	UFUNCTION(BlueprintCallable, Category = "SelectableHighlight")
		void RemoveHighlight();

	UFUNCTION(BlueprintPure, Category = "Selectable")
		FORCEINLINE bool GetCostOxygenToSpawn() { return CostOxygenToSpawn; }
	UFUNCTION(BlueprintPure, Category = "Selectable")
		FORCEINLINE bool GetCostRawToSpawn() { return CostRawToSpawn; }

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Selectable")
		int32 CostOxygenToSpawn;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Selectable")
		int32 CostRawToSpawn;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called when Destroy() is called
	virtual void Destroyed() override;

	UPROPERTY(EditAnywhere, Category = "Debug")
		bool DEBUG = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Selectable")
		class ASpaceCatRTSPlayerController* PC;

	/** A decal to highlight selected actor. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SelectableHighlight")
		TSubclassOf<class AActorWithMeshBase>  SelectionHighlightClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SelectableHighlight")
		class AActorWithMeshBase*  SelectionHighlight;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SelectableHighlight")
		FVector SelectionHighlightPostion = FVector(0.f, 0.f, -100.f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SelectableHighlight")
		UMaterialInterface* Mat_Highlighted;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SelectableHighlight")
		UMaterialInterface* Mat_NotHighlighted;
};

