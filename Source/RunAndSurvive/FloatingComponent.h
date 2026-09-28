#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FloatingComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class RUNANDSURVIVE_API UFloatingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFloatingComponent();

	// Настройки, которые можно менять в редакторе
	UPROPERTY(EditAnywhere, Category = "Floating")
	float FloatSpeed = 2.0f; // Скорость парения

	UPROPERTY(EditAnywhere, Category = "Floating")
	float FloatHeight = 50.0f; // Высота парения

	UPROPERTY(EditAnywhere, Category = "Floating")
	float RotationSpeed = 30.0f; // Скорость вращения

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction *ThisTickFunction) override;

private:
	float RunningTime;
};