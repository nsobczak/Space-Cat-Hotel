#pragma once

#include "CoreMinimal.h"
#include "GameMode/SpaceCatRTSGameMode.h"
#include "GMLevel.generated.h"

/**
 *
 */
UCLASS()
class SPACECATRTS_API AGMLevel : public ASpaceCatRTSGameMode
{
	GENERATED_BODY()

public:
	AGMLevel();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "GameLogic", Meta = (BlueprintProtected = "true"))
		virtual void SetupGame();

	UFUNCTION(BlueprintPure, Category = "GameTimer")
		FORCEINLINE float GetCurrentGameTimer();
	UFUNCTION(BlueprintPure, Category = "GameTimer")
		FORCEINLINE int32 GetCurrentGameTimerMinutes();
	UFUNCTION(BlueprintPure, Category = "GameTimer")
		FORCEINLINE int32 GetCurrentGameTimerSeconds();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Timer")
		float GameTimer;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Resources")
		int32 Oxygen;

	virtual void GameOver();
};
