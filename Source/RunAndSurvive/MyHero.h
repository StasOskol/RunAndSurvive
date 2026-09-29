// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyHero.generated.h"

UCLASS()
class RUNANDSURVIVE_API AMyHero : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyHero();

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	// Хождение, вращение камеры
	void MoveForward(float Value);
	void MoveRight(float Value);

	// Приседание
	void StartCrouch();
	void StopCrouch();

	// Спринт
	void StartSprint();
	void StopSprint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	float StandingCapsuleHalfHeight;  // Высота стоя
	float CrouchingCapsuleHalfHeight; // Высота в приседе
	float TargetCapsuleHalfHeight;	  // Куда стремимся при приседи

	// Флаг приседания
	bool bIsCrouching;
};
