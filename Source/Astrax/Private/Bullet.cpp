// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Asteroid.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DestructionTime = 10.f;
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(m_TimerHandle, this, &ABullet::DestroyBullet, DestructionTime);
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABullet::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	AAsteroid* asteroid = Cast<AAsteroid>(OtherActor);

	if (asteroid)
	{
		IncreamentPoints(asteroid->Level);
		DestroyBullet();
	}
}

void ABullet::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}

void ABullet::DestroyBullet()
{
	Destroy();
}

