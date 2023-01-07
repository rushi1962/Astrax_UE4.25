// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShip.h"
#include "Asteroid.h"

// Sets default values
ASpaceShip::ASpaceShip()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	TurretBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretBody"));
	TurretBody->SetupAttachment(Collider);

	Turret = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret"));
	Turret->SetupAttachment(TurretBody); 

	Collider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collider->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	Collider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Collider->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	
	MovementSpeed = 200.f;
	BulletSpawnRelativePoint = FVector(0.f);
}

// Called when the game starts or when spawned
void ASpaceShip::BeginPlay()
{
	Super::BeginPlay();

	m_ForwardVector = FVector(1.f, 0.f, 0.f);
}

void ASpaceShip::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	UE_LOG(LogTemp, Warning, TEXT("Begin overlap"));

	AAsteroid* asteroid = Cast<AAsteroid>(OtherActor);

	if (asteroid)
	{
		BeforeSpaceShipDestroyCallBack();
		Destroy();
	}
}

void ASpaceShip::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
	UE_LOG(LogTemp, Warning, TEXT("End overlap"));
}

void ASpaceShip::SetTurretRotation(FVector &direction)
{
	if (direction.Size() > 0.1f)
	{
		float angleFromForwardVector = direction.Y >= 0.f ? FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(m_ForwardVector, direction))) : -FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(m_ForwardVector, direction)));
		TurretBody->SetWorldRotation(FRotator(0.f, angleFromForwardVector, 0.f));
	}
}

FVector& ASpaceShip::GetBulletSpawnPosition(FVector& turretDirection)
{
	m_SpawnPosition = BulletSpawnRelativePoint;
	m_SpawnPosition.Y = m_SpawnPosition.X * turretDirection.Y;
	m_SpawnPosition.X *= turretDirection.X;

	m_SpawnPosition += GetActorLocation();

	return m_SpawnPosition;
}
