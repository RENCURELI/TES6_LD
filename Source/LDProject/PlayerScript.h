// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"
#include "PlayerScript.generated.h"

class UInputComponent;

UCLASS()
class LDPROJECT_API APlayerScript : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerScript();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* CameraComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float val);
	void MoveRight(float val);

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void Interact();

	void Jump();

	UFUNCTION()
		void Sprint();

	UFUNCTION()
		void Walk();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float g_jumpHeight;

	UPROPERTY(EditAnywhere)
		int g_walkSpeed;

	UPROPERTY(EditAnywhere)
		int g_sprintSpeed;

};
