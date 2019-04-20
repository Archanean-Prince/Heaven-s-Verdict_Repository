// Fill out your copyright notice in the Description page of Project Settings.

#include "FireballShooter.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"
#include "DrawDebugHelpers.h"
#include "Fireball.h"
// Sets default values
AFireballShooter::AFireballShooter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	
	//Creates the hitbox component
	mCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Hitbox"));
	//Then attaches the collision box to the root component. Order of attachment is important!
	RootComponent->SetupAttachment(mCollisionSphere);
	
	mCollisionSphere->InitSphereRadius(50);

	mCollisionSphere->SetRelativeLocation(FVector(0, 0, 0));
	
	//This creates the static mesh component

	myMesh = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	
	myMesh->SetupAttachment(RootComponent);

	myMesh->SetStaticMesh((ConstructorHelpers::FObjectFinderOptional<UStaticMesh>
		(TEXT("/Game/StarterContent/Shapes/Shape_Tube.Shape_Tube"))).Get());

	
	//Sets it's relative location to zero so it ligns up with everything else
	myMesh->SetRelativeLocation(FVector().ZeroVector);
	myMesh->SetRelativeLocation(FVector(0, 0, -50));

	mCollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AFireballShooter::OnOverlapBegin);

	RootComponent = mCollisionSphere;

	mCollisionSphere->ComponentTags.Add(FName("Target"));
}



// Called when the game starts or when spawned
void AFireballShooter::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(countdownTimerHandle, this, &AFireballShooter::shootFireball, 5.0f, true, 2.0f);
	
	targetLocation = GetActorLocation();

	fireballSpawnPoint.Y = targetLocation.Y - 150;
	fireballSpawnPoint.X = targetLocation.X - 30;
	fireballSpawnPoint.Z = targetLocation.Z;



}

// Called every frame
void AFireballShooter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//DrawDebugBox(GetWorld(), fireballSpawnPoint, FVector(40, 40, 40), FColor::Purple, false, 0.3f, 0, 2);
}

void AFireballShooter::shootFireball()
{
	//Simple spawning that is found in multiple areas
	AFireBall* newFireball = GetWorld()->SpawnActor <AFireBall>(toSpawn, fireballSpawnPoint, FRotator::ZeroRotator);
	//Gives the fireball the necessary velocity
	newFireball->currentVelocity.Y = FMath::Clamp(defaultValue, -1.0f, 1.0f) * -500.0f;

	//UE_LOG(LogTemp, Warning, TEXT("Fireball fired"));
}

void AFireballShooter::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherComp->ComponentHasTag("fireball")) {
		//UE_LOG(LogTemp, Warning, TEXT("Collided with fireball"));
		Destroy();
		OtherComp->DestroyComponent();
	}
	if (OtherComp->ComponentHasTag("Hitbox")) {
		//UE_LOG(LogTemp, Warning, TEXT("Got punched!"));
		Destroy();
	}
	
}

bool AFireballShooter::GetFireballStatus()
{
	return false;
}