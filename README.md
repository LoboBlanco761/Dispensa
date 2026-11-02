<p align="center">
<b>Dispensa</b>
  </p>
  <p align="center">
<b>Gestione della dispensa di casa con prodotti suddivisi per categoria</b>
    </p>
    <p align="center">
      <img src="https://github.com/LoboBlanco761/Dispensa/blob/master/Immagini/Dispensa600.png" width="600">
    </p>
     <p align="center">
<b>utilizzo del linguaggio C++ con framework QT</b>
     </p>
      <p align="center">
<b>Lingue supportate: <br> Italiano , Inglese , Spagnolo , Francese , Tedesco , Greco , 
Rumeno , Portoghese , Russo</b>
</p>
<p align="center">
 Disponibile per Linux , Mac e Windows
</p>
<br>
<p align="center">
  <b>Installazione</b>
</p>

### Debian e derivate
1. Download 'dispensa_1.0-1_amd64.deb' da [Dispensa releases page] (https://github.com/LoboBlanco761/Dispensa/releases).
2.  Esegui  `sudo apt install ./dispensa_1.0-1_amd64.deb` nella cartella dove hai scaricato.
3.  Avvia da Laucher Dispensa.

### Fedora
1. Download 'dispensa_1.0-2.x86_64.rpm' da [Dispensa releases page] (https://github.com/LoboBlanco761/Dispensa/releases).
2.  Esegui  `sudo dnf install ./dispensa_1.0-2.x86_64.rpm` nella cartella dove hai scaricato.
3.  Avvia da Laucher Dispensa.

### Apple Mac
1. Download 'Dispensa.dmg' da [Dispensa releases page] (https://github.com/LoboBlanco761/Dispensa/releases).
2. Monta e apri il .dmg e copia Dispensa.app in Applicazioni.
3. Avvia da Lauchpad.

### Windows 10 11
1. Download 'DispensaInstaller.exe' da [Dispensa releases page] (https://github.com/LoboBlanco761/Dispensa/releases).
2. Lancia l'installer , rispondi si alla richiesta di autorizzaione accetta la licenza e installa.
3. Avvia da Start o dall'icona sul Desktop.

## Compilazione dai sorgenti

La compilazione richiede:

- Qt 6.9.3 con i moduli **Widgets, SQL, Multimedia e PrintSupport**;
- CMake 3.22 o superiore;
- un compilatore C++17 supportato dal sistema;
- Git, per clonare il repository.

Installa Qt 6.9.3 con Qt Online Installer e seleziona i componenti necessari per il tuo sistema e compilatore. Per esempio, su Windows scegli il kit **MinGW** e usa lo stesso kit in Qt Creator.

### Con Qt Creator

1. Clona il repository e apri `CMakeLists.txt` in Qt Creator.
2. Seleziona il kit Qt 6.9.3 appropriato per il sistema operativo.
3. Configura il progetto, seleziona la configurazione **Release** e compila.
4. Per creare una cartella distribuibile, esegui anche il passaggio **Install** di CMake.

### Da terminale

Dalla cartella principale del progetto:

```sh
cmake -S . -B build -DCMAKE\_PREFIX\_PATH="/percorso/dell'installazione/Qt/6.9.3/<kit>"
cmake --build build --config Release
cmake --install build --config Release --prefix dist
