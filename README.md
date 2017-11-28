## Developer Pack for ARM Cortex_M
Здесь собраны инструменты для
* Сборка
* Линковка
* Прошивка MCU
* и Отладка

---
1. Скачать или выгрузить проект в корень C:\ 
2. Открываем редактор Переменные Окружения
* $sysdm.cpl
3. Добавляем в переменную Path следующие пути
* C:\Developer\GCC\MinGW\bin
* C:\Developer\GCC\MinGW\msys\1.0\bin
* C:\Developer\GCC\ARM\6.3.1\gcc-arm-none-eabi\bin
* C:\Developer\DEBUG\OpenOCD\0.10.0\bin
* C:\Developer\DEBUG\ST_LINK_GDB\bin
* C:\Developer\FLASHER\DFU\0.9\dfu-util-0.9-win64
* C:\Developer\FLASHER\ST-LINK_Utility

Проверяем доступность комманд, если что-то не так смотрим пути
* $arm-none-eabi-gcc
* $make

---
## Про отладку
>	Если у вас программатор ST_LINK V1 необходимо заменить драйвер на winusb.
>	http://zadig.akeo.ie	

	Исчерпывающяя материал по настройке OpenOCD от mrsin
* >	http://microsin.net/programming/ARM/openocd-manual-part1.html
* >	unix : http://gnutoolchains.com/arm-eabi/openocd/
* >	win  : https://gnu-mcu-eclipse.github.io/openocd/install/

	http://false.ekta.is/2016/01/using-netbeans-for-stm32-development-with-openocd/

## Ликбез
---
* > Сценарий Линковщика
* > https://www.opennet.ru/docs/RUS/gnu_ld/gnuld-3.html
* > EABI 
* > https://ru.wikipedia.org/wiki/Двоичный_интерфейс_приложений
* > MinGW
* > https://ru.wikipedia.org/wiki/MinGW
* > Make for Windows		
* > http://gnuwin32.sourceforge.net/packages/make.htm
	
## ARM Specific Compiler Options 
* >	-mcpu=cortex-m3 -mthumb -mno-thumb-interwork -mfpu=vfp -msoft-float -mfix-cortex-m3-ldrd
* >	Для отладки через Semihost
* >	Для вывода printf			: -specs=nosys.specs -specs=nano.specs -specs=rdimon.specs -lc -lrdimon
* >	Для корректного вывода float: LDFLAGS += -u _printf_float
