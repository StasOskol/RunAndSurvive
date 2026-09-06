// Fill out your copyright notice in the Description page of Project Settings.

#include "MyHero.h"

// Sets default values
AMyHero::AMyHero()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyHero::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyHero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMyHero::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMyHero::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyHero::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AMyHero::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AMyHero::AddControllerPitchInput);
}

void AMyHero::MoveForward(float Value)
{
	if (Controller && Value != 0.0f)
	{
		FRotator YawRotation(0, Controller->GetControlRotation().Yaw, 0);
		FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AMyHero::MoveRight(float Value)
{
	if (Controller && Value != 0.0f)
	{
		FRotator YawRotation(0, Controller->GetControlRotation().Yaw, 0);
		FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}