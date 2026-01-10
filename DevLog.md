### FPS Assignment

## 项目地址

[FPSAssignment](https://github.com/Don-James-shrinp/FPSAssignment)
## 游戏整体流程(Game Loop)
在限定时间内击杀Enemy AI，击杀AI会获得分数，被Enemy AI击杀则会扣分，最后得分最多的玩家获胜

## GAS输入绑定
本质上就是给由Input来trigger触发的Ability绑定事件回调函数，其实现的方式如下
1. 与其他Ability一样，首先会将其存入Data Asset中，其会与一个Input Tag对应
2. 在加载Data Asset时，会通过Ability System Component将Ability给予角色，在给予角色前，会将InputTag加入到AbilitySpec的DynamicSpecSourceTags容器中，使得InputTag可以和Ability建立对应关系
3. 在上述基础之上，事件回调函数就可以统一，本质上就是按下(pressed)就激活该Ability，然后松开(released)就移除该Ability，如何找到对应的Ability？上述的InputTag就发挥了作用，只需要找到与当前输入的InputTag对应的Ability即可（现在的实现方式存在着性能问题，通过`GetActivatableAbilities`来获取所有可激活的Ability，然后找到与InputTag匹配的Abiilty，算法复杂度为O(n)，该部分的性能开销会随着Ability数量的增加而增加，有待优化）

## 武器的管理
对于武器，我们将其分为了敌人的武器（其在敌人生成时就直接装备）和玩家的武器（武器初始状态下不会装备，需要玩家通过输入来触发武器的装备）

敌人和玩家的武器有一些公有的部分（比如StaticMeshComponent），但是对于玩家武器来说，其需要一些附属在武器上的Weapon Data，比如又Weapon带来的Anim Layer（因为装备与否其动画是不一样的）和Weapon带来的额外的Ability（开火的Ability等），因此可以把公有的部分抽象成一个基类，然后派生出一个PlayerWeapon

对于武器的管理，我们通过给角色增加一个Component进行武器的管理，其中通过一个Map数据结构通过GameplayTag来查询对应的武器，然后在武器被生成时就会调用该Component的武器注册函数将其存入Map中，同样的因为需要同时管理敌人Weapon和Player Weapon，但是其武器注册的逻辑是公有的，因此可以将其放在基类Component，然后派生出一个PlayerComponent来实现其特有的Getter来获取PlayerWeapon

## 动画资产复用
在Unreal的FPS的模板中，仅提供了Equip武器的Animation Sequence，并没有提供Unequip的Animation Sequence，但是我们起始可以通过倒放Equip的动画来获得Unequip的动画

1. 创建原始Animation Sequence的副本
2. 然后设置其Play Rate为-1就可以实现倒放
3. 然后基于此动画资产创建Anim Montage实现后续的Unequip

## AnimLayer
角色往往存在多套动画，比如角色在不装备武器时使用一套动画，在装备武器时使用另一套动画，为了提高角色动画系统的可扩展性，引入了AnimLayer的概念，通过此设计，不同的Anim可以动态的装载(Link)和卸载(Unlink)，从而动态的实现不同动画之间切换，具体实现流程如下

1. 创建Animation Layer Interface，在其中定义所有的AnimLayer，但是并不会给出实现这些定义的AnimLayer
2. 然后通过创建一个继承自自定义的AnimLinkedLayer class的Anim Blueprint，我们将其称为Base_AnimLayer，并实现上述Animation Layer Interface，给这些AnimLayer一个具有普适性的实现，将实际的动画资产的填充下放给实际的AnimLayer
3. 而对于真正的AnimLayer则继承自上述Base_AnimLayer，并填入实际的动画资产
4. 在WeaponData中只需维护一个AnimLinkedLayer类的指针，并填入相应的AnimLayer即可，然后在装备武器后，从WeaponData中找到AnimLayer，并将其进行Link即可
5. 此外主AnimBP中，需要实现上述Animation Layer Iterface，然后根据实际情况（比如通过是否装备武器的branch）来决定是否要使用AnimLayer来作为当前的动画
参考文档：[UE5 白话Lyra动画系统](https://zhuanlan.zhihu.com/p/654430436)

## 属性设计(Attribute)
### 角色属性
与角色绑定的属性放在AttributeSet中(GAS中用于维护角色属性的数据结构)
- 生命值
- 防御值
### 武器属性
与武器绑定的属性，可以将其分为静态属性和动态属性
静态属性
- 武器伤害：可以放在WeaponData中，决定该武器能够造成的伤害
- 武器的弹夹容量：可以容纳的弹药上限
动态属性
- 武器的弹药数量：当前弹夹中剩余的弹药数量，会随着武器的开火、装弹等行为动态发生变化，可以作为武器的成员，然后由Combat Component提供接口来动态改变该属性

## UI和角色之间的数据通信
对于角色的UI，比如说血条的显示，其需要依赖角色的生命值属性，当角色的生命值发生变化时，就需要通过某种方式将此信息传递给UI，使其能够根据此信息来更新UI

类似于对武器的管理，同样可以通过一个UIComponent来对角色和UI之间的数据通信进行管理，本质上就是在此Component中定义一系列Delegate，然后在UI端会listen这些Delegate并实现相应的回调函数来更新UI，在Character端，当属性发生更新时就会对Delegate进行Broadcast，将属性更新的信息传递给UI，这样就实现了从Character到UI的数据通信

## 射击状态设计
射击状态可以分为非瞄准状态下的射击(Dry Fire)和瞄准状态下的射击(Aim Fire)

当玩家按下鼠标的右键就会进入瞄准状态，此时玩家会拥有一个Gameplay Status Tag表示玩家处于瞄准状态，只有在拥有该Status Tag下才能够触发瞄准射击的Ability，通过指定Gameplay Ability的Activation Required Tag来实现

此外在瞄准状态下，将无法激活Dry Fire，通过设置Dry Fire Ability的Activate Blocked Tag来实现

## 弹药管理
枪械的弹药应该与武器绑定在一起，主要用于进行弹药数量的管理，用于处理子弹发射和重新装填子弹的子弹数量的动态管理

由于子弹这个对象是频繁创建和销毁的，如果频繁的调用SpawnActor来生成子弹对象，调用Destory来销毁不需要的子弹对象，就会因为频繁的创建和销毁产生额外的开销，因此可以通过对象池来优化，通过设计一个子弹对象池的组件挂载在武器上，武器的进行发射时会向该子弹索要空闲的子弹对象，然后当子弹要进行销毁操作时，不会将其真正销毁，而是将其状态设置为空闲状态；此外，当子弹数量的需求超过了对象池当前的容量时，需要进行动态扩容，即需要创建新的子弹对象加入到对象池中。

整体流程如下
1. 首先会在PoolComponent中创建对象池的所有的子弹，子弹类的BeginPlay函数中会绑定子弹的碰撞盒的碰撞回调函数，即只需要绑定一次就可以反复使用此回调函数
2. 射击时，通过武器的PoolComponent来获取子弹，通过子弹的SetActive传入必要的参数，比如说Instigator信息，以及子弹生成的位置、Rotation信息
3. 在SetActive函数中根据传入的参数将选中的空闲子弹设置为激活状态，将其发射出去，并设置子弹的生命周期Timer，当Timer计时结束后就自动回收子弹
4. 当子弹命中Actor，就会向Instigator发送事件，供射击者进行击中处理，然后子弹被回收

## 调试技巧
### Ability System调试
按下引号`"`按键（回车旁边的按键），可以进入Gameplay Debugger调试界面，通过按下小键盘的数字键可以显式自己需要的调试信息

此外，通过在命令行中（通过\`键打开命令行）输入`ShowDebug AbilitySystem`展示Ability System的调试信息

### Visual Studio Attach To Process

在开发的过程中，遇到了卡死的问题，一般就是程序陷入了死循环导致的，通过Visual Studio提供的Attach To Process功能就能够通过Call Stack信息找到程序卡在哪一行指令上

1. 启动Unreal Editor（可以不需要通过Visual Studio启动，通过.uproject独立启动也行）
2. 在Visual Studio中`Debug>Attach To Process`，将`UnrealEditor.exe`Attach过去
3. 然后复现卡住的情况
4. 回到Visual Studio点击Break All（两根竖线`||`的按钮）
5. 然后在Call Stack窗口中查看最后调用的指令



## Bug及解决方案

### UIComponent为空导致的空指针访问(Access Violation)

**BUG**: 加载Enemy的GameplayEffect（主要原因在于加载与CurrentHealth相关的GameplayEffect）时导致游戏的崩溃。

在实现Enemy时，由于AttributeSet(声明在BaseCharacter类中)中定义了如下的代码，因此其需要通过GetPawnUIComponent方法来获取PawnUIComponent，BaseCharacter虽然实现了IPawnUIInterface接口，但是其没有PawnUIComponent成员，其函数也只是默认实现，即返回nullptr，因此需要派生类自己声明自己的PawnUIComponent，并override相应的函数，使得其能够获得有效的PawnUIComponent，如果没有定义就会出现空指针访问的错误(Access Violation)，因此在处理指针是需要额外注意，必要时加上check或者checkf，使得程序崩溃时可以知道是哪里的问题

```c++
void UFPSAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	if (!CachedPawnUIInterface.IsValid())
	{
		CachedPawnUIInterface = TWeakInterfacePtr<IPawnUIInterface>(Data.Target.GetAvatarActor());
	}
	checkf(CachedPawnUIInterface.IsValid(), TEXT("%s didn't implement IPawnUIInterface"), *Data.Target.GetAvatarActor()->GetActorNameOrLabel());

	UPawnUIComponent* PawnUIComponent = CachedPawnUIInterface->GetPawnUIComponent();

	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())  //  生命值发生变化之后，需要通过PawnUIComponent对Delegate进行Broadcast
	{
		const float NewHealth = FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth());
		SetCurrentHealth(NewHealth);
		PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());
	}
}

