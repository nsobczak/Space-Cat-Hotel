#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SpaceCatRTSPlayerController.generated.h"

UCLASS()
class ASpaceCatRTSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASpaceCatRTSPlayerController();

	int32 bMoveCameraXAxis = 0, bMoveCameraYAxis = 0;

	UFUNCTION(BlueprintPure, Category = "Selection")
		FORCEINLINE ASpaceCatRTSSelectable* GetSelectedActor() { return SelectedActor; };
	UFUNCTION(BlueprintCallable, Category = "Selection")
		void RemoveSelectedActor() { SelectedActor = nullptr; };

	UFUNCTION(BlueprintPure, Category = "Resources")
		FORCEINLINE int32 GetOxygenVal() { return Oxygen; };
	UFUNCTION(exec, BlueprintCallable, Category = "Resources")
		void SetOxygenVal(int32 val) { Oxygen = val; };
	UFUNCTION(BlueprintCallable, Category = "Resources")
		void AddOxygenVal(int32 val) { Oxygen += val; };

	UFUNCTION(BlueprintPure, Category = "Resources")
		FORCEINLINE int32 GetRawMatVal() { return RawMat; };
	UFUNCTION(exec, BlueprintCallable, Category = "Resources")
		void SetRawMatVal(int32 val) { RawMat = val; };
	UFUNCTION(BlueprintCallable, Category = "Resources")
		void AddRawMatVal(int32 val) { RawMat += val; };

	void SetMouseCursorWidget(TSubclassOf<UUserWidget> NewWidgetClass);
	UFUNCTION(BlueprintCallable, Category = "MouseInterface")
		void UpdateMouseCursorViewportOrder() { SetMouseCursorWidget(MouseCursorWidgetClass); };


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Debug")
		bool DEBUG = false;

	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	UPROPERTY(VisibleAnywhere, Category = "Debug")
		ASpaceCatRTSSelectable* SelectedActor;

	/**widget to use for our HUD screen*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "MouseInterface")
		TSubclassOf<UUserWidget> MouseCursorWidgetClass;

	/** Update camera location when cursor moves to viewport sides. */
	void HandleCamera(float LocationX, float LocationY);

	/** Check if mouse over facility site and change its material if it needed to be highlighted. */
	void HandleFacilityHighlight();

	/** Navigate player to the current mouse cursor location. */
	void MoveToMouseCursor();

	/** Navigate player to the current touch location. */
	void MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

	/** Input handlers for PawnSelection action. */
	void OnSelectPawnPressed();
	void OnSelectPawnReleased();


	UPROPERTY(VisibleAnywhere, Category = "Resources")
		int32 Oxygen;
	UPROPERTY(VisibleAnywhere, Category = "Resources")
		int32 RawMat;

private:
	/** The widget instance that we are using as our mouse cursor. */
	UUserWidget* MouseCursorWidget;
};


