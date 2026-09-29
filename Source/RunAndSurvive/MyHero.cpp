// Fill out your copyright notice in the Description page of Project Settings.

#include "MyHero.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

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

	// Запоминаем стандартную высоту капсулы (стоя)
	StandingCapsuleHalfHeight = GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();

	// Высота в приседе — половина от высоты стоя
	CrouchingCapsuleHalfHeight = StandingCapsuleHalfHeight * 0.5f;

	// Изначально мы стоим
	TargetCapsuleHalfHeight = StandingCapsuleHalfHeight;

	bIsCrouching = false;
}

// Called every frame
void AMyHero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Текущая высота капсулы
	float CurrentHalfHeight = GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();

	// Плавно интерполируем к целевой высоте
	// Последний параметр — скорость приседания (чем больше, тем быстрее)
	float NewHalfHeight = FMath::FInterpTo(CurrentHalfHeight, TargetCapsuleHalfHeight, DeltaTime, 8.0f);

	// Применяем новую высоту
	GetCapsuleComponent()->SetCapsuleHalfHeight(NewHalfHeight);
}

// Called to bind functionality to input
void AMyHero::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMyHero::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyHero::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AMyHero::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AMyHero::AddControllerPitchInput);

	// Для прыжка
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyHero::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMyHero::StopJumping);

	// Приседание
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AMyHero::StartCrouch);
	PlayerInputComponent->BindAction("UnCrouch", IE_Released, this, &AMyHero::StopCrouch);

	// Спринт
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMyHero::StartSprint);
	PlayerInputComponent->BindAction("StopSprint", IE_Released, this, &AMyHero::StopSprint);
}

// Движение камеры и персонажа
void AMyHero::MoveForward(float Value)
{
	if (Controller && Value != 0.0f)
	{
		FRotator YawRotation(0, Controller->GetControlRotation().Yaw, 0);
		FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

// Движение камеры и персонажа
void AMyHero::MoveRight(float Value)
{
	if (Controller && Value != 0.0f)
	{
		FRotator YawRotation(0, Controller->GetControlRotation().Yaw, 0);
		FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

// Приседание
void AMyHero::StartCrouch()
{
	// Задаём цель — высота в приседе
	TargetCapsuleHalfHeight = CrouchingCapsuleHalfHeight;

	// Меняем скорость передвижения
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;

	// Сообщаем движку, что мы в приседе (для проверки препятствий над головой)
	GetCharacterMovement()->bWantsToCrouch = true;

	// Запоминаем, что мы в присяди
	bIsCrouching = true;
}

// Приседание
void AMyHero::StopCrouch()
{
	// Задаём цель — высота стоя
	TargetCapsuleHalfHeight = StandingCapsuleHalfHeight;

	// Возвращаем скорость
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;

	// Сообщаем движку, что мы встаём
	GetCharacterMovement()->bWantsToCrouch = false;

	// Запоминаем, что мы встаём
	bIsCrouching = false;
}

void AMyHero::StartSprint()
{
	// Проверка при приседание
	if (bIsCrouching)
	{
		return;
	}

	GetCharacterMovement()->MaxWalkSpeed = 900.0f;
}

void AMyHero::StopSprint()
{
	// Проверка на приседание
	if (bIsCrouching)
	{
		GetCharacterMovement()->MaxWalkSpeed = 300.0f;
		return;
	}

	// Возвращаем обычную скорость
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}