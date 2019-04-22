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


	//The players health value
	float health = 100;

	//How much meter/special bar they have
	float meter;


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
	bool isFacingLeft = false;

	//If the player is actually air dashing
	UPROPERTY(VisibleAnywhere)
	bool isAirdashing;

	//The players start location when they begin their air dash
	FVector airDashStart;

	//The players current velocity either along X or Y.
	FVector currentVelocity;

	//What checks to see if the player has already shot their fireball.
	bool fireBallFired = true;
	//Checks to see if the player hasn't already expended their singular air dash
	UPROPERTY(VisibleAnywhere)
		bool canAirdash = false;

	//Checks to see if the fireball is dead.
	bool fireballDead;

	//Meant to mimic how the fireball timer works
	int fireballLifeSpan = 100;

	FTimerHandle countdownTimerHandle;

	void AdvanceTimer();
	
	void CountdownHasFinished();

	int hitboxLifeSpan = 100;

	void AdvanceHitboxTimer();

	void hitboxFinished();

	bool proximityBlocking = false;
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
	//Records the player location
	UPROPERTY(EditAnywhere)
		FVector playerLocation;
	//The fireball spawn point
	UPROPERTY(EditAnywhere)
		FVector fireballSpawn;
	//Where the hitbox will spawn
	UPROPERTY(EditAnywhere)
		FVector hitboxLocation;

	UPROPERTY(EditAnywhere)
		class UBoxComponent* blockBox;

	//What will allow us to chose what we want to spawn.
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AFireBall> toSpawn;

	UPROPERTY(EditAnywhere)
		class UBoxComponent* activeHitbox;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AHitbox> hitbox;
	UPROPERTY(EditAnywhere)


	bool isHitboxActive;
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

	void AirDashB();
	//The method that handles the base functionality of the special button. Would be different for each player and made virtual in the future.
	void specialButton();

	//This method will be called in the blueprint
	UFUNCTION(BlueprintCallable)
		void TakeDamage(bool isBlocked_);
	//Method for the attack hitbox
	UFUNCTION()
		void AttackButton();


	//Boolean to check if the player wants to airdash left
	bool airDashLeft;

};
