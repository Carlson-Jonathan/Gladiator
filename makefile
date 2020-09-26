gladiator.out: main.o combat.o character.o advancedWeapon.o advancedArmor.o general.o
	g++ -o gladiator.out main.cpp character.cpp

main.o: main.cpp character.h 
	g++ -c main.cpp

combat.o: character.h general.h
	g++ -c combat.h

hero.o: advancedWeapon.h 
	g++ -c hero.h

basicWeapon.o: 
	g++ -c basicWeapon.h

advancedWeapon.o: basicWeapon.h
	g++ -c advancedWeapon.h

monster.o: advancedWeapon.h 
	g++ -c monster.h

basicArmor.o: 
	g++ -c basicArmor.h

advancedArmor.o: basicArmor.h
	g++ -c advancedArmor.h

general.o:
	g++ -c general.h
