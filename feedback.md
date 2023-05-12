# Feedback project13

## README

Grei start på README. Bildet tar vel stor plass.
Få med ting som hva som kreves å bygge,
så vel som andre ting om prosjektet etterhvert som det kommer på plass.
Denne filen angir førsteintrykket noen får når de ser prosjektet,
så tenk litt på hva du ka få med her for å gi ett godt innblikk/inntrykk av prosjektet.

> and figuring out how bullet works. Not the best documented thing, but it's getting more understandable.

Bullet er ganske dårlig dokumentert ja..

> * Figure out a good and efficient way of making the board in which the game is played.
> * Make outer-playing field mesh, will most likely do this in Fusion 360 and import into the project. Objects that you
    hit for points will be added using threepp.

Merk at selve collision-detection bør (må) gjøres med primitiver.
Du ønsker ikke å gi `bullet` en fancy 3D model. threepp -> bullet wrapperen støtter det heller ikke.
Du kan bruke det som visualisering, men til `bullet` gir du primitive typer,
som sånn ca. matcher det visuelle.

## CMake

Oppsettet ser ok ut så langt, men det mangler så klart litt.
Sånn generelt så ønsker vi å se noe slik som:

```
data/
include/
  myfile.hpp
src/                       # if not header-only
  myfile.cpp
  CMakeLists.txt
tests/
  CMakeLists.txt
  mytest.cpp
main.cpp       
CMakeLists.txt
README.md
.gitignore
vcpkg.json
vcpkg-configuraion.json
```

Dette er ingen fasit, men en god pekepinn. Det ser uansett som at det er dit du er på vei.

```cmake
set(SRC pinballGame.cpp src/objectsLogic.cpp)
#...
add_executable(pinballGame ${SRC})
```

Jeg ville helst sett en `CMakeLists.txt` i `src` med noe slik som:

```cmake
add_library(pinballlib "objectsLogic.cpp")
target_link_libraries(pinballlib PUBLIC ...)
target_include_directories(pinballlib PUBLIC "${CMAKE_SOURCE_DIR}/include")
```

så i rot `CMakeLists.txt`:

```cmake
add_subdirectory(src)

add_executable(pinballGame "pinballGame.cpp")
target_link_libraries(pinballGame PUBLIC pinballlib)
```

Du har lagt til en depdendency på `assimp` som enda ikke er bruk.
Ta denne bort om du ikke kommer til å bruke den.

Du har en header `gameObjects.hpp` med implementasjon i `objectsLogic.cpp"`.
Dette er lovlig, men forvirrende. Bruk samme navn.
Bruk også typ `GameObjects.hpp` eller `game_objects.hpp`, heller enn `gameObjects.hpp`.

## Kode

Du er ikke konsekvent med formeteringsreglene,
så kjør formatering (`code->reformat code`) på alle kildefilene slik at det blir det.

`main()` funksjonen din i `physicsTest.cpp` er ganske stor.
Se om du greier å delegere ut i funksjoner.

## Annet

Du mangler oppsett for tester og Continuous Integration (CI) (her i vertfall). Få dette inn før enn senere.
Testoppsett finner dere bla. [her](https://github.com/AIS1002-OOP-V23), og CI kan kopieres mer eller mindre direkte
fra `threepp`.
Du har dog en manuell test, som også er en god ting.

Sett av nok tid i nær fremtid for å komme godt på vei videre,
så du ikke sliter inn mot eksamensperioden.

Lykke til videre!

---

Disclaimer: Denne tilbakemeldingen er ikke nødvendigvis fullstendig og kan ha feil eller mangler.