```

此外在BaseClass的PossessedBy函数中，初始化了AbilitySystemComponent的信息(AvatarActor)，在派生类中需要override该函数，用于加载StartupData，但是需要通过静态的方式来调用基类的PossessedBy函数，通过`Super::PossessedBy(NewController)`来调用，但是在实现时没有调用，导致AbiltiySystemComponent的信息无效



### Enemy的GameplayEffect无法生效问题

**BUG**: Enemy虽然在StartupData中传入了自己的GameplayEffect，但是却无法生效，其Apply的依然是Player定义的GameplayEffect，导致两者的属性完全一致，即Enemy和Player共用一个GameplayEffect

貌似是showdebug abilitysystem仅会显示客户端的属性，最好使用`"`按键进行AbilitySystem的Debug

## UnrealEditor中设置的初值没法修改成员变量

在Weapon类中，我设置了MaxAmmo，并将其UPROPERTY设置为EditDefaultsOnly，即可以在Unreal Editor中修改其默认值，此外我还定义了CurrentAmmo私有成员，用于记录当前的子弹数量

我在类中给了MaxAmmo默认初值，并在构造函数中将CurrentAmmo设置为MaxAmmo，但是当我在UnrealEditor中修改了MaxAmmo的初值后，CurrentAmmo的值却依然没有改变，依然是类中默认的初值

这跟Unreal C++的生命周期有关

1. 首先会进行构造函数
2. 然后序列化/属性加载，将UnrealEditor的属性加载到成员上
3. BeginPlay/OnConstruction：游戏开始

所以，在构造函数中赋值时机过早，应该在BeginPlay中进行赋值
