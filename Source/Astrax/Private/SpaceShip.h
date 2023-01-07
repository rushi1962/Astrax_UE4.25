// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SpaceObject.h"
#include "SpaceShip.generated.h"

UCLASS()
class ASpaceShip : public ASpaceObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpaceShip();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh)
		UStaticMeshComponent* TurretBody;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh)
		UStaticMeshComponent* Turret;

	UPROPERTY(EditAnywhere, meta = (MakeEditWidget = "true"))
		FVector BulletSpawnRelativePoint;

	UFUNCTION(BlueprintImplementableEvent)
		void BeforeSpaceShipDestroyCallBack();

	void SetTurretRotation(FVector &direction);
	FVector& GetBulletSpawnPosition(FVector& turretDirection);

private:
	FVector m_ForwardVector;
	FVector m_SpawnPosition;
};
