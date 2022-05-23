# Beágyazott Linux alapú modell autó

## I. Motiváció
- Szerettem volna egy teljes rendszert építeni, amelyben hardveres és szoftveres feladatok egyaránt vannak.
- Szoftver és hardver határán minél nagyobb tapasztalatra szert tenni.
- Hosszabb távú projektet végigvinni, ami modulárisan fejleszthető

## II. A cél: teljesen saját vázú és elektronikájú autó/robot
- Cél a tapasztalatszerzés:
  - saját elektronika tervezése (NYÁK tervezésben tapasztalat)
  - saját firmware (STM32 mikorvezérlőkkel tapasztalat)
  - Saját vezérlés (Linux tapasztalat)
- későbbiekben új funkciókkal legyen bővíthető: moduláris kialakítás-> továbbfejleszthetőség

## III. A projekt:
- egy irányítható/önjáró autó építése
  - táp áramkör (akksikkal, BMSel, )
  - meghajtás vezérlő (STM32)
  - Raspberry Pi (Linux)
    - vezeték nélküli kommunikációs lehetőség
  - forgatható kamera, mint egy periszkóp -> video streaming.
  - opcionálisan, valamilyen egyéb kommunikációs modul.

## IV. Blokkdiagram a rendszerről (Gen 1)

<Random nagy kép>

## V. Hardver tervek (táp)
- schematic
- layout

- olyan alkatrészekből dolgoztam amiket találtam,
- Pi, 15W + meghajtás, ~15W -> ~30W -ra tervezett táp
  - IN
    - 12V
  - OUT
    - 3V3 -> vezérlő elektronika
    - 5V  -> Raspi táp
    - 6V  -> motor meghajtások
- layout inkább nagy területek kitöltésével kapcsol össze, hogy csökkentse a zavarokat.

## VI. Hardver tervek (vezérlés)
- schematic

- megvalósított funkciók:
  - motorvezérlés -> két motor külön kerekeket vezérel
  - lidar távolságérzékelés -> ütközés figyelmeztetés
  - 1 szervómotor meghajtás -> opcionálisan majd egy kamerának
  - debug led, btn, uart
  - raspberry kommunikáció (I2C)

- layout

## VII. Problémák
- alkatrészhiány -> "dolgozzunk abbol ami van" -> sok effortot megevett
- Modularitás szempontjából célszerűbb lett volna külön venni a szervó, és a léptetőmotorok irányítását.
- alkatrészek rendelésénél a motorok mérete nem megfelelő (túl nehéz a léptetőmotor)
- váz megtervezése még teljesen fiktív

## VIII. továbbfejleszthetőség
- kamera beépítése
- gyorsulás mérés (mozgásvezérlés)
- vezeték nélküli kommunikáció, esetleges nagy távolságú kommunikáció
- saját akkumulátor menedzsment, beépített töltési lehetőség
- vezérlő operációs rendszer fordítása, és vezérlőprogram írása
