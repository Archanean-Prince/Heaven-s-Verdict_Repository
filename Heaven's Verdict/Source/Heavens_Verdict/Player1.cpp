// Fill out your copyright notice in the Description page of Project Settings.

#include "Player1.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/BoxComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "FireBall.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"
// Sets default values
APlayer1::APlayer1()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Makes it so that it receives input from the lowest port player
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	
	//Creates the root component where everything will be added to
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));


	//Where the hitbox is created, initialized in it's size and then attached to the root component as well.
	mCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Hitbox"));
	RootComponent->SetupAttachment(mCollisionBox);
	mCollisionBox->InitBoxExtent(FVector(40, 40, 40));
	

	//Where the mesh is initialized, and then attached to the root component
	myMesh = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	myMesh->SetupAttachment(RootComponent);
	//This line also makes it auto spawn with the basic cube found within the starter assets.
	myMesh->SetStaticMesh((ConstructorHelpers::FObjectFinderOptional<UStaticMesh>
		(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"))).Get());
	//The line below makes sure it's in the center of the root component.
	myMesh->SetRelativeLocation(FVector().ZeroVector);
	myMesh->SetRelativeLocation(FVector(0, 0, -40));
	//X,Y,Z. X is Horizontal, Y is forward and Z is up and down.
	mCollisionBox->ComponentHasTag(FName("Player"));

	//The method below is called when the hitbox collide with another object who also has a box collider.
	mCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &APlayer1::OnOverlapBegin);

	//Sets up the camera to be a specific distance away. Yet to function properly like a normal fighter
	theCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	theCamera->SetupAttachment(RootComponent);
	theCamera->SetRelativeLocation(FVector(-470.0f, 110.0f, 0.0f));
	


	//Make sure this parts go last part go last!
	RootComponent = mCollisionBox;
}

// Called when the game starts or when spawned
void APlayer1::BeginPlay()
{

	Super::BeginPlay();
	
}

// Called every frame
void APlayer1::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);


	//DrawDebugPoint(GetWorld(), projectileSpawnPoint, 20, FColor(255, 0, 255), false, 0.03);

	//If the player is grounded, set them still
	if (isGrounded) {
		currentVelocity.Z = 0;
	}
	else if (isAirdashing) {
		UE_LOG(LogTemp, Warning, TEXT("Startin air dash"));
		//Air dash has started, make them move.
		if (abs(airDashStart.Y - GetActorLocation().Y) <=120) {
			jumpTimer = 0;
			currentVelocity.Z += -currentVelocity.Z;
			if (isFacingLeft) {
				currentVelocity.Y = FMath::Clamp(defaultValue, -1.0f, 1.0f) * -500.0f;
			}
			else {
				currentVelocity.Y = FMath::Clamp(defaultValue, -1.0f, 1.0f) * 500.0f;
			}
		}
		//Air dash is done, make them fall now.
		else if (abs(airDashStart.Y - GetActorLocation().Y) >= 120) {
			UE_LOG(LogTemp, Warning, TEXT("Reached End of Airdash"));
			isAirdashing = false;
			currentVelocity.Z = FMath::Clamp(defaultValue, 1.0f, 1.0f) * -300.0f;
			currentVelocity.Y = FMath::Clamp(defaultValue, -1.0f, 1.0f) * 0.0f;
		}

	}
	//If the player is falling and isn't grounded, let them fall
	else if (jumpTimer <= 0.0 && !isGrounded && !isAirdashing) {
		jumpTimer = 0;
		currentVelocity.Z = FMath::Clamp(defaultValue, 1.0f, 1.0f) * -300.0f;
	}
	//If the player isn't grounded but the timer hasn't been reached, they rise.
	else if (jumpTimer >=0 && !isGrounded && !isAirdashing){
		jumpTimer--;
		currentVelocity.Z = FMath::Clamp(defaultValue, 1.0f, 1.0f) * 300.0f;
	}

	//The important part that lets the player actually move.
	if (!currentVelocity.IsZero())
	{
		FVector NewLocation = GetActorLocation() + (currentVelocity * DeltaTime);
		SetActorLocation(NewLocation);
	}
}

// Called to bind functionality to input
void APlayer1::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Binds the axis so when you press the button that corresponds to "MoveX" play this method.
	PlayerInputComponent->BindAxis("MoveX",this, &APlayer1::moveX);

	//The method that makes players jump. Usually an "alley oop" to set a variable to work in the tick function
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayer1::Jump);

	//The method that checks if the player double taps, causing them to air dash forward but only if they're airborne.
	PlayerInputComponent->BindAction("AirDash", IE_DoubleClick, this, &APlayer1::AirDash);

	PlayerInputComponent->BindAction("Special", IE_Pressed, this, &APlayer1::specialButton);
}

void APlayer1::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	//If the player collides with another object that has the tag of floor, say that you collided with it.
	if (OtherComp->ComponentHasTag("Floor")) {
		isGrounded = true;
		UE_LOG(LogTemp, Warning, TEXT("Oh shit we collided with something"));
	}
	//UE_LOG(LogTemp, Warning, TEXT("Oh shit we collided with something"));
}

void APlayer1::moveX(float axisValue)
{
	if (isGrounded) {
		//UE_LOG(LogTemp, Warning, TEXT("Supposed to be moving"));
		currentVelocity.Y = FMath::Clamp(axisValue, -1.0f, 1.0f) * 500.0f;
	}
}

void APlayer1::Jump()
{
	if (isGrounded) {
		jumpTimer = jumpMaximum;
		isGrounded = false;
		UE_LOG(LogTemp, Warning, TEXT("Supposed to be jumping"));
	}

}

void APlayer1::AirDash() {
	isAirdashing = true;
	airDashStart.Y = GetActorLocation().Y;
	UE_LOG(LogTemp, Warning, TEXT("Supposed to be air dashing"));
}

void APlayer1::specialButton()
{
	fireBallFired = true;

	//AFireBall* newFireball = GetWorld()->SpawnActor<AFireBall>(GetClass(), projectileSpawnLocation, FRotator::ZeroRotator);
	
	UE_LOG(LogTemp, Warning, TEXT("Special button pressed!"));
}
