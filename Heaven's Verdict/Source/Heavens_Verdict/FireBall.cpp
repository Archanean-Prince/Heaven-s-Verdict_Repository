// Fill out your copyright notice in the Description page of Project Settings.

#include "FireBall.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "DrawDebugHelpers.h"
#include "UObject/ConstructorHelpers.h"
// Sets default values
AFireBall::AFireBall()
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
	mCollisionBox->InitBoxExtent(FVector(40,40, 40));
	//and places it in a specific area
	mCollisionBox->SetRelativeLocation(FVector(0, 0, 0));
	//This creates the static mesh component
	myMesh = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));

	myMesh->SetupAttachment(RootComponent);
	//Fetches the default cube object from my files
	myMesh->SetStaticMesh((ConstructorHelpers::FObjectFinderOptional<UStaticMesh>
		(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"))).Get());


	//Sets it's relative location to zero so it ligns up with everything else
	myMesh->SetRelativeLocation(FVector().ZeroVector);
	//Moves it slightly downards to better fit it
	myMesh->SetRelativeScale3D(FVector(0.5, 0.5, 0.5));
	myMesh->SetRelativeLocation(FVector(0, 0, -30));

	
	RootComponent = mCollisionBox;
	//Gives it the fireball tag so it can be recognized as a fireball
	mCollisionBox->ComponentTags.Add(FName("fireball"));

}

// Called when the game starts or when spawned
void AFireBall::BeginPlay()
{
	Super::BeginPlay();
	
		
}

void AFireBall::AdvanceTimer()
{
	--fireballLifeSpan;
	if (fireballLifeSpan < 0) {
		//GetWorldTimerManager().ClearTimer(countdownTimerHandle);
		CountDownHasFinished();
	}
}

void AFireBall::CountDownHasFinished()
{
	Destroy();
	UE_LOG(LogTemp, Warning, TEXT("Fireball is dead!"));
	fireballDead = true;
}

bool AFireBall::GetFireballStatus()
{

	return fireballDead;
}

void AFireBall::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherComp->ComponentHasTag("Player")) {
		Destroy();
	}
}

// Called every frame
void AFireBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugBox(GetWorld(), GetActorLocation(), FVector(45, 45, 45), FColor::Purple, false, 0.05f, 0, 2);
	AdvanceTimer();

	// The important part that lets the fireball move forward. Is called on startup.
	if (!currentVelocity.IsZero())
	{
		FVector NewLocation = GetActorLocation() + (currentVelocity * DeltaTime);
		SetActorLocation(NewLocation);
	}
}

