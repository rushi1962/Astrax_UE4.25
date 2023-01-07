// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"

// Sets default values
AGameManager::AGameManager()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	SetRootComponent(MainCamera);

	XBorder = 10.f;
	YBorder = 6.f;
	LifeLimit = 3;
	bIsPlayerAlive = true;
}

// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
	Super::BeginPlay();
	SetActorRotation(FRotator(-90.f,0.f,0.f));
	m_SpaceShipMovement = FVector(0.f,0.f,0.f);

	TArray<FVector> asteroidsPosition;

	for (int i = 0; i < 3; i++)
	{
		asteroidsPosition.Emplace(FVector(FMath::FRandRange(-XBorder + 1.f, XBorder - 1.f), FMath::FRandRange(-YBorder + 1.f, YBorder - 1.f), -500.f));
	}

	SpawnAsteroids(asteroidsPosition, 1);

	RespawnSpaceShip();

	xMousePos = 0.f;
	yMousePos = 0.f;
	zPos = -500.f;
}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_currentSpaceShip && bIsPlayerAlive)
	{
		m_SpaceShipMovement.Normalize();
		m_currentSpaceShip->SetMovementDirection(m_SpaceShipMovement);
		m_CurrentPositionOfShip = m_currentSpaceShip->GetActorLocation();

		xMousePos = -(FMath::GetMappedRangeValueClamped(FVector2D(0.f, 1.f), FVector2D(-XBorder, XBorder), MousePosition.X));
		yMousePos = FMath::GetMappedRangeValueClamped(FVector2D(0.f, 1.f), FVector2D(-YBorder, YBorder), MousePosition.Y);


		turretDirection = FVector(xMousePos, yMousePos, zPos) - m_CurrentPositionOfShip;
		turretDirection.Normalize();
		m_currentSpaceShip->SetTurretRotation(turretDirection);
	}
}

// Called to bind functionality to input
void AGameManager::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AGameManager::MoveLongitudenally);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AGameManager::MoveLaterally);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AGameManager::Fire);
}

void AGameManager::MoveLongitudenally(float yMovment)
{
	m_SpaceShipMovement.X = yMovment;
}

void AGameManager::MoveLaterally(float xMovment)
{
	m_SpaceShipMovement.Y = xMovment;
}

ASpaceShip* AGameManager::SpawnSpaceShip()
{
	FVector positionToSpawn = GetActorLocation();
	positionToSpawn.Z -= 500.f;	

	do 
	{
		positionToSpawn.X = FMath::FRandRange(-XBorder + 1, XBorder - 1);
		positionToSpawn.Y = FMath::FRandRange(-YBorder + 1, YBorder - 1);
	} while (!IsAtSafeDistance(positionToSpawn));

	return Cast<ASpaceShip>(SpawnActor(SpaceShipToSpawn, positionToSpawn));
}

bool AGameManager::IsAtSafeDistance(FVector& position)
{
	bool isSafe = true;
	for (int i = 0; i < m_CurrentAsteroid.Num(); i++)
	{
		if ((m_CurrentAsteroid[i]->GetActorLocation() - position).Size() < SafeDistance) return false;
	}

	return isSafe;
}

void AGameManager::RespawnSpaceShip()
{
	bIsPlayerAlive = true;
	m_currentSpaceShip = SpawnSpaceShip();

	m_currentSpaceShip->SetXBorder(XBorder);
	m_currentSpaceShip->SetYBorder(YBorder);
}

void AGameManager::SpaceShipDestructionCallback()
{
	LifeLimit--;
	bIsPlayerAlive = false;

	if (LifeLimit > 0)
	{
		GetWorldTimerManager().SetTimer(m_RespawnTimerHandler, this, &AGameManager::RespawnSpaceShip, RespawnTime);
	}
	else
	{
		GetWorldTimerManager().SetTimer(m_ResetGameTimerHandler, this, &AGameManager::RestartThetGame, 5.f);
	}
}

void AGameManager::Fire()
{
	if (m_currentSpaceShip && bIsPlayerAlive)
	{
		ABullet* bullet = SpawnBullet();
		ASpaceObject* spaceObject = Cast<ASpaceObject>(bullet);
		if (spaceObject)
		{
			spaceObject->SetMovementDirection(spaceObject->GetActorForwardVector());
			spaceObject->SetXBorder(XBorder);
			spaceObject->SetYBorder(YBorder);
		}
	}
}

ABullet* AGameManager::SpawnBullet()
{
	if (BulletToSpawn)
	{
		FVector& spawnPosition = m_currentSpaceShip->GetBulletSpawnPosition(turretDirection);
		return Cast<ABullet>(SpawnActor(BulletToSpawn, spawnPosition, m_currentSpaceShip->TurretBody->GetComponentRotation()));
	}
	return nullptr;
}

void AGameManager::AsteroidDestructionCallback(AAsteroid* asteroid, int level)
{
	m_CurrentAsteroid.Remove(asteroid);

	if (level < 3)
	{
		TArray<FVector> positions;
		FVector position = asteroid->GetActorLocation();
		for (int i = 0; i < 3; i++)
			positions.Emplace(position);

		SpawnAsteroids(positions, asteroid->Level + 1);
	}

	if (m_CurrentAsteroid.Num() <= 0)
	{
		GetWorldTimerManager().SetTimer(m_ResetGameTimerHandler, this, &AGameManager::RestartThetGame, 5.f);
	}
}

void AGameManager::SpawnAsteroids(TArray<FVector>& positions, int level)
{
	for (int i = 0; i < positions.Num(); i++)
	{
		if (AsteroidToSpawn)
		{
			float rotation = FMath::FRandRange(1.f, 359.f);
			AActor* actor = nullptr;

			switch(level)
			{
				case 1:
					actor = SpawnActor(AsteroidToSpawn, positions[i], FRotator(0.f, rotation, 0.f));
					break;

				case 2:
					actor = SpawnActor(AsteroidToSpawn_01, positions[i], FRotator(0.f, rotation, 0.f));
					break;

				case 3:
					actor = SpawnActor(AsteroidToSpawn_02, positions[i], FRotator(0.f, rotation, 0.f));
					break;
			}

			ASpaceObject* asteroid = Cast<ASpaceObject>(actor);
			AAsteroid* newAsteroid = Cast<AAsteroid>(asteroid);

			if (newAsteroid)
			{
				m_CurrentAsteroid.Emplace(newAsteroid);
			}

			if (asteroid)
			{
				asteroid->MovementSpeed = FMath::FRandRange(100.f, 300.f);
				asteroid->SetXBorder(XBorder);
				asteroid->SetYBorder(YBorder);
				asteroid->SetActorScale3D(FVector(1.f)/level);
			}
		}
	}
}

AActor* AGameManager::SpawnActor(UClass* ToSpawn, FVector& position, FRotator rotation)
{
	if (ToSpawn)
	{
		UWorld* world = GetWorld();
		FActorSpawnParameters params;

		if (world)
		{
			AActor* actorSpawned = world->SpawnActor<AActor>(ToSpawn, position, rotation, params);
			return actorSpawned;
		}
		return nullptr;
	}

	return nullptr;
}

void AGameManager::IncreamentPoints(int level)
{
	Points += 10 * level;
}

