// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpaceObject.h"
#include "Asteroid.generated.h"

/**
 * 
 */
UCLASS()
class AAsteroid : public ASpaceObject
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAsteroid();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Asteroid Variables")
		int Level;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

public :
	UFUNCTION(BlueprintImplementableEvent)
		void BeforeDestructionCallback();

private:
	FRotator m_RotationSpeed;
};
