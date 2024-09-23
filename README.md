# GSM карта
Проект демонстрирует работу модуля SIM800L в GSM сети и определение приблизительного местополжения методом триангуляции. Модуль получает данные с вашек сотовый связи такие как: идентификатор, оператор, уровень сигнала и тд. Затем по полученным данным происходит поиск в базе данных, в которой находятся координаты найденных станций. По завершению поиска координаты сохраняются в память контроллера для отображения местоположения вышек на карте.  
![](https://github.com/shlkarl/GSM-Map/blob/main/src/Project/1.jpg)
## **Список оборудования**
* Плата [ESP32](https://aliexpress.ru/item/32864722159.html?sku_id=10000014440609820&spm=a2g2w.productlist.search_results.0.2dd54037mLcv27)
* GSM Модуль [SIM800L](https://aliexpress.ru/item/32284548751.html?sku_id=65628281840&spm=a2g2w.productlist.search_results.0.489c24a4rbnfto)
* Восьмибитный дисплей с параллельным интерфесом [2.4 TFT LCD](https://aliexpress.ru/item/1005006209528975.html?sku_id=12000036290251188&spm=a2g2w.productlist.search_results.0.7b0f65ee9Pbj3D)
    * SD-карта (2Gb+)
* Мембранная [клавиатура](https://aliexpress.ru/item/1005003070219961.html?sku_id=12000023783993123&spm=a2g2w.productlist.search_results.7.7eba3ba6Ihx6yp) 1х4
* Аккумулятор 3.7В


## **Подключение**
|ESP32|LCD_TFT  |SIM800L
|-:|-:|-:|
|16||TX|
|17||RX|
|15|TFT_DC(RS)|
|2|TFT_RD||
|4|TFT_WR||
|33|TFT_CS||
|32|TFT_RST||
|GND|RESET|
|12|TFT_D0||
|13|TFT_D1||
|26|TFT_D2||
|25|TFT_D3||
|18|TFT_D4||
|5|TFT_D5||
|27|TFT_D6||
|14|TFT_D7||
|19|SD_D0|
|21|SD_CS||
|22|SD_SCK|
|23|SD_D1||
|GND|GND|GND|
|3V3|3V3|


![](https://github.com/shlkarl/GSM-Map/blob/main/src/Project/2.jpg)

## **Используемые библиотеки**
* TFT_eSPI by Bodmer
* TouchScreen by Adafruit

>Для корректной работы TFT_eSPI файлы из src/TFT_eSPI переместить в каталог с установленной библиотекой подтвердив замену

