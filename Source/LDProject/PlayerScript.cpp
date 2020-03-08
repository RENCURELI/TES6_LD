// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerScript.h"

// Sets default values
APlayerScript::APlayerScript()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	CameraComponent->SetupAttachment(GetCapsuleComponent());
	CameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f);
	CameraComponent->bUsePawnControlRotation = true;

	g_jumpHeight = 500.f;
	g_walkSpeed = 500;
	g_sprintSpeed = 1000;
}

// Called when the game starts or when spawned
void APlayerScript::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void APlayerScript::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerScript::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent)

	//Movement
	PlayerInputComponent->BindAxis("Forward", this, &APlayerScript::MoveForward);
	PlayerInputComponent->BindAxis("Right", this, &APlayerScript::MoveRight);

	//Camera controls
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);

	//Actions
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APlayerScript::Interact);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerScript::Jump);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &APlayerScript::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &APlayerScript::Walk);
}

void APlayerScript::Landed(const FHitResult &hit)
{
	g_jumpCount = 0;
}

void APlayerScript::MoveForward(float val)
{
	if (val != 0)
	{
		AddMovementInput(GetActorForwardVector(), val);
	}
}

void APlayerScript::MoveRight(float val)
{
	if (val != 0)
	{
		AddMovementInput(GetActorRightVector(), val);
	}
}

void APlayerScript::Interact()
{
	//Add logic
	UE_LOG(LogTemp, Warning, TEXT("Interact"));
}

void APlayerScript::Jump()
{
	if (g_jumpCount < 1)
	{
		APlayerScript::LaunchCharacter(FVector(0, 0, g_jumpHeight), false, true);
		g_jumpCount++;
	}
	
}

void APlayerScript::Sprint()
{
	GetCharacterMovement()->MaxWalkSpeed = g_sprintSpeed;	
}

void APlayerScript::Walk()
{
	GetCharacterMovement()->MaxWalkSpeed = g_walkSpeed;
}