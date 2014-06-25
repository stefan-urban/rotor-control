Using two BeagleBone GPIOs in Userspace
=======================================

Normally the creation, setup and removal of GPIOs is a job for a system's root. But in some cases it may be usefull to permit this tasks being performed out of the userspace.

Simply create a new udev rule:
```
KERNEL=="gpio*", SUBSYSTEM=="gpio", ACTION=="add", PROGRAM="/path/to/programm"
```


Now the GPIOs can be created by
```
/sys/class/gpio/export
```

deleted by
```
/sys/class/gpio/unexport
```

and used in
```
/sys/class/gpioXY/...
```

i.e.
```
/sys/class/gpioXY/direction
/sys/class/gpioXY/value
```
