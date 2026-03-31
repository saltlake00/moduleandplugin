# ModuleAndPlugin

Unreal Engine 5.5 프로젝트 — 커스텀 플러그인 모듈(`MySpartaLog`) 연동 예제입니다.

---

## 프로젝트 개요

이 프로젝트는 UE5에서 **커스텀 플러그인**과 **게임 모듈** 간의 의존성 설정 및 로그 카테고리 사용법을 학습하기 위한 교안용 예제입니다.

- 커스텀 플러그인(`MyNBCLog`)을 직접 제작하고 게임 모듈에서 참조하는 방법을 보여줍니다.
- 플러그인 모듈에서 정의한 로그 카테고리(`LogMySpartaModule`)를 외부 모듈에서 사용하는 방법을 실습합니다.

---

## 프로젝트 구조

```
ModuleAndPlugin/
├── ModuleAndPlugin.uproject          # 프로젝트 설정 (엔진 5.5, 플러그인 목록)
│
├── Source/
│   ├── ModuleAndPlugin/              # 메인 게임 모듈
│   │   ├── ModuleAndPlugin.Build.cs  # 빌드 설정 (MySpartaLog 의존성 포함)
│   │   ├── ModuleAndPlugin.h / .cpp  # 모듈 진입점
│   │   ├── ModuleAndPluginCharacter.h / .cpp  # 플레이어 캐릭터 (ThirdPerson 기반)
│   │   ├── ModuleAndPluginGameMode.h / .cpp   # 게임 모드
│   │   └── TestActor.h / .cpp        # 플러그인 로그 사용 예제 액터
│   │
│   ├── ModuleAndPlugin.Target.cs     # Game 빌드 타겟
│   └── ModuleAndPluginEditor.Target.cs  # Editor 빌드 타겟
│
└── Plugins/
    └── MyNBCLog/
        ├── MyNBCLog.uplugin          # 플러그인 메타데이터
        └── Source/
            └── MySpartaLog/
                ├── MySpartaLog.Build.cs  # 플러그인 모듈 빌드 설정
                ├── MySpartaLog.h         # 로그 카테고리 선언 + 모듈 클래스
                └── MySpartaLog.cpp       # 모듈 시작/종료 로직
```

---

## 핵심 구성 요소

### 플러그인: `MyNBCLog`

| 항목 | 내용 |
|------|------|
| 플러그인 이름 | MyNBCLog |
| 모듈 이름 | MySpartaLog |
| 로그 카테고리 | `LogMySpartaModule` |
| 로딩 페이즈 | Default (Runtime) |

`MySpartaLog.h`에서 `MYSPARTALOG_API`를 통해 로그 카테고리를 외부에 공개합니다.

```cpp
MYSPARTALOG_API DECLARE_LOG_CATEGORY_EXTERN(LogMySpartaModule, Log, All);
```

모듈 시작 시 경고 로그를 출력합니다.

```cpp
void FMySpartaLog::StartupModule()
{
    UE_LOG(LogMySpartaModule, Warning, TEXT("MySpartaLog is Start"));
}
```

---

### 게임 모듈: `ModuleAndPlugin`

`ModuleAndPlugin.Build.cs`에서 `MySpartaLog`를 PublicDependency로 추가해 플러그인 모듈을 참조합니다.

```csharp
PublicDependencyModuleNames.AddRange(new string[]
{
    "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "MySpartaLog"
});
```

---

### TestActor

게임 시작 시 캐릭터의 `BeginPlay()`에서 `ATestActor`를 스폰하며, `TestActor`는 플러그인의 로그 카테고리를 사용해 메시지를 출력합니다.

```cpp
// ModuleAndPluginCharacter.cpp
void AModuleAndPluginCharacter::BeginPlay()
{
    Super::BeginPlay();
    GetWorld()->SpawnActor(ATestActor::StaticClass());
}

// TestActor.cpp
void ATestActor::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogMySpartaModule, Display, TEXT("Actor call MySpartaLog Module!"));
}
```

---

## 빌드 및 실행

### 요구 사항

- Unreal Engine **5.5**
- Visual Studio 2022 (Windows) 또는 Xcode (Mac)

### 빌드 방법

1. `ModuleAndPlugin.uproject`를 우클릭 → **Generate Visual Studio project files** 선택
2. 생성된 솔루션(`.sln`)을 Visual Studio에서 열기
3. 빌드 타겟을 `ModuleAndPluginEditor` 또는 `ModuleAndPlugin`으로 설정 후 빌드

### 실행 확인

게임 실행 후 **Output Log**에서 아래 두 메시지를 확인할 수 있습니다.

```
LogMySpartaModule: Warning: MySpartaLog is Start
LogMySpartaModule: Display: Actor call MySpartaLog Module!
```

---

## 학습 포인트

1. **플러그인 생성** — `.uplugin` 파일 구성 및 모듈 선언 방법
2. **모듈 간 의존성** — `Build.cs`의 `PublicDependencyModuleNames`를 통한 플러그인 모듈 참조
3. **로그 카테고리 공개** — `DECLARE_LOG_CATEGORY_EXTERN` + API 매크로로 외부 모듈에 노출
4. **Target.cs 설정** — `ExtraModuleNames`에 플러그인 모듈 추가

---

## 참고

- 작성자: Eunil
- 엔진 버전: Unreal Engine 5.5
- 카테고리: Sparta
