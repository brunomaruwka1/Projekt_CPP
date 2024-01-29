# Minigames Platform

## Link to GitHub'a: https://github.com/brunomaruwka1/Projekt_CPP/tree/master/sfml_games

## Instrukcje do konfiguracji SFML

1. **Pobierz SFML:**
   - Odszukaj najnowszą wersję SFML na oficjalnej stronie: [https://www.sfml-dev.org/download.php](https://www.sfml-dev.org/download.php)
   - Pobierz odpowiednią wersję SFML dla Twojego systemu operacyjnego (np. SFML 2.5.1 - Windows - GCC 7.3.0 MinGW (SEH)).

2. **Rozpakuj pobrane archiwum:**
   - Rozpakuj pobrane archiwum SFML w wybranej lokalizacji na swoim komputerze.

3. **Skonfiguruj Projekt w Visual Studio:**
   - Uruchom Visual Studio i otwórz swój projekt.
   - Wybierz prawym przyciskiem myszy projekt w "Solution Explorer" i wybierz "Properties".
   - W "C/C++ -> General -> Additional Include Directories" dodaj ścieżkę do folderu "include" w rozpakowanym katalogu SFML.
   - W "Linker -> General -> Additional Library Directories" dodaj ścieżkę do folderu "lib" w rozpakowanym katalogu SFML.
   - W "Linker -> Input -> Additional Dependencies" dodaj odpowiednie pliki .lib z folderu "lib".

4. **Przenieś pliki DLL:**
   - Z folderu "bin" w rozpakowanym katalogu SFML skopiuj pliki DLL (np. sfml-graphics-2.dll, sfml-window-2.dll, sfml-system-2.dll) do folderu z Twoim projektem.

Gdyby jednak był problem ze skonifugrowaniem SFML zostawiam link do poradnika:
https://www.youtube.com/watch?v=lFzpkvrscs4
