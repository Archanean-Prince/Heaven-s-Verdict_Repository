// Fill out your copyright notice in the Description page of Project Settings.

#include "FireBall.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
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
	mCollisionBox->InitBoxExtent(FVector(5,5, 5));
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

	//Gives it the fireball tag so it can be recognized as a fireball
	mCollisionBox->ComponentTags.Add(FName("Floor"));

}

// Called when the game starts or when spawned
void AFireBall::BeginPlay()
{
	Super::BeginPlay();
	
	currentVelocity.Y = FMath::Clamp(defaultValue, -1.0f, 1.0f) * 500.0f;
		
}

// Called every frame
void AFireBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	// The important part that lets the fireball move forward. Is called on startup.
	if (!currentVelocity.IsZero())
	{
		FVector NewLocation = GetActorLocation() + (currentVelocity * DeltaTime);
		SetActorLocation(NewLocation);
	}
}

