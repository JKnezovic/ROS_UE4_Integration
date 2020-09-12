# ROS_UE4_Integration

## OPIS

Povezan UE4 na windows hostu s ROS-om na linux virtualnoj mašini preko ROS bridge-a i ROSIntegrationa. 
Tipkama preko ROS sučelja se šalju poruke preko ROS bridge-a na koje je pretplaćen projek u UE4. Preko poruka se zadaju komande za upravljanje letjelice unutar UE4.

## UPUTE
postaviti [ROSIntegration](https://github.com/code-iai/ROSIntegration) plugin kako je napisano u uputama .

### ROS

Upaliti ROSbridge te pokreniti skriptu keyteleop.

keyteleop.py stvara sučelje za upravljanje. Kada se stisne tipka šalje se nova poruka tipa  Twist/geometry preko topica key_vel 

### UE4

Kada se kreira file ListenerPawn treba postaviti runtime od ROSIntegration plugina, a ne od projekta.

Skripte za upravljanje letjelicom i za pretplaćivanje na topic spojiti na mesh letjelice.

U ROSIntegration.Build.cs file treba unutar funkcije PublicDependencyModulesName dodati ime projekt da bi fileove koji imaju runtime plugina mogli include-at klase iz glavnog projekta:
```c++

PublicDependencyModuleNames.AddRange(
	new  string[]
		{
		"Core",
		"Sockets",
		"Networking",
		"Spaceship"
		// ... add other public dependencies that you statically link with here ...
		}
);
```
ListenerPawn se subscribea na topic key_vel, raspakira poruke u vektore, pronađe klasu letjelice te poziva njene funkcije za upravljenje u koje šalje vrijednost dobivenih iz poruka s ROS-a.
