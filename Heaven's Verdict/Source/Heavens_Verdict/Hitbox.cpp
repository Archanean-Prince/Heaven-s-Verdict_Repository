// Fill out your copyright notice in the Description page of Project Settings.

#include "Hitbox.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "DrawDebugHelpers.h"
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
	mCollisionBox->InitBoxExtent(FVector(45, 45, 45));
	//and places it in a specific area
	mCollisionBox->SetRelativeLocation(FVector(0, 0, 0));

	RootComponent = mCollisionBox;
	//Gives it the fireball tag so it can be recognized as a fireball
	mCollisionBox->ComponentTags.Add(FName("Hitbox"));

	mCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AHitbox::OnOverlapBegin);
}
AHitbox::AHitbox(bool low_) {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Creates the root componenent
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));

	//Creates the hitbox component
	mCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Hitbox"));
	//Then attaches the collision box to the root component. Order of attachment is important!
	RootComponent->SetupAttachment(mCollisionBox);

	//Creates the collision box to be of a specific size
	mCollisionBox->InitBoxExtent(FVector(60, 45, 20));
	//and places it in a specific area
	mCollisionBox->SetRelativeLocation(FVector(0, 0, 0));

	RootComponent = mCollisionBox;
	//Gives it the fireball tag so it can be recognized as a fireball
	mCollisionBox->ComponentTags.Add(FName("Hitbox"));

	mCollisionBox->ComponentTags.Add(FName("LowHitbox"));

}
void AHitbox::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherComp->ComponentHasTag("Player") && isActive==true) {
		UE_LOG(LogTemp, Warning, TEXT("Collided with player"));
	}
}
// Called when the game starts or when spawned
void AHitbox::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Warning, TEXT("Hitbox made!"));
}

// Called every frame
void AHitbox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (isActive) {
		AdvanceTimer();
	}
	DrawDebugBox(GetWorld(), GetActorLocation(), FVector(60, 45, 20), FColor::Blue, false, 0.05f, 0, 2);
	
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
	isActive = false;
	hitboxDuration = 100;
	UE_LOG(LogTemp, Warning, TEXT("Deactivated"));
}

