#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SpaceCatRTSSelectable.generated.h"


UENUM(BlueprintType)
enum class ESelectableNature : uint8
{
	FSN_FACILITY UMETA(DisplayName = "Facility"),
	FSN_WORKER UMETA(DisplayName = "Worker")
};

UCLASS(Blueprintable)
class ASpaceCatRTSSelectable : public ACharacter
{
	GENERATED_BODY()

public:
	ASpaceCatRTSSelectable();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Selectable", meta = (AllowPrivateAccess = "true"))
		ESelectableNature SNature;

protected:
	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UDecalComponent* CursorToWorld;

};

