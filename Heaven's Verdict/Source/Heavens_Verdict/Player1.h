// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Runtime/Engine/Classes/Components/TimelineComponent.h"
#include "Player1.generated.h"

UCLASS()
class HEAVENS_VERDICT_API APlayer1 : public APawn
{
	GENERATED_BODY()

///Where all the public variables are compiled. Some should be private/protected however...
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

	//What advances the timer
	void AdvanceTimer();

	//What happens next when the countdown has finished
	void CountdownHasFinished();

	//Determines how long the hitbox remains active
	int hitboxLifeSpan = 100;

	//Advances the hitboxes timer
	void AdvanceHitboxTimer();

	//Returns true when the hitbox has done existin
	void hitboxFinished();

///Where the components are initialized, protected because of course they are.
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

	//What will allow us to chose what we want to spawn.
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AFireBall> toSpawn;

	UPROPERTY(EditAnywhere)
		class UBoxComponent* activeHitbox;
	/*
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AHitbox> hitboxInstance;
	*/
	UPROPERTY(EditAnywhere)
		class AHitbox* hitboxInstance;

	//Determines whether or not the hitbox has been made or not.
	UPROPERTY(EditAnywhere)
	bool isHitboxActive;

///Public methods that everyone should have access to or know of
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

	//Method for the attack hitbox
	UFUNCTION()
		void AttackButton();

	//Boolean to check if the player wants to airdash left
	bool airDashLeft;

///Below here is what determines UI functionality
protected:
	//Does not blow up! (yet)
	//Our full health value, can be changed to whatever we want
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float fullHealth;

	//Current health the player has
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float Health;

	//The current % of health that the player has
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float healthPercentage;

	//Whatever the full Meter value is, same as health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meter")
		float fullMeter;

	//current % of meter that the player has
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meter")
		float MeterPercentage;

	//Holds what the previous value for the meter is
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meter")
		float prevMeterValue;

	//What the current value of the meter is
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meter")
		float MeterValue;

	//Pretty sure this is useless to me but it could help determine Invicibility frames
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		bool redFlash;

	//Also does not blow up!

	//Allows for a "smooth" transition between two values,
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meter")
		UCurveFloat *MeterCurve;

	//The timeline value that will help make everything go
	UPROPERTY(EditAnywhere, Category = "Meter")
		FTimeline myTimeline;

	//The timer for... things. I forgot
	UPROPERTY(EditAnywhere, Category = "Meter")
		FTimerHandle memberTimerHandler;

	//WHat the current float value is b
	float curveFloatVlaue;

	//Whatever the timeline value us
	float timelineValue;

	//Is the player able to use their meter?
	bool canUseMeter;

	//Get's the players current health
	UFUNCTION(BlueprintPure, Category = "Health")
		float GetHealth();

	//Doesn't blow up! Cool!
	//Get's the health as an integer to then be dispalyed
	UFUNCTION(BlueprintPure, Category = "Health")
		FText GetHealthIntText();

	//Gets the meter value
	UFUNCTION(BlueprintPure, Category = "Meter")
		float GetMeter();

	//Doesn't blow up! Cool!

	//Then displays it as an integer and then on the UI
	UFUNCTION(BlueprintPure, Category = "Meter")
		FText GetMeterIntText();

	//Determines how much damage the player is taking.
	UFUNCTION()
		void SetDamageState();

	//Sets the meters current value
	UFUNCTION()
		void SetMeterValue();

	//Sets the current meters state,(if usesable or not)
	UFUNCTION()
		void SetMeterState();

	//Sets the change to take place,
	UFUNCTION()
		void SetMeterChange(float MeterValue_);

	//Updates the meter value to whatever it needs to be
	UFUNCTION()
		void UpdateMeter();

	//Plays a red flash upon taking damage, useless to me I think however.
	UFUNCTION(BlueprintPure, Category = "Health")
		bool PlayFlash();

	/*
	UFUNCTION()
		void ReceivePointDamage(float Damage, const UDamageType* damageType, FVector HitLocation, FVector hitNormal,
			UPrimitiveComponent* hitComponent, FName boneName, FVector shotFromDirection,
			AController *instigatedBy, AActor *damageCauser, const FHitResult &hitInfo);
			Commented out for some reason?
			*/

	//Updates the health
	UFUNCTION(BlueprintCallable, Category = "Health")
		void UpdateHealth(float HealthChange_);

};
