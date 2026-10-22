#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyHUDWidget.generated.h"

UCLASS()
class RUNANDSURVIVE_API UMyHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void UpdateStats(float CurrentHealth, float MaxHealth, int32 Level, int32 CurrentAmmo, int32 MaxAmmo);

protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock *HealthText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock *LevelText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock *AmmoText;
};