# SCR Polecenia zadań

SCR_4
Zadanie 1
Napisz program, który:

    -utworzy potok (funkcją pipe),
    -uruchomi podproces, z którym proces nadrzędny będzie komunikował się przez ten potok (funkcja fork),
    -proces nadrzędny otworzy plik tekstowy podany w argumencie wywołania programu, a następnie wyśle procesowi potomnemu zawartość tego pliku przez potok,
    -proces potomny odczyta dane z potoku, a następnie wyświetli je na standardowym wyjściu dodając znak '#' na początku i końcu każdej odebranej paczki danych. Wielkość paczek jest dowolna. 

Zadanie 2
Zmodyfikuj program z punktu 1:

    -proces nadrzędny zamiast pliku graficznego ma przesyłać plik graficzny (JPEG lub PNG),
    -proces potomny zamiast odczytywać bezpośrednio z potoku wykona przekierowanie zawartości potoku na standardowe wejście (funkcje close i dup), a następnie uruchomi program (jedna z funkcji exec*) wyświetlający obrazek pobrany z tego wejścia (deskryptora 0).
    -Jako program wyświetlający obrazki można zastosować program display należący do pakietu Image Magick. Przydatnym programem wyświetlającym obrazki jest również xv, lecz jego licencja zezwala na jego użycie tylko do celów prywatnych.
    -Uruchom program, sprawdź, czy proces potomny zacznie wyświetlać obrazek od razu, czy dopiero po zamknięciu potoku przez proces nadrzędny. 
    
    SCR_5
    Zadanie 1
Napisz program, który:

    -Wykona mapowanie obszaru pamięci do pliku na dysku (funkcja mmap), w taki sposób, aby zapisy do pamięci były widoczne w pliku,
    -Będzie wykonywał w pętli nieskończonej następujące operacje na plikach tekstowych:
        -odpyta użytkownika o nazwę pliku,
        -obliczy długość pliku i zmieni odpowiednio wielkość obszaru pamięci wspólnej i zmapowanego pliku (funkcje stat, mmap, ftruncate),
        -wczyta podany plik do zmapowanego obszaru pamięci. 


Zadanie 2
Zmodyfikuj powyższy program w następujący sposób:

    -Program będzie teraz mapował pliki graficzne (JPEG lub PNG),
    -Stworzony zostanie proces potomny, który następnie uruchomi program (jedną z funkcji exec*) wyświetlający obrazek ze zmapowanego pliku z opcją aktualizacji,
    -W razie potrzeby proces nadrzędny wymusi aktualizację wyświetlanego obrazu przez podproces (funkcja memcntl/MC_SYNC???). 
