Lesson 110: Create a blank C++ Pawn Class.

Lesson 111: Learn 'Components' in blueprints, each actor has a root component and root component can be replaced by other useful component, such as capsule component.
Compoent B can attach to Componet A. When A is moved or scaled, B will also changes.

Lesson 112: Learn 'Forward Declaration' such as: 
class UCapsuleComponent* CapsuleComp;
in .h file and with out #include relevant .h
Because we should include as little as possible in .h
We don't need the header to declare a pointer. 

Lesson 113: Constructed a Capsule Component, made it the root component.

Lesson 114: Create Components in C++ file, and attach them.

Lesson 115: Derived child blueprints from BasePawn class,but the component in it can't be edit and the propery is blank.

Lesson 116: the difference between Instance & Default, Instance is the actual thing in world, Default is a abstract blurprint or class that doesn't exist in the level.

Lesson 117: UPROPERTY() 's specifiers, such as EditAnywhere, VisibleInstanceOnly and so on;

Lesson 118: Expose the components in C++ class to blueprint, by code: 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CPP Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;

Lesson 119: Create child C class: create Tank class based on BasePawn

Lesson 120: Set Auto Possess Player of Tank instance to Player 0.

Lesson 121: Bind axis mapping to function.
Lesson 121.5: Learned from other lesson, know how to bind input action values to functions in C++, especially by enhanced input system.

Lesson 122: Add actor local offset.
Lesson 123: Add movespeed independent with deltatime. 

Lesson 124: add actor locao rotation, and learn idea of sweep(collision).

Lesson 125: learn cast.

Lesson 126: get the hit result under the cursor.PlayController->GetHitResultUnderCursor
DrawDebugSphere

Lesson 127&128: Rotate the Turret and tower.
Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

Lesson 129: bind IA_Fire and Fire() function.

Lesson 130: create a timer.
GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);

Lesson 131: create a Projectile C class and Blueprint class.

Lesson 132: spawn projectile. 
UPROPERTY(EditAnywhere, Category = "Combat")
TSubclassOf<class AProjectile> ProjectileClass;

GetWorld()->SpawnActor<AProjectile>(ProjectileClass,
	ProjectileSpawnPoint->GetComponentLocation(),
	ProjectileSpawnPoint->GetComponentRotation());

Lesson 133: add ProjectileMovementComponent.

Lesson 134: Hit Events
ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

Lesson 135: create and add Health Component.

Lesson 136: applying damage.
UGameplayStatics::ApplyDamage

Lesson 137: create Game Mode Class and set the default pawn.

Lesson 138: handled actor death.

Lesson 139: Create custom player controller.
Problems: mouse input error while show mouse cursor.

Lesson 140: Create HandleGameStart.

Lesson 141: Create start game widget blueprint.

Lesson 142&143: create variable 'countdown' and test.

Lesson 144&145: Create win/lose conditions and count tower numbers.

Lesson 146&146&147: Add hit, trail and dead particle in projectile.

Lesson 148: Add sound.
