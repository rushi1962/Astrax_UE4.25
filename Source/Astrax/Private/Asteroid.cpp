// Fill out your copyright notice in the Description page of Project Settings.


#include "Asteroid.h"

AAsteroid::AAsteroid()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AAsteroid::BeginPlay()
{
	Super::BeginPlay();

	SetMovementDirection(GetActorForwardVector());
	m_RotationSpeed = FRotator(FMath::FRandRange(-300.f, 300.f), FMath::FRandRange(-300.f, 300.f), FMath::FRandRange(-300.f, 300.f));
}

// Called every frame
void AAsteroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Mesh->SetWorldRotation(Mesh->GetComponentRotation() + m_RotationSpeed * DeltaTime);
}

void AAsteroid::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	AAsteroid* otherAsteroid = Cast<AAsteroid>(OtherActor);

	if (otherAsteroid == nullptr)
	{
		Collider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		BeforeDestructionCallback();
		Destroy();
	}
}

void AAsteroid::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}
