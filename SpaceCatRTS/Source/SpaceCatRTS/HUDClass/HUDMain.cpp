#include "HUDMain.h"
#include "UMG/Public/UMG.h"

AHUDMain::AHUDMain()
{
	PrimaryActorTick.bCanEverTick = true; // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bTickEvenWhenPaused = true;
}


void AHUDMain::BeginPlay()
{
	Super::BeginPlay();

	//hud
	PlayerController = this->GetOwningPlayerController();
	if (PlayerController)
	{
		if (WidgetToShow != EHudWidget::FHW_NONE)
		{
			switch (WidgetToShow)
			{
			case EHudWidget::FHW_START:
				ShowStartingWidget();
				break;
			case EHudWidget::FHW_HUD:
				ShowHUDWidget();
				break;
			case EHudWidget::FHW_PAUSE:
				ShowPauseWidget();
				break;
			case EHudWidget::FHW_END:
				ShowEndingWidget();
				break;
			default:
				break;
			}
		}
	}
}



#pragma region Widgets
//==============================================================================================
void AHUDMain::ShowCursor(bool showCursor)
{
	if (PlayerController)
	{
		//UE_LOG(LogTemp, Warning, TEXT("before if - showCursor = %s"), showCursor ? TEXT("true") : TEXT("false"));
		PlayerController->bShowMouseCursor = showCursor;
		PlayerController->bEnableClickEvents = showCursor;
		PlayerController->bEnableMouseOverEvents = showCursor;
	}
}

UUserWidget* AHUDMain::GetCurrentWidget()
{
	return CurrentWidget;
}

TSubclassOf<UUserWidget> AHUDMain::GetCurrentWidgetClass()
{
	return CurrentWidgetClass;
}

UUserWidget* AHUDMain::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass, bool showCursor)
{
	if (CurrentWidget != nullptr)
	{
		OldWidgetClass = CurrentWidget->GetClass();
		CurrentWidget->RemoveFromViewport();
		CurrentWidget->RemoveFromParent();
		CurrentWidget->Destruct();
		CurrentWidget = nullptr;
	}

	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
			CurrentWidgetClass = NewWidgetClass;
		}

		ShowCursor(showCursor);
	}

	return CurrentWidget;
}

bool AHUDMain::IsShowingWidget(EHudWidget widgetToLookFor)
{
	switch (widgetToLookFor)
	{
	case EHudWidget::FHW_START:
		return CurrentWidgetClass == StartingWidgetClass;
		break;

	case EHudWidget::FHW_HUD:
		return CurrentWidgetClass == HUDWidget;
		break;

	case EHudWidget::FHW_PAUSE:
		return CurrentWidgetClass == PauseWidgetClass;
		break;

	case EHudWidget::FHW_END:
		return CurrentWidgetClass == EndingWidgetClass;
		break;

	default:
		return false;
		break;
	}
}

void AHUDMain::ShowWidget(TSubclassOf<UUserWidget> NewWidgetClass, bool showCursor)
{
	if (NewWidgetClass != nullptr)
	{
		//OldWidgetClass = NewWidgetClass;
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}

		ShowCursor(showCursor);
	}
}

void AHUDMain::ShowStartingWidget()
{
	ChangeMenuWidget(StartingWidgetClass, true);
}

void AHUDMain::ShowEndingWidget()
{
	ChangeMenuWidget(EndingWidgetClass, true);
}

void AHUDMain::ShowPauseWidget()
{
	ChangeMenuWidget(PauseWidgetClass, true);
}

void AHUDMain::ShowHUDWidget()
{
	ChangeMenuWidget(HUDWidget, false);
}


void AHUDMain::HideWidget(UUserWidget* widgetToHide, bool showCursor)
{
	if (widgetToHide != nullptr)
	{
		widgetToHide->RemoveFromViewport();
		widgetToHide->RemoveFromParent();
		widgetToHide->Destruct();
	}

	ShowCursor(showCursor);
}

void AHUDMain::HideCurrentWidget(bool showCursor)
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget->RemoveFromParent();
		CurrentWidget->Destruct();
		CurrentWidget = nullptr;
	}

	ShowCursor(showCursor);
}
//==============================================================================================
#pragma endregion

