#pragma once

#include "CoreMinimal.h"
#include "GameFramework/WorldSettings.h"
#include "Utils/Struct/StructLevelInfo.h"
#include "Utils/Struct/StructGoal.h"
#include "LevelSettings.generated.h"

/**
 *
 */
UCLASS()
class SPACECATRTS_API ALevelSettings : public AWorldSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LevelSettings")
		FStructLevelInfo LevelInfo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LevelSettings")
		TArray<FStructGoal> Goals;
};
