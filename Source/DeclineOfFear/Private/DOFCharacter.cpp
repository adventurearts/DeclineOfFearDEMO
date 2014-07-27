

#include "DeclineOfFear.h"
#include "DOFCharacter.h"


ADOFCharacter::ADOFCharacter(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	cameraSupport = PCIP.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("CameraSupport"));
	cameraSupport->AttachTo(RootComponent);
	cameraSupport->bEnableCameraLag = true;
	cameraSupport->bEnableCameraRotationLag = true;
	cameraSupport->CameraLagSpeed = 3.f;
	cameraSupport->CameraRotationLagSpeed = 8.f;
	cameraSupport->bUseControllerViewRotation = true;

	playerCamera = PCIP.CreateDefaultSubobject<UCameraComponent>(this, TEXT("PlayerCamera"));
	playerCamera->AttachTo(cameraSupport, USpringArmComponent::SocketName);
	playerCamera->bUseControllerViewRotation = false;
}

void ADOFCharacter::BeginPlay()
{
	
}

void ADOFCharacter::SetupPlayerInputComponent(class UInputComponent *InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	check(InputComponent);

	InputComponent->BindAction("UnPossessAvatar", IE_Released, this, &ADOFCharacter::unPossessMe);

	InputComponent->BindAxis("Turn", this, &ADOFCharacter::Turn);
	InputComponent->BindAxis("LookUp", this, &ADOFCharacter::LookUp);
	InputComponent->BindAxis("WalkForward", this, &ADOFCharacter::WalkForward);
	InputComponent->BindAxis("WalkRight", this, &ADOFCharacter::WalkRight);
	InputComponent->BindAction("CameraZoomIn", EInputEvent::IE_Released, this, &ADOFCharacter::CameraZoomIn);
	InputComponent->BindAction("CameraZoomOut", EInputEvent::IE_Released, this, &ADOFCharacter::CameraZoomOut);
}

void ADOFCharacter::unPossessMe()
{
	if (Controller != nullptr)
	{
		Controller->PlayerState->bIsSpectator = true;
		Controller->ChangeState(NAME_Spectating);

#ifdef UE_EDITOR

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("UnPossessed"));
		}

#endif
	}
}

void ADOFCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ADOFCharacter::LookUp(float val)
{
	AddControllerPitchInput(val * - 60.0f * GetWorld()->GetDeltaSeconds());
}

void ADOFCharacter::Turn(float val)
{
	AddControllerYawInput(val * 40.0f * GetWorld()->GetDeltaSeconds());
}

void ADOFCharacter::WalkForward(float val)
{
	FRotator viewRotator = GetControlRotation();
	FVector viewDirection = viewRotator.Vector().SafeNormal2D();

	AddMovementInput(viewDirection, val * 0.5f);
}

void ADOFCharacter::WalkRight(float val)
{
	FRotator viewRotator = GetControlRotation().Add(0.f, 90.f, 0.f);
	FVector viewDirection = viewRotator.Vector().SafeNormal2D();
	
	AddMovementInput(viewDirection, val * 0.5f);
}

void ADOFCharacter::CameraZoomIn()
{
	
}

void ADOFCharacter::CameraZoomOut()
{
	
}