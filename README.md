Rotor control with BeagleBone Black
===================================

Dieses Projekt entstand als Teil meiner Bachelorarbeit. Es zielt darauf ab ein Interface für zwei Antennenrotoren (unterschiedlicher Hersteller) zu bauen. Dieses soll eine Schnittstelle zu hamlib besitzen.


Vorraussetzungen
----------------

Hardware
- BeagleBone Black (=BBB)
- Cape wie unter dem Ordner `/hardware/eagle-project`
- Rotoren:
 - Create ERC5A (Elevation)
 - Yaesu G-2800DXC (Azimuth)

Software
- Debian 7.x mit
 - libpcre3-dev
 - libconfig-dev


Installation & Inbetriebnahme
-----------------------------

1. Software (unter `/software/`) aus diesem Repository in beliebigen Ordner auf dem BBB speichern.

2. Software kompilieren:
```
debian@beaglebone:~/code/rotor-control/software$ make
rm -f rotor_control *.o
gcc -c -Wall adc.c -o adc.o
gcc -c -Wall configuration.c -o configuration.o
gcc -c -Wall debug.c -o debug.o
gcc -c -Wall gpio.c -o gpio.o
gcc -c -Wall gs232-interface.c -o gs232-interface.o
gcc -c -Wall main.c -o main.o
gcc -c -Wall microchip_mcp4901.c -o microchip_mcp4901.o
gcc -c -Wall pseudoterminal.c -o pseudoterminal.o
gcc -c -Wall rotor_create_erc5a.c -o rotor_create_erc5a.o
gcc -c -Wall rotor_debug.c -o rotor_debug.o
gcc -c -Wall rotors.c -o rotors.o
gcc -c -Wall rotor_yaesu_g2800dxc.c -o rotor_yaesu_g2800dxc.o
gcc adc.o configuration.o debug.o gpio.o gs232-interface.o main.o microchip_mcp4901.o pseudoterminal.o rotor_create_erc5a.o rotor_debug.o rotors.o rotor_yaesu_g2800dxc.o -o rotor_control -lconfig -lpthread -lpcre
```
3. (Optional) Konfigurationsfile unter `/etc/rotor_control.conf` anlegen. Eine Beispielkonfiguration ist beigelegt.

4. (Optional) Rsyslogd konfigurieren.

 Standardmäßig werden alle Logging-Meldungen in `/var/log/syslog` mit allen anderen Meldungen vom System vermischt. Wie unser Programm ein eigene Logging-Datei erhält wird im beiliegenen Dokument `syslog.md` erklärt.

5. Programm mit root-Rechten starten
 ```
 debian@beaglebone:~/code/rotor-control/software$ sudo ./rotor_control &
 ```

6. Logging-Datei ansehen
 ```
 debian@beaglebone:~/code/rotor-control/software$ tail /var/log/rotor_control.log 
 
 May 15 04:40:29 beaglebone rotor_control[1452]: --------------------------------------------------
 May 15 04:40:29 beaglebone rotor_control[1452]: Starting rotor_control!
 May 15 04:40:29 beaglebone rotor_control[1452]: GS232-INTERFACE: Stopping all rotors!
 May 15 04:40:29 beaglebone rotor_control[1452]: Pseudoterminal is open at: /dev/pts/1
 ```

7. Hamlib rotctld starten.
 - `-m 602` bedeutet wie verwenden ein GS232 kompatibles Interface
 
 - `-r /dev/pts/1` bedeutet wir verwenden das Pseudoterminal `pts/1` zur Kommunikation mit unserem Programm (wie oben in der Logging-Datei ersichtlich, kann abweichen!)
 
 ```
 debian@beaglebone:~/code/rotor-control/software$ sudo rotctld -m 602 -r /dev/pts/1
 ```

8. Verbindung mit gPredict aufbauen

 8.1. gPredict starten
 
 8.2. Unter _Bearbeiten_ > _Einstellungen_ > _Interfaces_ > _Rotators_ einen neuen Rotor hinzufügen.
 
 8.3 Im Hauptfenster rechts oben auf den nach unten zeigenden Pfeil drücken und im erscheinenen Menü _Antennenkontrolle_ auswählen
 
 8.4 Es erscheint folgendes Fenster:

 ![gpredict_rotor_control](docs/images/gpredict_rotor_control.png)
 
 8.5 Mit Drücken von _Kontakt_ wird die Verbindung zum BBB hergestellt und versucht die eingestellt Position anzufahren.

Verwendung ohne Rotoren
-----------------------

Zum Debugging ist es oft hilfreich das Programm __ohne__ die Rotorenanbindung zu betreiben. Dies ist möglich wenn in der Datei `rotors.c` `//#define DEBUG_SWITCH` einkommentiert wird. Dann wie oben beschrieben vorgehen.

Hintergrund: Als Rotorenansteuerung kommen jetzt nicht diverse GPIOs und ADCs zum Einsatz, welche es auf PCs gar nicht gibt, sondern ein Simulator.
