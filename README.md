## Zavrsni_rad
Kod završnog rada za prijediplomski sveučilišni studij računarstva na FESB-u.

## Postavke za pokretanje u VS
Otvorite Zavrsni_rad Property Pages te unutar Configuration Properties postavite putanje za:

**VC++ Directories**  
Include Directiories -> Edit -> New Line -> C:\ *[Vaša putanja]* \Zavrsni_rad\Zavrsni_rad\SDL2_Image\include  
Library Directories -> Edit -> New Line -> C:\ *[Vaša putanja]* \Zavrsni_rad\Zavrsni_rad\SDL2_Image\lib\x86

**C/C++**  
General -> Additional Include Directories -> Edit -> New Line -> C:\ *[Vaša putanja]* \Zavrsni_rad\Zavrsni_rad\SDL2_Image\include  
General -> Additional Include Directories -> Edit -> New Line -> C:\ *[Vaša putanja]* \Zavrsni_rad\Zavrsni_rad\SDL2\include

**Linker**  
General -> Additional Library Directories -> Edit -> New Line -> C:\ *[Vaša putanja]* \Zavrsni_rad\Zavrsni_rad\SDL2_Image\lib\x86  
General -> Additional Library Directories -> Edit -> New Line -> C:\ *[Vaša putanja]* \Zavrsni_rad\Zavrsni_rad\SDL2\lib\x86  
Input -> Additional Dependencies -> Edit ->  *(Dodati datoteke)*  SDL2_image.lib, SDL2.lib, SDL2main.lib

## Kontrola igrača
Igračom se upravlja pomoću W, A, S i D tipki, a držanjem SPACE_BAR-a se može podignuti prtljaga. Pronađite prtljagu u drugoj prostoriji i odnesite je na cilj (mjesto označeno s 9 crvenih kvadratića).
