#include "MyHUDWidget.h"
#include "Components/TextBlock.h"

void UMyHUDWidget::UpdateStats(float CurrentHealth, float MaxHealth, int32 Level, int32 CurrentAmmo, int32 MaxAmmo)
{
    if (HealthText)
    {
        FString HealthStr = FString::Printf(TEXT("HP: %.0f / %.0f"), CurrentHealth, MaxHealth);
        HealthText->SetText(FText::FromString(HealthStr));
    }
    if (LevelText)
    {
        FString LevelStr = FString::Printf(TEXT("Level: %d"), Level);
        LevelText->SetText(FText::FromString(LevelStr));
    }
    if (AmmoText)
    {
        FString AmmoStr = FString::Printf(TEXT("Ammo: %d / %d"), CurrentAmmo, MaxAmmo);
        AmmoText->SetText(FText::FromString(AmmoStr));
    }
}