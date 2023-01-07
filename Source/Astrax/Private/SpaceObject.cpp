// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceObject.h"

// Sets default values
ASpaceObject::ASpaceObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	SetRootComponent(Collider);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collider);

	Collider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collider->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	Collider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Collider->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	MovementSpeed = 500.f;
}

// Called when the game starts or when spawned
void ASpaceObject::BeginPlay()
{
	Super::BeginPlay();
	
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ASpaceObject::OnOverlapBegin);
	Collider->OnComponentEndOverlap.AddDynamic(this, &ASpaceObject::OnEndOverlap);
}

// Called every frame
void ASpaceObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() + m_MovementDirection * MovementSpeed * DeltaTime);

	FVector currentObjectLocation = GetActorLocation();

	if (currentObjectLocation.X < -m_XBorder)
	{
		currentObjectLocation.X = m_XBorder;
		SetActorLocation(currentObjectLocation);
	}
	else if (currentObjectLocation.X > m_XBorder)
	{
		currentObjectLocation.X = -m_XBorder;
		SetActorLocation(currentObjectLocation);
	}
	else if (currentObjectLocation.Y > m_YBorder)
	{
		currentObjectLocation.Y = -m_YBorder;
		SetActorLocation(currentObjectLocation);
	}
	else if (currentObjectLocation.Y < -m_YBorder)
	{
		currentObjectLocation.Y = m_YBorder;
		SetActorLocation(currentObjectLocation);
	}
}

void ASpaceObject::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Begin overlap Spaceobject"));
}

void ASpaceObject::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("End overlap Spaceobject"));
}

