#pragma once

#include "CoreMinimal.h"
#include "GameEnums.generated.h"

#pragma region Selectable Natures

UENUM(BlueprintType)
enum class ESelectableNature : uint8
{
	FSN_FACILITY UMETA(DisplayName = "Facility"),
	FSN_WORKER UMETA(DisplayName = "Worker")
};

UENUM(BlueprintType)
enum class EWorkerNature : uint8
{
	FWN_HARVESTER UMETA(DisplayName = "Harvester"),
	FWN_ENGINEER UMETA(DisplayName = "Engineer")
};

UENUM(BlueprintType)
enum class EFacilityNature : uint8
{
	FFN_MINE UMETA(DisplayName = "Mine"),
	FFN_HOTEL UMETA(DisplayName = "Hotel"),
	FFN_EARTH UMETA(DisplayName = "Earth")
};

UENUM(BlueprintType)
enum class EMineNature : uint8
{
	FMN_OXYGEN UMETA(DisplayName = "Oxygen"),
	FMN_RAW UMETA(DisplayName = "Raw materials")
};

UENUM(BlueprintType)
enum class EHotelNature : uint8
{
	FHN_PURPLE_CONE UMETA(DisplayName = "Purple cone"),
	FHN_YELLOW_CUBE UMETA(DisplayName = "Yellow cube"),
	FHN_RED_CYLINDER UMETA(DisplayName = "Red cylinder")
};


#pragma endregion

#pragma region Game

UENUM(BlueprintType)
enum class EAnimalBreed : uint8
{
	FAB_BEAR UMETA(DisplayName = "Flying bear"),
	FAB_COW UMETA(DisplayName = "Nuclear cow"),
	FAB_WORM UMETA(DisplayName = "Giant worm"),
	FAB_FISH UMETA(DisplayName = "Solar fish"),
	FAB_PARROT UMETA(DisplayName = "Vampire parrot")
};

#pragma endregion

/**
 *
 */
class SPACECATRTS_API GameEnums
{
public:
	GameEnums();
	~GameEnums();
};
