#include "FacilitySite.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
AFacilitySite::AFacilitySite()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFacilitySite::BeginPlay()
{
	Super::BeginPlay();

	HighlightTimer = 0;
	if (BaseMesh) BaseMesh->SetMaterial(0, Mat_base);
	bIsHighlighted = false;
}

// Called every frame
void AFacilitySite::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HighlightTimer > 0)
	{
		HighlightTimer -= DeltaTime;
	}

	if (HighlightTimer <= 0 && bIsHighlighted && BaseMesh)
	{
		BaseMesh->SetMaterial(0, Mat_base);
		bIsHighlighted = false;
	}
}

void AFacilitySite::Highlight()
{
	if (BaseMesh)
	{
		HighlightTimer = TimeStayingHigligtedAfterHovering;
		BaseMesh->SetMaterial(0, Mat_highlighted);
		bIsHighlighted = true;
	}
}