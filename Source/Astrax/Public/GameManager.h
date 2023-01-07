// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "SpaceShip.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "GameManager.generated.h"

UCLASS()
class ASTRAX_API AGameManager : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGameManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MainCamera)
		UCameraComponent* MainCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
		float XBorder;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
		float YBorder;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GamePlay)
		float SafeDistance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GamePlay)
		int LifeLimit;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GamePlay)
		float RespawnTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GamePlay)
		int Points;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Spawning Blueprints")
		TSubclassOf<class ASpaceShip> SpaceShipToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Spawning Blueprints")
		TSubclassOf<class ABullet> BulletToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Spawning Blueprints")
		TSubclassOf<class AAsteroid> AsteroidToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Spawning Blueprints")
		TSubclassOf<class AAsteroid> AsteroidToSpawn_01;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Spawning Blueprints")
		TSubclassOf<class AAsteroid> AsteroidToSpawn_02;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mouse Position")
		FVector2D MousePosition;

	UFUNCTION(BlueprintCallable)
		void IncreamentPoints(int level);

	UFUNCTION(BlueprintCallable)
		void AsteroidDestructionCallback(AAsteroid* asteroid, int level);

	UFUNCTION(BlueprintCallable)
		void SpaceShipDestructionCallback();

	UFUNCTION(BlueprintImplementableEvent)
		void RestartThetGame();

private:

	FVector m_SpaceShipMovement;
	FVector m_CurrentPositionOfShip;

	float xMousePos;
	float yMousePos;
	float zPos;
	FVector turretDirection;

	bool bIsPlayerAlive;

	ASpaceShip* m_currentSpaceShip;
	TArray<AAsteroid*> m_CurrentAsteroid;

	FTimerHandle m_RespawnTimerHandler;
	FTimerHandle m_ResetGameTimerHandler;

	void MoveLongitudenally(float yMovment);
	void MoveLaterally(float xMovment);

	AActor* SpawnActor(UClass* ToSpawn, FVector& position, FRotator rotation = FRotator(0.f));
	ASpaceShip* SpawnSpaceShip();
	ABullet* SpawnBullet();
	void Fire();
	void SpawnAsteroids(TArray<FVector>& positions, int level); 
	void RespawnSpaceShip();
	bool IsAtSafeDistance(FVector& position);
};
