// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Player1.generated.h"

UCLASS()
class HEAVENS_VERDICT_API APlayer1 : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayer1();

	//The speed of which the player travels on the X axis
	float speedX;


	//How long the player has been in the air for.
	float jumpTimer;

	//The maximum amount of time the player can be in the air for
	float jumpMaximum=30;

	//Some filler variable to save me some time.
	float defaultValue = 1;

	//If the player is grounded or not
	UPROPERTY(VisibleAnywhere)
	bool isGrounded;

	//If the player is facing the left or right
	bool isFacingLeft;

	//If the player is actually air dashing
	UPROPERTY(VisibleAnywhere)
	bool isAirdashing;

	//The players start location when they begin their air dash
	FVector airDashStart;

	//The players current velocity either along X or Y.
	FVector currentVelocity;

	//What checks to see if the player has already shot their fireball.
	bool fireBallFired = false;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//The Static Mesh Component, the actual cube itself and not the collision.
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* myMesh;

	//The box collision component, this is the actual hitbox.
	UPROPERTY(EditAnywhere)
		class UBoxComponent* mCollisionBox;
	//The Camera that we're using
	UPROPERTY(EditAnywhere)
		class UCameraComponent* theCamera;

	UPROPERTY(EditAnywhere)
		class UBoxComponent* projectileSpawnPoint;

	TSubclassOf<class AFireBall> fireballClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//The method that is called when collision happens.
	UFUNCTION()
		virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& SweepResult);

	//Method that moves the player along the X axis.
	void moveX(float axisValue);

	//The method that lets players jump. 
	void Jump();

	//The method that sets the "is airdashing variable" to true. 
	void AirDash();

	//The method that handles the base functionality of the special button. Would be different for each player and made virtual in the future.
	void specialButton();
};
