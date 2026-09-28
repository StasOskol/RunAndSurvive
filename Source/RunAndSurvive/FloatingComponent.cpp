#include "FloatingComponent.h"
#include "GameFramework/Actor.h"

UFloatingComponent::UFloatingComponent()
{
	// Включаем Tick для этого компонента
	PrimaryComponentTick.bCanEverTick = true;
	RunningTime = 0.0f;
}

void UFloatingComponent::BeginPlay()
{
	Super::BeginPlay();

	// Запоминаем начальную позицию (опционально)
	// Можно будет добавить позже
}

void UFloatingComponent::TickComponent(float DeltaTime, ELevelTick TickType,
									   FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Получаем объект, к которому прикреплен компонент
	AActor *Owner = GetOwner();
	if (!Owner)
		return;

	// Считаем время
	RunningTime += DeltaTime;

	// ВРАЩЕНИЕ
	FRotator CurrentRotation = Owner->GetActorRotation();
	CurrentRotation.Yaw += RotationSpeed * DeltaTime;
	Owner->SetActorRotation(CurrentRotation);

	// ПАРЕНИЕ (движение вверх-вниз)
	FVector CurrentLocation = Owner->GetActorLocation();

	// Синус создает плавное движение
	float DeltaZ = FMath::Sin(RunningTime * FloatSpeed) * FloatHeight;

	// Применяем новую высоту (относительно начальной)
	// Здесь мы просто двигаем относительно текущей позиции
	// Для более точного парения нужно запоминать начальную позицию в BeginPlay
	FVector NewLocation = CurrentLocation;
	NewLocation.Z = CurrentLocation.Z + DeltaZ * DeltaTime;

	Owner->SetActorLocation(NewLocation);
}