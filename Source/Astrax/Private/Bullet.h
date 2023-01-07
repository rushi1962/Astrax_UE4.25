// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SpaceObject.h"
#include "Bullet.generated.h"

UCLASS()
class ABullet : public ASpaceObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Destruction Time")
		float DestructionTime;

	UFUNCTION(BlueprintImplementableEvent)
		void IncreamentPoints(int level);

private:
	FTimerHandle m_TimerHandle;

	void DestroyBullet();
};
