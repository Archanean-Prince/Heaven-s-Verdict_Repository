// Fill out your copyright notice in the Description page of Project Settings.

#include "Hitbox.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"
// Sets default values
AHitbox::AHitbox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Creates the root componenent
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));

	//Creates the hitbox component
	mCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Hitbox"));
	//Then attaches the collision box to the root component. Order of attachment is important!
	RootComponent->SetupAttachment(mCollisionBox);

	//Creates the collision box to be of a specific size
	mCollisionBox->InitBoxExtent(FVector(20, 20, 20));
	//and places it in a specific area
	mCollisionBox->SetRelativeLocation(FVector(0, 0, 0));

	RootComponent = mCollisionBox;
	//Gives it the fireball tag so it can be recognized as a fireball
	mCollisionBox->ComponentTags.Add(FName("Hitbox"));

}

// Called when the game starts or when spawned
void AHitbox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHitbox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AdvanceTimer();
}

void AHitbox::AdvanceTimer()
{
	--hitboxDuration;
	if (hitboxDuration < 0) {
		CountdownHasFinished();
	}
}

void AHitbox::CountdownHasFinished()
{
	Destroy();
}
