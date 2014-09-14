Logging mit Rsyslog
==================

Das Logging wird mit Rsyslog, welches bereits auf der bestehenden Debian-Platform vorhanden ist, realisiert.

In der Standardeinstellung werden alle Meldungen von Rsyslog in `/var/log/syslog` gespeichert. Ist es gewünscht für die Rotorsteuerung ein eigenes Logfile zu erstellen, muss dies in der Konfiguration von Rsyslog geändert werden. Hierzu erstellt man eine neue Datei unter `/etc/rsyslog.d/` und fügt folgenden Text ein:

```
if $programname == 'rotor_control' then /var/log/rotor_control.log
```

Anschließend muss Rsyslog noch neu gestartet werden:

```
service rsyslog restart
```

Ab sofort findet man alle Logfile-Einträge unserer Anwendung unter `/var/log/rotor_control.log`.
